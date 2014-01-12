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

#include <dragon/util/HashMap.h>
#include <dragon/util/logging/Logger.h>
#include <dragonx/audio/io/spi/AudioClipIORegistry.h>
#include <dragonx/audio/io/plugins/wav/WavAudioReader.h>
#include <dragonx/audio/io/plugins/mp3/Mp3AudioReader.h>
#include <dragonx/audio/io/plugins/ogg/OggAudioReader.h>

Import dragon::util;
Import dragon::util::logging;
Import dragonx::audio::io::spi;
Import dragonx::audio::io::plugins::wav;
Import dragonx::audio::io::plugins::mp3;
Import dragonx::audio::io::plugins::ogg;

const Type* AudioClipIORegistry::TYPE = TypeOf<AudioClipIORegistry>();
static Logger* logger = Logger::getLogger(AudioClipIORegistry::TYPE, ERROR);

AudioClipIORegistry* AudioClipIORegistry::singleton = null;

AudioClipIORegistry* AudioClipIORegistry::getInstance() {
    if (AudioClipIORegistry::singleton == null) {
        AudioClipIORegistry::singleton = new AudioClipIORegistry();
    }
    
    return AudioClipIORegistry::singleton;
}

AudioClipIORegistry::AudioClipIORegistry() 
    :readerMap(new HashMap<String, AudioReader>()) {
    init();
}

AudioClipIORegistry::~AudioClipIORegistry() {

}

void AudioClipIORegistry::init() {
    // WAV
    registerAudioReader("WAV", new WavAudioReader());

    // MP3
    registerAudioReader("MP3", new Mp3AudioReader());

    // OGG
    registerAudioReader("OGG", new OggAudioReader());
}

void AudioClipIORegistry::registerAudioReader(const String& audioType, AudioReader* reader) {
    this->readerMap->put(audioType, reader);
}
    
const AudioReader* AudioClipIORegistry::getAudioReader(const String& audioType) {
    return this->readerMap->get(audioType);
}
