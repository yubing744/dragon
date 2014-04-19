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

#include <stdlib.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/scene/GameObject.h>
#include <com/dragon3d/framework/GameException.h>
#include <com/dragon3d/scene/audio/AudioListener.h>

Import com::dragon3d::framework;
Import com::dragon3d::util::math;
Import com::dragon3d::scene::audio;

const Type* AudioListener::TYPE = TypeOf<AudioListener>();

AudioListener::AudioListener() 
    :_pause(false) {

}

AudioListener::~AudioListener() {
    alDeleteSources(1, &source);
}

bool AudioListener::isTypeOf(const Type* type) {
    return AudioListener::TYPE->equals(type) 
        || Behaviour::isTypeOf(type);
}

void AudioListener::init() {
    GameObject* gameObject = this->gameObject;
    Vector3 listenerPos = gameObject->transform->getPosition();
    Vector3 listenerVel(0, 0, 0);

    alListenerfv(AL_POSITION, listenerPos.getData());
    alListenerfv(AL_VELOCITY, listenerVel.getData());
    alListenerfv(AL_ORIENTATION, Vector3::UP.getData());

    alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
    alSourcei(source, AL_ROLLOFF_FACTOR, 0);

    if (alGetError() == AL_NO_ERROR) {
        throw new GameException("Could not set source parameters");
    }
}

void AudioListener::update(Input* input, ReadOnlyTimer* timer) {

}

void AudioListener::destroy() {
    
}

void AudioListener::pause() {
    this->_pause = true;
}

void AudioListener::resume() {
    this->_pause = false;
}

bool AudioListener::isPause() {
    return this->_pause; 
}