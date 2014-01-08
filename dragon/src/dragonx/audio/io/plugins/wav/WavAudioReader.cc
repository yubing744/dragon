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

#include <dragon/lang/UnsupportedOperationException.h>
#include <dragon/util/logging/Logger.h>
#include <dragonx/audio/io/plugins/wav/WavAudioReader.h>

Import dragon::lang;
Import dragon::util::logging;
Import dragonx::audio::io::plugins::wav;


const Type* WavAudioReader::TYPE = TypeOf<WavAudioReader>();
static Logger* logger = Logger::getLogger(WavAudioReader::TYPE, ERROR);

WavAudioReader::WavAudioReader() {

}

WavAudioReader::~WavAudioReader() {

}

sf_count_t stream_get_filelen(void *user_data) {
    throw new UnsupportedOperationException("stream_get_filelen not support!");
}

sf_count_t stream_seek(sf_count_t offset, int whence, void *user_data) {
    throw new UnsupportedOperationException("stream_get_filelen not support!");
}

sf_count_t stream_read(void *ptr, sf_count_t count, void *user_data) {
    InputStream* input = (InputStream*)user_data;
    return input->read(ptr, count);
}

sf_count_t stream_write(const void *ptr, sf_count_t count, void *user_data) {
    throw new UnsupportedOperationException("stream_write not support!");
}

sf_count_t stream_tell(void *user_data) {
    throw new UnsupportedOperationException("stream_tell not support!");
}

AudioClip* WavAudioReader::read(const InputStream* input) const {
    float buffer[BUFFER_LEN];

    AudioClip   *clip;
    SNDFILE     *infile;
    SF_INFO     sfinfo;

    int         k, readcount;

    int filetype = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SF_VIRTUAL_IO vio;

    vio.get_filelen = stream_get_filelen;
    vio.seek = stream_seek;
    vio.read = stream_read;
    vio.write = stream_write;
    vio.tell = stream_tell;

    if (!(infile = sf_open_virtual(&vio, SFM_READ, &sfinfo, input))) {   
        String* msg = String::format("Error : could not open file : %s", sf_strerror(NULL));
        IOExceptoin* e = new IOException(msg);
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


    clip = new AudioClip(fmt);

    size_t size = sfinfo.channels * sfinfo.frames * sizeof(float);
    byte* data = (byte*)malloc(size);
    byte* wp = data;

    while ((readcount = sf_read_float (infile, buffer, BUFFER_LEN)) > 0) {
        int readByte = readcount * sizeof(float);
        memcpy(wp, (byte*)buffer, readByte);
        wp += readByte；
    }

    clip->setAudioData(data, size);

    sf_close (infile);

    return clip;
}
