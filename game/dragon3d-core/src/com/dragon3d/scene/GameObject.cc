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

#include <dragon/lang/Class.h>
#include <dragon/util/ArrayList.h>
#include <com/dragon3d/scene/GameObject.h>

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::scene;

const Type* GameObject::TYPE = TypeOf<GameObject>();

GameObject::GameObject() 
	:hideFlags(false), layer(0), active(true) {
	this->name = new String("unnamed");
	this->transform = new Transform();
	this->transform->gameObject = this;

	this->components = new ArrayList<Component>();
	this->tags = new ArrayList<String>();
}

GameObject::~GameObject() {
	SafeRelease(this->name);
	SafeRelease(this->transform);
	SafeRelease(this->components);
	SafeRelease(this->tags);
}

void GameObject::init() {
	Iterator<Component>* it = this->components->iterator();

	while(it->hasNext()) {
		Component* component = it->next();
		component->init();
		SafeRelease(component);
	}

	SafeDelete(it);
}


void GameObject::update(Input* input, ReadOnlyTimer* timer) {
	Iterator<Component>* it = this->components->iterator();

	while(it->hasNext()) {
		Component* component = it->next();
		component->update(input, timer);
		SafeRelease(component);
	}

	SafeDelete(it);
}

void GameObject::destroy() {
	Iterator<Component>* it = this->components->iterator();

	while(it->hasNext()) {
		Component* component = it->next();
		component->destroy();
		SafeRelease(component);
	}

	SafeDelete(it);
}

void GameObject::addComponent(Component* component) {
	if (!this->components->contains(component)) {
		this->components->add(component);

		// attach some other componet
		component->gameObject = this;
	}
}

Component* GameObject::getFirstComponent(const Type* type) {
	Iterator<Component>* it = this->components->iterator();

	while(it->hasNext()) {
		Component* component = it->next();

		if (component->isTypeOf(type)) {
			SafeDelete(it);

			return component;
		} else {
			SafeRelease(component);
		}
	}

	SafeDelete(it);
	return null;
}

List<Component>* GameObject::getComponents(const Type* type) {
	List<Component>* results = new ArrayList<Component>();

	Iterator<Component>* it = this->components->iterator();

	while(it->hasNext()) {
		Component* component = it->next();

		if (component->isTypeOf(type)) {
			results->add(component);
		} 
		
		SafeRelease(component);
	}

	SafeDelete(it);
	
	return results;	
}

bool GameObject::hasComponent(const Type* type) {
	Iterator<Component>* it = this->components->iterator();

	while(it->hasNext()) {
		Component* component = it->next();

		if (component->isTypeOf(type)) {
			SafeRelease(component);
			SafeDelete(it);

			return true;
		} else {
			SafeRelease(component);
		}
	}

	SafeDelete(it);
	return false;
}

bool GameObject::hasTag(const String& tagName) {
	Iterator<String>* it = this->tags->iterator();

	while(it->hasNext()) {
		String* tag = it->next();

		if (tag->equals(tagName)) {
			SafeRelease(tag);
			SafeDelete(it);

			return true;
		} else {
			SafeRelease(tag);
		}
	}

	SafeDelete(it);
	return false;	
}

String* GameObject::getName() {
	String* name = this->name;
	SafeRetain(name);
	return name;
}

void GameObject::setName(const String& name) {
	SafeRelease(this->name);
	this->name = new String(name);
}

void GameObject::setActive(bool value) {
	this->active = value;
}

bool GameObject::isActiveSelf() {
	return this->active;
}

bool GameObject::isActiveInHierarchy() {
	GameObject* parent = this->getParent();

	if (parent!=null && this->active 
		&& parent->isActiveInHierarchy() ) {
		return true;
	}

	return this->active;
}

GameObject* GameObject::getParent() {
	if (this->transform->getParent() != null) {
		return this->transform->getParent()->gameObject;
	}

	return null;
}

List<GameObject>* GameObject::getChildren() {
	List<GameObject>* children = new ArrayList<GameObject>();

	int count = this->transform->childCount();

	for (int i=0; i<count; i++) {
		Transform* ts = this->transform->getChild(i);
		children->add(ts->gameObject);
	}

	return children;
}

Transform* GameObject::getTransform() {
	return this->transform;
}