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
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sndfile.h>

#define BUFFER_LEN          4096

#include <dragon/util/logging/Logger.h>
#include <dragon/io/BufferedInputStream.h>
#include <dragon/io/ByteArrayOutputStream.h>
#include <dragon/lang/UnsupportedOperationException.h>
#include <dragonx/audio/io/plugins/wav/WavAudioReader.h>

#include <dragonx/audio/io/plugins/wav/WavAudioInputStream.h>
#include <dragon/util/logging/Logger.h>

Import dragon::io;
Import dragon::lang;
Import dragon::util::logging;
Import dragonx::audio::io::plugins::wav;

const Type* WavAudioInputStream::TYPE = TypeOf<WavAudioInputStream>();
static Logger* logger = Logger::getLogger(WavAudioInputStream::TYPE, ERROR);

WavAudioInputStream::WavAudioInputStream(const InputStream* stream) 
    :AbstractAudioInputStream(stream) {

}

WavAudioInputStream::~WavAudioInputStream() {

}

typedef struct _StreamContext {
    SNDFILE     *infile;
    SF_VIRTUAL_IO vio;

    InputStream* input;
    size_t current;
} StreamContext;

sf_count_t stream_get_filelen(void *user_data) {
    StreamContext* ctx = (StreamContext*)user_data;
    InputStream* input = ctx->input;
    return input->available();
}

long force_skip(InputStream* input, size_t n) {
    size_t skiped = 0;

    while (skiped < n) {
        skiped += input->skip(n - skiped);
    }

    return skiped;
}

sf_count_t stream_seek(sf_count_t offset, int whence, void *user_data) {
    StreamContext* ctx = (StreamContext*)user_data;
    InputStream* input = ctx->input;

    if (whence == SEEK_SET) {
        input->reset();

        if (offset > 0) {
            force_skip(input, offset);
        }

        ctx->current = offset;

        return 0;
    } else if (whence == SEEK_CUR) {
        if (offset > 0) {
            force_skip(input, offset);
            ctx->current += offset;
        } else {
            input->reset();
            force_skip(input, ctx->current + offset);
            ctx->current = ctx->current + offset;
        }

        return 0;
    } else if (whence == SEEK_END) {
        int available = input->available();
        force_skip(input, available + offset);
        ctx->current += (available + offset);

        return 0;
    } else {
        return -1;
    }
}

sf_count_t stream_read(void *ptr, sf_count_t count, void *user_data) {
    StreamContext* ctx = (StreamContext*)user_data;
    InputStream* input = ctx->input;
    size_t read = input->read((byte*)ptr, count);
    ctx->current += read;
    return read;
}

sf_count_t stream_tell(void *user_data) {
    StreamContext* ctx = (StreamContext*)user_data;
    return ctx->current;
}

sf_count_t stream_write(const void *ptr, sf_count_t count, void *user_data) {
    throw new UnsupportedOperationException("stream_write not support!");
}

void WavAudioInputStream::open() {
    SNDFILE     *infile;
    SF_INFO     sfinfo;

    int         k, readcount;

    int filetype = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    //BufferedInputStream* bis = new BufferedInputStream(const_cast<InputStream*>(input));
    InputStream* is = const_cast<InputStream*>(this->stream);
    int max = is->available();
    is->mark(max + 1);


    StreamContext* ctx = (StreamContext*)malloc(sizeof(StreamContext));
    ctx->input = is;
    ctx->current = 0;

    SF_VIRTUAL_IO* vio = &ctx->vio;
    memset(vio, 0, sizeof(SF_VIRTUAL_IO));

    vio->get_filelen = stream_get_filelen;
    vio->seek = stream_seek;
    vio->read = stream_read;
    vio->tell = stream_tell;
    //vio.write = stream_write;
    //
    sfinfo.format = filetype;

    if (!(infile = sf_open_virtual(vio, SFM_READ, &sfinfo, (void*)ctx))) {   
        String* msg = String::format("Error : could not open file : %s", sf_strerror(NULL));
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    ctx->infile = infile;

    if (!sf_format_check(&sfinfo)) {   
        sf_close(infile) ;

        throw new IOException("Invalid encoding\n");
    }

    AudioFormat* fmt = new AudioFormat();
    fmt->setSampleRate(sfinfo.samplerate);
    fmt->setChannels(sfinfo.channels);
    fmt->setSampleSizeInBits(16);

    SafeDelete(this->format);
    this->format = fmt;

    this->nativeData = ctx;
}

int WavAudioInputStream::read(byte* b, int num, int off, int len) throw(IOException*) {
    StreamContext* ctx = (StreamContext*)this->nativeData;
    SNDFILE* infile = ctx->infile;
    AudioFormat* fmt = this->format;

    this->checkReadSize(len);

    int readcount = 0;
    short* buffer = (short*)(b + off);
    int bufSize = len / sizeof(short);

    if ((readcount = sf_read_short(infile, buffer, bufSize)) > 0) {
        return readcount * sizeof(short);
    }

    return 0;
}

void WavAudioInputStream::close() throw(IOException*) {
    StreamContext* ctx = (StreamContext*)this->nativeData;
    SNDFILE* infile = ctx->infile;
    sf_close(infile);

    free(ctx);
}

