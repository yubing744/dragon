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

#ifndef AudioSource_Audio_Scene_Dragon3d_Com_H
#define AudioSource_Audio_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragonx/audio/AudioClip.h>
#include <com/dragon3d/scene/Behaviour.h>

#define NUM_BUFFERS 4

BeginPackage4(com, dragon3d, scene, audio)

Import dragonx::audio;
Import com::dragon3d::scene::audio;

class _DragonExport AudioSource extends(Behaviour) {
public:
    const static Type* TYPE;

public:
	AudioSource();
	virtual ~AudioSource();

public:
    /**
     * the component is type of type.
     * 
     * @param  type [description]
     * @return      [description]
     */
    virtual bool isTypeOf(const Type* type);

public:
    virtual void init();
    virtual void update(Input* input, ReadOnlyTimer* timer);
    virtual void destroy();

public:
    virtual bool isPlaying();
    virtual bool isLoop();
    virtual void setAudioClip(AudioClip* clip);

public:
    virtual void play();
    virtual void playDelayed(float delay);
    virtual void mixing();
    virtual void pause();
    virtual void stop();

protected:
	AudioClip* clip;

    bool playing;
    bool loop;
    bool mute;
    float volume;
    bool autoPlay;

    /* These are the buffers and source to play out through OpenAL with */
    unsigned int buffers[NUM_BUFFERS];
    unsigned int source;

    /* A temporary data buffer for readAVAudioData to write to and pass to
     * OpenAL with */
    byte *data;
    int dataSize;

    /* The format of the output stream */
    int format;
    unsigned int frequency;
    int channels;
    unsigned int bitSize;
};//AudioSource

EndPackage4 //(com, dragon3d, scene, audio)

#endif //AudioSource_Audio_Scene_Dragon3d_Com_H
