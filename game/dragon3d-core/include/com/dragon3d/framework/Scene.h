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
 * Created:     2013/09/17
 **********************************************************************/


#ifndef Scene_Framework_Dragon3d_Com_H
#define Scene_Framework_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/String.h>
#include <dragon/util/List.h>
#include <com/dragon3d/scene/GameObject.h>
#include <com/dragon3d/util/math/Ray3.h>
#include <com/dragon3d/util/intersection/PickResults.h>

BeginPackage3(com, dragon3d, framework)

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::scene;
Import com::dragon3d::util::math;
Import com::dragon3d::util::intersection;

/**
 * Owns all the data that is related to the scene. This class should not really know anything about rendering or the
 * screen, it's just the scene data.
 */
interface_ Scene {
public:
	virtual ~Scene(){};

public:
	/**
	 * get root gameobject of scene.
	 * 
	 * @return [description]
	 */
	virtual GameObject* getRoot() = 0;
	
	/**
	 * do pick with a ray.
	 * 
	 * @param  pickRay [description]
	 * @return         [description]
	 */
	virtual PickResults* doPick(Ray3* pickRay) = 0;

};//Scene

EndPackage3 //(com, dragon3d, framework)

#endif //Scene_Framework_Dragon3d_Com_H
