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
 * Created:     2013/09/28
 **********************************************************************/

#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/scene/gameObject.h>

#include <com/dragon3d/scene/audio/AudioSource.h>
#include <com/dragon3d/framework/GameException.h>

Import dragon::util::logging;

Import com::dragon3d::scene;
Import com::dragon3d::util::math;
Import com::dragon3d::scene::audio;
Import com::dragon3d::framework;

const Type* AudioSource::TYPE = TypeOf<AudioSource>();

static Logger* logger = Logger::getLogger(AudioSource::TYPE, DEBUG);

AudioSource::AudioSource() 
    : clip(null), playing(false),
    loop(false), mute(false), volume(1.0), 
    autoPlay(true) {
}

AudioSource::~AudioSource() {
    alDeleteSources(1, &this->source);
}

bool AudioSource::isTypeOf(const Type* type) {
    return AudioSource::TYPE->equals(type) 
        || Behaviour::isTypeOf(type);
}

void AudioSource::init() {
    logger->debug("init");

    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;

    if (clip == null) {
        throw new GameException("the audio source must be config a AudioClip!");
    }

    // 载入WAV数据
    alGenBuffers(1, &buffer);

    if (alGetError() != AL_NO_ERROR) {
        throw new GameException("error in gen openal buffer!");
    }

    AudioFormat* fmt = clip->getAudioFormat();

    data = (ALvoid*)clip->getAudioData();
    size = clip->getAudioDataSize();
    freq = fmt->getSampleRate();

    if (fmt->getChannels() == 1) {
        format = AL_FORMAT_MONO16;
    } else if (fmt->getChannels() == 2) {
        format = AL_FORMAT_STEREO16;
    } else {
        throw new GameException("not support clip format!");
    }

    alBufferData(buffer, format, data, size, freq);
    

    // 捆绑源
    alGenSources(1, &source);

    if (alGetError() != AL_NO_ERROR) {
        throw new GameException("error in gen openal source!");
    }

    alSourcei (source, AL_BUFFER,   buffer   );
    alSourcef (source, AL_PITCH,    1.0f     );
    alSourcef (source, AL_GAIN,     1.0f     );
    alSourcei (source, AL_LOOPING,  this->loop);

    GameObject* gameObject = this->gameObject;
    Vector3 sourcePos = gameObject->transform->getPosition();
    Vector3 sourceVel(0, 0, 0);

    alSourcefv(source, AL_POSITION, sourcePos.toArray());
    alSourcefv(source, AL_VELOCITY, sourceVel.toArray());

    if (this->autoPlay) {
        this->play();
    }
}

void AudioSource::update(Input* input, ReadOnlyTimer* timer) {
    GameObject* gameObject = this->gameObject;
    Vector3 sourcePos = gameObject->transform->getPosition();
    Vector3 sourceVel(0, 0, 0);

    alSourcefv(source, AL_POSITION, sourcePos.toArray());
    alSourcefv(source, AL_VELOCITY, sourceVel.toArray());
}

bool AudioSource::isPlaying() {

}

bool AudioSource::isLoop() {
    return loop;
}

void AudioSource::setAudioClip(AudioClip* clip) {
    SafeDelete(this->clip);
    this->clip = clip;
}

void AudioSource::play() {
    alSourcePlay(source);
}

void AudioSource::playDelayed(float delay) {
    alSourcePlay(source);
}

void AudioSource::pause() {
    alSourcePause(source);
}

void AudioSource::stop() {
    alSourceStop(source);
}
