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
#include <math.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <dragon/util/logging/Logger.h>
#include <dragon/io/ByteArrayOutputStream.h>
#include <dragonx/audio/io/plugins/ogg/OggAudioReader.h>

Import dragon::io;
Import dragon::util::logging;
Import dragonx::audio::io::plugins::ogg;

const Type* OggAudioReader::TYPE = TypeOf<OggAudioReader>();
static Logger* logger = Logger::getLogger(OggAudioReader::TYPE, ERROR);

OggAudioReader::OggAudioReader() {

}

OggAudioReader::~OggAudioReader() {

}

#define OGG_BUFFER_SIZE 4096

static size_t ogg_stream_read_func(void *ptr, size_t size, size_t nmemb, void *datasource) {
    InputStream* input = (InputStream*)datasource;

    int n = 0;
    int bytes = 0;
    byte* p = (byte*)ptr;

    while(n < size) {
        int read = input->read(p + (nmemb * n), nmemb);

        if (read > 0) {
            bytes += read;
        } 
        
        n++;
    }

    return bytes;
}

static ov_callbacks OV_CALLBACKS_INPUTSTREAM = {
    (size_t (*)(void *, size_t, size_t, void *))  ogg_stream_read_func,
    (int (*)(void *, ogg_int64_t, int))           NULL,
    (int (*)(void *))                             NULL,
    (long (*)(void *))                            NULL
};

AudioClip* OggAudioReader::read(const InputStream* input) const throw(IOException*) {
    AudioClip* clip = new AudioClip();
    AudioFormat* fmt = clip->getAudioFormat();
    ByteArrayOutputStream* baos = new ByteArrayOutputStream();

    OggVorbis_File vf;
    int eof = 0;
    int current_section;
    char pcmout[OGG_BUFFER_SIZE]; /* take 4k out of the data segment, not the stack */

    if(ov_open_callbacks((void*)input, &vf, NULL, 0, OV_CALLBACKS_INPUTSTREAM) < 0) {
        throw new IOException("Input does not appear to be an Ogg bitstream!");
    }

    /* Throw the comments plus a few lines about the bitstream we're decoding */
    {
        char **ptr = ov_comment(&vf, -1)->user_comments;
        vorbis_info *vi = ov_info(&vf,-1);

        while(*ptr){
            logger->debug("%s\n", *ptr);
            ++ptr;
        }

        logger->debug("\nBitstream is %d channel, %ldHz\n", vi->channels, vi->rate);
        logger->debug("\nDecoded length: %ld samples\n",
                (long)ov_pcm_total(&vf, -1));
        logger->debug("Encoded by: %s\n\n", ov_comment(&vf, -1)->vendor);

        fmt->setSampleRate((int)vi->rate);
        fmt->setChannels(vi->channels);
    }
  
    while(!eof){
        long ret = ov_read(&vf, pcmout, sizeof(pcmout), 0, 2, 1, &current_section);

        if (ret == 0) {
            /* EOF */
            eof = 1;
        } else if (ret < 0) {
            if(ret == OV_EBADLINK){
                throw new IOException("Corrupt bitstream section! Exiting.\n");
            }
        } else {
            baos->write(pcmout, OGG_BUFFER_SIZE, 0, (int)ret);
        }
    }

    Array<byte> data = baos->toByteArray();
    clip->setAudioData(data.raw(), data.size());
    SafeDelete(baos);

    /* cleanup */
    ov_clear(&vf);

    return clip;
}