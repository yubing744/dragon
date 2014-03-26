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

#include <dragon/lang/Array.h>
#include <dragonx/audio/AudioClip.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/io/ByteArrayOutputStream.h>
#include <dragonx/audio/io/ByteArrayAudioInputStream.h>
#include <dragonx/audio/io/AudioIO.h>

Import dragon::io;
Import dragon::lang;
Import dragonx::audio;
Import dragon::util::logging;
Import dragonx::audio::io;

const Type* AudioClip::TYPE = TypeOf<AudioClip>();
static Logger* logger = Logger::getLogger(AudioClip::TYPE, ERROR);


AudioClip::AudioClip(const AudioFormat* format, byte* data, size_t off, size_t len) {
    this->stream = new ByteArrayAudioInputStream(format, Array<byte>(data + off, len));
    this->stream->open();
}

AudioClip::AudioClip(AudioInputStream* stream) {
    this->stream = stream;
    this->stream->open();
}

AudioClip::AudioClip(InputStream* stream, const String& format) {
    AudioInputStream* ais = AudioIO::getAudioInputStream(stream, format);
    this->stream = ais;
    this->stream->open();
}

AudioClip::~AudioClip() {
    this->stream->close();
    SafeDelete(this->stream);
}

AudioInputStream* AudioClip::getAudioInputStream() const {
    return this->stream;
}

const AudioFormat* AudioClip::getFormat() const {
    return this->stream->getFormat();
}

const Array<byte> AudioClip::getData() const {
    AudioInputStream* ais = this->stream;

    ByteArrayOutputStream* baos = new ByteArrayOutputStream();

    const AudioFormat* fmt = ais->getFormat();

    int read = 0;
    int bufSize = fmt->getFrameSize() * 1024;
    byte* buf = (byte*)malloc(bufSize);

    while((read = ais->read(buf, bufSize, 0, bufSize)) > 0) {
        baos->write(buf, bufSize, 0, read);
    }

    Array<byte> data = baos->toByteArray();

    SafeDelete(baos);

    return data;
}
