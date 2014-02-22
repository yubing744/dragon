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
 * Created:     2014/01/05
 **********************************************************************/


#include <dragonx/audio/AudioFormat.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::audio;
Import dragon::util::logging;

const Type* AudioFormat::TYPE = TypeOf<AudioFormat>();
static Logger* logger = Logger::getLogger(AudioFormat::TYPE, ERROR);

AudioFormat::AudioFormat() :
    sampleRate(0), sampleSizeInBits(0), channels(0), 
    bigEndian(false) {

}

AudioFormat::AudioFormat(const AudioFormat& format) :
    sampleRate(format.sampleRate), sampleSizeInBits(format.sampleSizeInBits), channels(format.channels), 
    bigEndian(format.bigEndian) {

}

AudioFormat::AudioFormat(const AudioFormat* format) :
    sampleRate(format->sampleRate), sampleSizeInBits(format->sampleSizeInBits), channels(format->channels), 
    bigEndian(format->bigEndian) {

}

AudioFormat::~AudioFormat() {

}

float AudioFormat::getSampleRate() const {
    return this->sampleRate;
}

int AudioFormat::getSampleSizeInBits() const {
    return this->sampleSizeInBits;
}

int AudioFormat::getChannels() const {
    return this->channels;
}

bool AudioFormat::isBigEndian() const {
    return bigEndian;
}

void AudioFormat::setSampleRate(float sampleRate) {
    this->sampleRate = sampleRate;
}

void AudioFormat::setSampleSizeInBits(int sampleBitsSize) {
    this->sampleSizeInBits = sampleBitsSize;
}

void AudioFormat::setChannels(int channels) {
    this->channels = channels;
}

void AudioFormat::setBigEndian(bool isBigEndian) {
    this->bigEndian = isBigEndian;
}