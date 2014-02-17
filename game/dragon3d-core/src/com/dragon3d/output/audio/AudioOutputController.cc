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
 * Created:     2014/02/11
 **********************************************************************/

#include <dragon/util/ArrayList.h>
#include <com/dragon3d/framework/GameException.h>
#include <com/dragon3d/output/audio/AudioOutputController.h>
#include <dragon/util/logging/Logger.h>

Import dragon::util;
Import com::dragon3d::framework;
Import com::dragon3d::output::audio;
Import dragon::util::logging;

const Type* AudioOutputController::TYPE = TypeOf<AudioOutputController>();
static Logger* logger = Logger::getLogger(AudioOutputController::TYPE, ERROR);

AudioOutputController::AudioOutputController() {
    this->render = new AudioRenderer();
}

AudioOutputController::~AudioOutputController() {
    SafeDelete(this->render);
}

void AudioOutputController::init() {
    logger->info("init");
    
    ALCdevice *device;
    ALCcontext *ctx;

    /* Open and initialize a device with default settings */
    device = alcOpenDevice(NULL);
    if(!device) {
        throw new GameException("Could not open a device!");
    }

    ctx = alcCreateContext(device, NULL);
    if(ctx == NULL || alcMakeContextCurrent(ctx) == ALC_FALSE) {
        if(ctx != NULL)
            alcDestroyContext(ctx);

        alcCloseDevice(device);
        throw new GameException("Could not set a context!\n");
    }

    logger->debug("Opened \"%s\"\n", alcGetString(device, ALC_DEVICE_SPECIFIER));
}

List<AudioSource>* findAllAudioSourceFromScene(Scene* scene) {
    List<AudioSource>* ases = new ArrayList<AudioSource>();

    List<GameObject>* gameObjects = scene->getAll();
    
    Iterator<GameObject>* it = gameObjects->iterator();

    while(it->hasNext()) {
        GameObject* gameObject = it->next();
        AudioSource* audioSource = (AudioSource*)gameObject->getComponent(AudioSource::TYPE);

        if (audioSource != null) {
            ases->add(audioSource);
        }
    }

    SafeDelete(it);

    return ases;
}

List<AudioListener>* findAllAudioListenerFromScene(Scene* scene) {
    List<AudioListener>* ales = new ArrayList<AudioListener>();

    List<GameObject>* gameObjects = scene->getAll();
    
    Iterator<GameObject>* it = gameObjects->iterator();

    while(it->hasNext()) {
        GameObject* gameObject = it->next();
        AudioListener* audioListener = (AudioListener*)gameObject->getComponent(AudioListener::TYPE);

        if (audioListener != null) {
            ales->add(audioListener);
        }
    }

    SafeDelete(it);

    return ales;
}

void AudioOutputController::output(Scene* scene) {
    List<AudioListener>* ales = findAllAudioListenerFromScene(scene);

    if (ales != null) {
        List<AudioSource>* ases = findAllAudioSourceFromScene(scene);

        Iterator<AudioListener>* it = ales->iterator();

        while(it->hasNext()) {
            AudioListener* listener = it->next();
            this->render->render(listener, ases);
        }

        SafeDelete(it);
    }
}

void AudioOutputController::destroy() {
    ALCdevice *device;
    ALCcontext *ctx;

    ctx = alcGetCurrentContext();
    if(ctx == NULL)
        return;

    device = alcGetContextsDevice(ctx);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(device);
}

