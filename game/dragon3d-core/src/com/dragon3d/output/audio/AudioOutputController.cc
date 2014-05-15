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

void AudioOutputController::output(Scene* scene) {
    Ref<GameObject> root = scene->getRoot();

    Ref<List<AudioListener> > ales = (List<AudioListener>*)root->getComponentsInChildren(AudioListener::TYPE);

    if (ales != null) {
        Ref<List<AudioSource> > ases = (List<AudioSource>*)root->getComponentsInChildren(AudioSource::TYPE);

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

