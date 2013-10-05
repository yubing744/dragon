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
#include <com/dragon3d/scene/GameObject.h>

BeginPackage3(com, dragon3d, framework)

Import com::dragon3d::scene;

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
	virtual GameObject* find(const char* name) = 0;

	/**
	 * find game object by name
	 */
	virtual GameObject* findWithTag(const char* tag) = 0;

	/**
	 * find game objects by tag
	 */
	virtual List<GameObject>* findGameObjectsWithTag(const char* tag) = 0;

	/**
	 * find all gameobject
	 * 
	 * @return [description]
	 */
	virtual List<GameObject>* getAll() = 0;

};//Scene

EndPackage3 //(com, dragon3d, framework)

#endif //Scene_Framework_Dragon3d_Com_H

/*
#pragma once

#include "dg_config.h"

#ifndef DG_SCENE
#define DG_SCENE

#include "dg_game_object.h"
#include "dg_horizon_grid.h"

class DGScene
	:public DGGameObject
{
public:
	DGScene(void);
	virtual ~DGScene(void);

public:
	virtual void init(DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
	virtual void turnOnHorizonGrid();
	virtual void turnOffHorizonGrid();

private:
	DGHorizonGrid* horizonGrid;
};

#endif

 */