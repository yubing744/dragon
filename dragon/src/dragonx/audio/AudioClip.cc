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


#include <dragonx/audio/AudioClip.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::audio;
Import dragon::util::logging;

const Type* AudioClip::TYPE = TypeOf<AudioClip>();
static Logger* logger = Logger::getLogger(AudioClip::TYPE, ERROR);


AudioClip::AudioClip(const AudioFormat* format) {
    this->format = new AudioFormat(format);
    this->data = NULL;
    this->size = 0;
}

AudioClip::AudioClip(const AudioFormat* format, byte* data, size_t size) {
    this->format = new AudioFormat(format);
    this->data = data;
    this->size = size;
}

AudioClip::~AudioClip() {
    SafeDelete(this->format);

    SafeFree(this->data);
    this->size = 0;
}

const AudioFormat* AudioClip::getAudioFormat() const {
    return this->audioFormat;
}

const byte* AudioClip::getAudioData() const {
    return this->data;
}

int AudioClip::getAudioDataSize() const {
    return this->size;
}

void AudioClip::setAudioFormat(const AudioFormat* format) {
    SafeDelete(this->format);
    this->format = new AudioFormat(format);
}

void AudioClip::setAudioData(byte* data, size_t size) {
    this->data = data;
    this->size = size;
}