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

Import dragon::io;
Import dragon::lang;
Import dragon::util::logging;
Import dragonx::audio::io::plugins::wav;


const Type* WavAudioReader::TYPE = TypeOf<WavAudioReader>();
static Logger* logger = Logger::getLogger(WavAudioReader::TYPE, ERROR);

WavAudioReader::WavAudioReader() {

}

WavAudioReader::~WavAudioReader() {

}

typedef struct _StreamContext {
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


AudioClip* WavAudioReader::read(const InputStream* input) const throw(IOException*) {
    short buffer[BUFFER_LEN];

    AudioClip   *clip;
    SNDFILE     *infile;
    SF_INFO     sfinfo;

    int         k, readcount;

    int filetype = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    //BufferedInputStream* bis = new BufferedInputStream(const_cast<InputStream*>(input));
    InputStream* is = const_cast<InputStream*>(input);
    int max = is->available();
    is->mark(max + 1);

    SF_VIRTUAL_IO vio;
    memset(&vio, 0, sizeof(SF_VIRTUAL_IO));

    vio.get_filelen = stream_get_filelen;
    vio.seek = stream_seek;
    vio.read = stream_read;
    vio.tell = stream_tell;
    //vio.write = stream_write;

    StreamContext ctx;
    ctx.input = is;
    ctx.current = 0;

    if (!(infile = sf_open_virtual(&vio, SFM_READ, &sfinfo, (void*)&ctx))) {   
        String* msg = String::format("Error : could not open file : %s", sf_strerror(NULL));
        IOException* e = new IOException(msg);
        SafeDelete(msg);

        throw e;
    }

    sfinfo.format = filetype;

    if (!sf_format_check(&sfinfo)) {   
        sf_close(infile) ;

        throw new IOException("Invalid encoding\n");
    }

    AudioFormat* fmt = new AudioFormat();
    fmt->setSampleRate(sfinfo.samplerate);
    fmt->setChannels(sfinfo.channels);
    fmt->setSampleSizeInBits(16);

    clip = new AudioClip(fmt);

    ByteArrayOutputStream* baos = new ByteArrayOutputStream();

    while ((readcount = sf_read_short(infile, buffer, BUFFER_LEN)) > 0) {
        baos->write((byte*)buffer, sizeof(short) * BUFFER_LEN, 0, sizeof(short) * readcount);
    }

    Array<byte> data = baos->toByteArray();
    clip->setAudioData(data.raw(), data.size());
    SafeDelete(baos);

    //SafeDelete(bis);
    sf_close(infile);

    return clip;
}
