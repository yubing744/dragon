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


#ifndef GameObject_Scene_Dragon3d_Com_H
#define GameObject_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/util/List.h>

#include <dragon/lang/reflect/Type.h>

#include <com/dragon3d/framework/Input.h>
#include <com/dragon3d/util/ReadOnlyTimer.h>

#include <com/dragon3d/scene/Component.h>
#include <com/dragon3d/scene/Transform.h>


BeginPackage3(com, dragon3d, scene)

Import dragon::lang;
Import dragon::util;

Import dragon::lang::reflect;

Import com::dragon3d::util;
Import com::dragon3d::scene;
Import com::dragon3d::framework;

/**
 * the game object
 */
class _DragonExport GameObject 
	extends(Object) {

public:
	static List<GameObject>* all;
	
public:
	GameObject();
	virtual ~GameObject();

public:
	/**
	 * update the game object
	 * 
	 * @param input [description]
	 * @param timer [description]
	 */
	virtual void update(Input* input, ReadOnlyTimer* timer);

	/**
	 * add component.
	 * 
	 * @param component [description]
	 */
	virtual void addComponent(Component* component);

	/**
	 * find the componet by type
	 * 
	 * @param  type [description]
	 * @return      [description]
	 */
	virtual Component* getComponent(Type* type);

protected:
	/**
	 * the name of game object;
	 */
	String* name;

	/**
	 * if the game object should hide.
	 */
	bool hideFlags;

	/**
	 * The Transform attached to this GameObject. (null if there is none attached).
	 */
	Transform* transform;

	/**
	 * game component.
	 */
	List<Component>* components;

};//GameObject

EndPackage3 //(com, dragon3d, scene)

#endif //GameObject_Scene_Dragon3d_Com_H


/*
#pragma once

#include "dg_transform.h"
#include "dg_component.h"

#include <vector>
using std::vector;

#if !defined(DG_GAME_OBJECT)
#define DG_GAME_OBJECT

class DGGameObject
{
protected:
	//顶点
	typedef struct tagVERTEX {
		DGfloat x, y, z;
		DGfloat u, v;
	} VERTEX;

	//三角形
	typedef struct tagTRIANGLE {
		VERTEX vertexs[3];
	} TRIANGLE;

	//区段
	typedef struct tagSECTOR {
		int numTriangles;
		TRIANGLE* triangle;
	} SECTOR;

public:
	DGGameObject(void);

	DGGameObject(DGTransform* transform);

	virtual ~DGGameObject(void);

public:
	virtual void init(DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

	virtual void addChild(DGGameObject* child);
	virtual void addComponent(DGComponent* component);

	virtual DGComponent* findComponent(const char* name);


public:
	DGTransform* transform; //位置、方向、缩放

private:
	vector<DGGameObject*> children; //孩子对象
	vector<DGComponent*> components; //组件
};

#endif
 */