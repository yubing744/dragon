/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2014/02/23
 **********************************************************************/

#include <stdio.h>
#include <strings.h>
#include <mpg123.h>

#include <dragon/util/logging/Logger.h>
#include <dragon/io/ByteArrayOutputStream.h>
#include <dragon/io/BufferedInputStream.h>
#include <dragonx/audio/io/plugins/mp3/Mp3AudioInputStream.h>

Import dragon::io;
Import dragon::util::logging;
Import dragonx::audio::io::plugins::mp3;

const Type* Mp3AudioInputStream::TYPE = TypeOf<Mp3AudioInputStream>();
static Logger* logger = Logger::getLogger(Mp3AudioInputStream::TYPE, ERROR);

Mp3AudioInputStream::Mp3AudioInputStream(const InputStream* stream) 
    :AbstractAudioInputStream(stream) {

}

Mp3AudioInputStream::~Mp3AudioInputStream() {

}

void cleanup(mpg123_handle *mh) {
    /* It's really to late for error checks here;-) */
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
}

typedef struct _InputStreamFile {
    mpg123_handle *mh;
    InputStream* input;
    long current;
} InputStreamFile;

/* Read callback needs nothing special. */
ssize_t inputstream_read(void* handle, void *buf, size_t count) {
    InputStreamFile* isf = (InputStreamFile*)handle;
    InputStream* input = isf->input;

    int read = input->read((byte*)buf, count);
    isf->current += read;

    //logger->info("mp3 current %d", isf->current);

    return read;
}

long mp3_force_skip(InputStream* input, size_t n) {
    size_t skiped = 0;

    while (skiped < n) {
        skiped += input->skip(n - skiped);
    }

    return skiped;
}

/* Seek callback needs protection from too big offsets. */
off_t inputstream_lseek(void* handle, off_t offset, int whence) {
    InputStreamFile* ctx = (InputStreamFile*)handle;
    InputStream* input = ctx->input;

    //logger->info("mp3 lseek offset %d", offset);
    //logger->info("mp3 lseek whence %d", whence);
    //logger->info("\n");

    if (whence == SEEK_SET) {
        input->reset();

        if (offset > 0) {
            mp3_force_skip(input, offset);
        }

        ctx->current = offset;

        return 0;
    } else if (whence == SEEK_CUR) {
        if (offset > 0) {
            mp3_force_skip(input, offset);
            ctx->current += offset;
        } else {
            input->reset();
            mp3_force_skip(input, ctx->current + offset);
            ctx->current = ctx->current + offset;
        }

        return 0;
    } else if (whence == SEEK_END) {
        int available = input->available();

        if (available + offset > 0) {
            mp3_force_skip(input, available + offset);
            ctx->current += (available + offset);
        } else {
            input->reset();
            mp3_force_skip(input, ctx->current + available + offset);
            ctx->current = ctx->current + available + offset;
        }

        return 0;
    } else {
        return -1;
    }   
}

void inputstream_cleanup(void* handle) {

}

void Mp3AudioInputStream::open() {
    mpg123_handle *mh = NULL;
    unsigned char* buffer = NULL;
    size_t buffer_size = 0;
    int  channels = 0, encoding = 0;
    long rate = 0;
    int  err  = MPG123_OK;
    off_t samples = 0;

    err = mpg123_init();

    if(err != MPG123_OK || (mh = mpg123_new(NULL, &err)) == NULL) {
        cleanup(mh);

        String* msg = String::format("Basic setup goes wrong: %s", mpg123_plain_strerror(err));
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    //mpg123_param(mh, MPG123_ADD_FLAGS, MPG123_FORCE_FLOAT, 0.);


    InputStream* is = const_cast<InputStream*>(stream);

    if (!is->markSupported()) {
        is = new BufferedInputStream(is);
    } 

    int max = is->available();
    is->mark(max + 1);

    InputStreamFile* isf = (InputStreamFile*)malloc(sizeof(InputStreamFile));
    isf->mh = mh;
    isf->input = is;
    isf->current = 0;

    mpg123_replace_reader_handle(mh, inputstream_read, inputstream_lseek, inputstream_cleanup);

    if(mpg123_open_handle(mh, isf) != MPG123_OK
        || mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK ) {
        cleanup(mh);
        
        String* msg = String::format("Trouble with mpg123: %s\n", mpg123_strerror(mh));
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    /* Signed 16 is the default output format anyways; it would actually by only different if we forced it.
       So this check is here just for this explanation. */
    if(encoding != MPG123_ENC_SIGNED_16 && encoding != MPG123_ENC_FLOAT_32) { 
        cleanup(mh);

        String* msg = String::format("Bad encoding: 0x%x!\n", encoding);
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    /* Ensure that this output format will not change (it could, when we allow it). */
    mpg123_format_none(mh);
    mpg123_format(mh, rate, channels, encoding);

    AudioFormat* fmt = new AudioFormat();
    fmt->setSampleRate(rate);
    fmt->setChannels(channels);
    fmt->setSampleSizeInBits(16);

    SafeDelete(this->format);
    this->format = fmt;

    this->nativeData = isf;
}

int Mp3AudioInputStream::read(byte* b, int num, int off, int len) throw(IOException*) {
    InputStreamFile* isf = (InputStreamFile*)this->nativeData;
    mpg123_handle *mh = isf->mh;

    this->checkReadSize(len);

    size_t done = 0;
    int  err  = MPG123_OK;

    err = mpg123_read(mh, (unsigned char*)(b + off), len, &done );
    //logger->info("mp3 error num %d", err);
    if (err == MPG123_OK) {
        return done;
    }

    if(err != MPG123_DONE && err != MPG123_NEED_MORE) {
        String* msg = String::format("Warning: Decoding ended prematurely because: %s\n",
             err == MPG123_ERR ? mpg123_strerror(mh) : mpg123_plain_strerror(err) );
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    return 0;
}

void Mp3AudioInputStream::close() throw(IOException*) {
    InputStreamFile* isf = (InputStreamFile*)this->nativeData;
    mpg123_handle *mh = isf->mh;

    cleanup(mh);

    if (this->stream) {
        stream->close();
    }

    free(isf);
}
