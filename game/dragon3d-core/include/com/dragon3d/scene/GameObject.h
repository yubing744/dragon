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
	const static Type* TYPE;

public:
	GameObject();
	GameObject(const String& name);
	virtual ~GameObject();

public:// Propertys
	/**
	 * get the game object's name
	 * 
	 * @return [description]
	 */
	virtual String* getName();

	/**
	 * set the game object's name
	 *
	 */
	virtual void setName(const String& name);

public:
	/**
	 * init the game object
	 */
	virtual void init();

	/**
	 * update the game object
	 * 
	 * @param input [description]
	 * @param timer [description]
	 */
	virtual void update(Input* input, ReadOnlyTimer* timer);

	/**
	 * destroy the game object
	 */
	virtual void destroy();

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
	virtual Component* getFirstComponent(const Type* type);

	/**
	 * find the component by type.
	 */
	virtual List<Component>* getComponents(const Type* type);

	/**
	 * check if the game object has component with type
	 * 
	 * @param  type [description]
	 * @return      [description]
	 */
	virtual bool hasComponent(const Type* type);

	/**
	 * check if the game object has tag with name
	 * 
	 * @param  tagName [description]
	 * @return         [description]
	 */
	virtual bool hasTag(const String& tagName);

	/**
	 * Activates/Deactivates the GameObject.
	 *
	 * Note that a GameObject may be inactive because a parent is not active. 
	 * In that case, calling SetActive() will not activate it, 
	 * but only set the local state of the GameObject, 
	 * which can be checked using GameObject.activeSelf. 
	 * This state will then be used once all parents are active.
	 * 
	 * @param value [description]
	 */
	virtual void setActive(bool value);

	/**
	 * Check if this game object is active.
	 * 
	 * @return The local active state of this GameObject
	 */
	virtual bool isActiveSelf();

	/**
	 * Is the GameObject active in the scene?
	 * 
	 * @return [description]
	 */
	virtual bool isActiveInHierarchy();

	/**
	 * get the parent game object.
	 * 
	 * @return [description]
	 */
	virtual GameObject* getParent();

	/**
	 * get all children game object
	 */
	virtual List<GameObject>* getChildren();

	/**
	 * get the transform of game object.
	 * 
	 * @return [description]
	 */
	virtual Transform* getTransform();

	/**
	 * get the position of gameobject.
	 * 
	 * @return [description]
	 */
	virtual Vector3 getPosition();

protected:// Events
	virtual void onInit();
	virtual void onUpdate(Input* input, ReadOnlyTimer* timer);
	virtual void onDestroy();

	virtual void afterInit();
	virtual void afterUpdate(Input* input, ReadOnlyTimer* timer);
	virtual void afterDestroy();
	
protected:
	/**
	 * the name of game object;
	 */
	String* name;

	/**
	 * The Transform attached to this GameObject. (null if there is none attached).
	 */
	Transform* transform;

	/**
	 * game component.
	 */
	List<Component>* components;

	/**
	 * local active state.
	 */
	bool active;

	/**
	 * if the game object should hide.
	 */
	bool hideFlags;

	/**
	 * the layer for the game object.
	 */
	int layer;

	/**
	 * the tags for the game object
	 */
	List<String>* tags;
};//GameObject

EndPackage3 //(com, dragon3d, scene)

#endif //GameObject_Scene_Dragon3d_Com_H
