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


#ifndef Component_Scene_Dragon3d_Com_H
#define Component_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/reflect/Type.h>
#include <com/dragon3d/framework/Input.h>
#include <com/dragon3d/util/ReadOnlyTimer.h>

BeginPackage3(com, dragon3d, scene)

Import dragon::lang;
Import com::dragon3d::util;
Import com::dragon3d::scene;
Import com::dragon3d::framework;

class GameObject;
class Transform;

class _DragonExport Component 
	extends(Object) {
public:
	const static Type TYPE;

public:
	Component();
	virtual ~Component();

public:
	/**
	 * update the game component
	 * 
	 * @param input [description]
	 * @param timer [description]
	 */
	virtual void update(Input* input, ReadOnlyTimer* timer);

	/**
	 * the component is type of type.
	 * 
	 * @param  type [description]
	 * @return      [description]
	 */
	virtual bool isTypeOf(const Type& type);

public:
	/**
	 * The game object this component is attached to. A component is always attached to a game object.
	 */
	GameObject* gameObject;

	/**
	 *  The Transform attached to this GameObject (null if there is none attached).
	 */
	Transform* transform;

};//Component

EndPackage3 //(com, dragon3d, scene)

#endif //Component_Scene_Dragon3d_Com_H

/*
#pragma once

#include "dg_game.h"
#include "dg_object.h"

#if !defined(DG_COMPONENT)
#define DG_COMPONENT

#include <string>
using std::string;

class DGTransform;
class DGGameObject;

class DGComponent
{
public:
	DGComponent(void);
	DGComponent(const char* name);

	virtual ~DGComponent(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

	virtual string getName();
	virtual DGboolean isActive();
	virtual void setActive(DGboolean active);

public:
    DGGameObject* gameObject;
    DGTransform* transform;
	
protected:
	string name;
	DGboolean active;
};

#endif

 */