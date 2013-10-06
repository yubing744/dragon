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
#include <dragon/util/List.h>
#include <com/dragon3d/scene/GameObject.h>
#include <com/dragon3d/util/math/Ray3.h>

BeginPackage3(com, dragon3d, framework)

Import dragon::util;
Import com::dragon3d::scene;
Import com::dragon3d::util::math;

/**
 * Owns all the data that is related to the scene. This class should not really know anything about rendering or the
 * screen, it's just the scene data.
 */
interface _DragonExport Scene {
public:
	virtual ~Scene(){};

public:
	/**
	 * add a new GameObject
	 * 
	 * @param gameObject [description]
	 */
	virtual void add(GameObject* gameObject) = 0;

	/**
	 * remove game object
	 * 
	 * @param gameObject [description]
	 */
	virtual void remove(GameObject* gameObject) = 0;

	/**
	 * find game object by name
	 */
	virtual GameObject* findFirstWithName(const char* name) = 0;
	virtual List<GameObject>* findWithName(const char* name) = 0;

	/**
	 * find game object by component Type
	 */
	virtual GameObject* findFirstWithType(const Type& type) = 0;
	virtual List<GameObject>* findWithType(const Type& type) = 0;

	/**
	 * find game object by name
	 */
	virtual GameObject* findFirstWithTag(const char* tag) = 0;
	virtual List<GameObject>* findWithTag(const char* tag) = 0;

	/**
	 * find game object by ray
	 */
	virtual GameObject* findFirstWithRay(Ray3* ray) = 0;
	virtual List<GameObject>* findWithRay(Ray3* ray) = 0;

	/**
	 * find all gameobject
	 * 
	 * @return [description]
	 */
	virtual List<GameObject>* getAll() = 0;

};//Scene

EndPackage3 //(com, dragon3d, framework)

#endif //Scene_Framework_Dragon3d_Com_H
