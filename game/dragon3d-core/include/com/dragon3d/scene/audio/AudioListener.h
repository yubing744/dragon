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


#ifndef AudioListener_Audio_Scene_Dragon3d_Com_H
#define AudioListener_Audio_Scene_Dragon3d_Com_H

#include <stdlib.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <dragon/config.h>
#include <com/dragon3d/scene/Behaviour.h>

BeginPackage4(com, dragon3d, scene, audio)

Import com::dragon3d::scene;
Import com::dragon3d::scene::audio;

class _DragonExport AudioListener extends(Behaviour) {
public:
    const static Type* TYPE;

public:
	AudioListener();
	virtual ~AudioListener();

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

protected:
    ALuint source;

};//AudioListener

EndPackage4 //(com, dragon3d, scene, audio)

#endif //AudioListener_Audio_Scene_Dragon3d_Com_H
