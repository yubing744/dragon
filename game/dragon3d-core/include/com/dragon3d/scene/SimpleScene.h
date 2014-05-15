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
 * Created:     2013/10/06
 **********************************************************************/


#ifndef SimpleScene_Scene_Dragon3d_Com_H
#define SimpleScene_Scene_Dragon3d_Com_H

#include <dragon/config.h>
#include <com/dragon3d/scene/AbstractScene.h>

BeginPackage3(com, dragon3d, scene)

Import com::dragon3d::scene;

/**
 * simple scene 
 * 
 * @param  Object [description]
 * @return        [description]
 */
class _DragonExport SimpleScene 
    extends(AbstractScene) {
public:
    static const Type* TYPE;

public:
    SimpleScene();
    virtual ~SimpleScene();

public:
    /**
     * do pick with a ray.
     * 
     * @param  pickRay [description]
     * @return         [description]
     */
    virtual PickResults* doPick(Ray3* pickRay);

protected:
    /**
     * the inner pick
     * 
     * @param results [description]
     * @param pickRay [description]
     */
    virtual void innerDoPick(PickResults* results, GameObject* gameObject, Ray3* pickRay);

};//SimpleScene

EndPackage3 //(com, dragon3d, scene)

#endif //SimpleScene_Scene_Dragon3d_Com_H
