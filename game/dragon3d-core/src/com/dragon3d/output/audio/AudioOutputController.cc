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
#include <dragon/lang/gc/Reference.h>
#include <com/dragon3d/output/audio/AudioOutputController.h>
#include <dragon/util/logging/Logger.h>

Import dragon::util;
Import dragon::lang::gc;
Import com::dragon3d::output::audio;
Import dragon::util::logging;

const Type* AudioOutputController::TYPE = TypeOf<AudioOutputController>();
static Logger* logger = Logger::getLogger(AudioOutputController::TYPE, ERROR);

AudioOutputController::AudioOutputController() {
    this->render = new AudioRenderer();
}

AudioOutputController::~AudioOutputController() {
    SafeRelease(this->render);
}

void AudioOutputController::init() {
    logger->info("init");
    
    this->render->init();
}

List<AudioSource>* findAllAudioSourceFromScene(Scene* scene) {
    List<AudioSource>* ases = new ArrayList<AudioSource>();

    Ref<List<GameObject> > gameObjects = scene->getAll();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();
        Ref<AudioSource> audioSource = (AudioSource*)gameObject->getFirstComponent(AudioSource::TYPE);

        if (audioSource != null) {
            ases->add(audioSource);
        }
    }

    return ases;
}

List<AudioListener>* findAllAudioListenerFromScene(Scene* scene) {
    List<AudioListener>* ales = new ArrayList<AudioListener>();

    Ref<List<GameObject> > gameObjects = scene->getAll();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();
        Ref<AudioListener> audioListener = (AudioListener*)gameObject->getFirstComponent(AudioListener::TYPE);

        if (audioListener != null) {
            ales->add(audioListener);
        }
    }

    return ales;
}

void AudioOutputController::output(Scene* scene) {
    Ref<List<AudioListener> > ales = findAllAudioListenerFromScene(scene);

    if (ales != null) {
        Ref<List<AudioSource> > ases = findAllAudioSourceFromScene(scene);

        Ref<Iterator<AudioListener> > it = ales->iterator();

        while(it->hasNext()) {
            Ref<AudioListener> listener = it->next();
            this->render->render(listener, ases);
        }
    }
}

void AudioOutputController::destroy() {
    logger->info("destroy");
    
    this->render->destroy();
}

