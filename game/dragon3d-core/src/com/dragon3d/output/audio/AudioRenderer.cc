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

#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/framework/GameException.h>
#include <com/dragon3d/output/audio/AudioRenderer.h>

Import dragon::util::logging;
Import com::dragon3d::framework;
Import com::dragon3d::output::audio;

const Type* AudioRenderer::TYPE = TypeOf<AudioRenderer>();
static Logger* logger = Logger::getLogger(AudioRenderer::TYPE, ERROR);

AudioRenderer::AudioRenderer() {

}

AudioRenderer::~AudioRenderer() {

}

void AudioRenderer::init() {
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

void AudioRenderer::render(AudioListener* listener, List<AudioSource>* ases) {
    if (listener != null) {
        bool pauseAudio = listener->isPause();

        Iterator<AudioSource>* it = ases->iterator();

        while(it->hasNext()) {
            AudioSource* as = it->next();
            as->mixing();
        }

        SafeDelete(it);
    }
}

void AudioRenderer::destroy() {
    logger->info("destroy");

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