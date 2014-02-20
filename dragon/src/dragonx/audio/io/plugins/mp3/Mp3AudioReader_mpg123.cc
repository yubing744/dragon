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
 * Created:     2014/01/06
 **********************************************************************/

#include <stdio.h>
#include <strings.h>
#include <mpg123.h>

#include <dragon/util/logging/Logger.h>
#include <dragon/io/ByteArrayOutputStream.h>
#include <dragon/io/BufferedInputStream.h>
#include <dragonx/audio/io/plugins/mp3/Mp3AudioReader.h>

Import dragon::io;
Import dragon::util::logging;
Import dragonx::audio::io::plugins::mp3;

const Type* Mp3AudioReader::TYPE = TypeOf<Mp3AudioReader>();
static Logger* logger = Logger::getLogger(Mp3AudioReader::TYPE, INFO);

Mp3AudioReader::Mp3AudioReader() {

}

Mp3AudioReader::~Mp3AudioReader() {

}

void cleanup(mpg123_handle *mh) {
    /* It's really to late for error checks here;-) */
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
}

typedef struct _InputStreamFile {
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

AudioClip* Mp3AudioReader::read(const InputStream* input) const throw(IOException*) {
    mpg123_handle *mh = NULL;
    unsigned char* buffer = NULL;
    size_t buffer_size = 0;
    size_t done = 0;
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

    mpg123_param(mh, MPG123_ADD_FLAGS, MPG123_FORCE_FLOAT, 0.);


    InputStream* is = const_cast<InputStream*>(input);

    if (!input->markSupported()) {
        is = new BufferedInputStream(is);
    } 

    int max = is->available();
    is->mark(max + 1);

    InputStreamFile isf;
    isf.input = is;
    isf.current = 0;

    mpg123_replace_reader_handle(mh, inputstream_read, inputstream_lseek, inputstream_cleanup);

    if(mpg123_open_handle(mh, &isf) != MPG123_OK
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

    AudioClip* clip = new AudioClip(fmt);

    ByteArrayOutputStream* baos = new ByteArrayOutputStream();

    /* Buffer could be almost any size here, mpg123_outblock() is just some recommendation.
       Important, especially for sndfile writing, is that the size is a multiple of sample size. */
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*)malloc( buffer_size );

    do {
        err = mpg123_read( mh, buffer, buffer_size, &done );
        baos->write((const byte*)buffer, buffer_size, 0, (int)done);
        /* We are not in feeder mode, so MPG123_OK, MPG123_ERR and MPG123_NEW_FORMAT are the only possibilities.
           We do not handle a new format, MPG123_DONE is the end... so abort on anything not MPG123_OK. */
    } while (err==MPG123_OK);

    //logger->info("mp3 error num %d", err);

    if(err != MPG123_DONE && err != MPG123_NEED_MORE) {
        String* msg = String::format("Warning: Decoding ended prematurely because: %s\n",
             err == MPG123_ERR ? mpg123_strerror(mh) : mpg123_plain_strerror(err) );
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }
   
    Array<byte> data = baos->toByteArray();
    clip->setAudioData(data.raw(), data.size());
    SafeDelete(baos);

    cleanup(mh);

    return clip;
}