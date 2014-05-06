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
#include <dragon/lang/gc/Reference.h>

#include <dragon/util/ArrayList.h>
#include <com/dragon3d/scene/GameObject.h>

Import dragon::lang;
Import dragon::lang::gc;

Import dragon::util;
Import com::dragon3d::scene;

const Type* GameObject::TYPE = TypeOf<GameObject>();

GameObject::GameObject() 
	:hideFlags(false), layer(0), active(true) {
	this->name = new String("unnamed");
	this->transform = new Transform();
	this->transform->setGameObject(this);

	this->components = new ArrayList<Component>();
	this->tags = new ArrayList<String>();
}

GameObject::GameObject(const String& name)
	:hideFlags(false), layer(0), active(true) {
	this->name = new String(name);
	this->transform = new Transform();
	this->transform->setGameObject(this);

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
	this->onInit();

	Ref<Iterator<Component> > it = this->components->iterator();

	while(it->hasNext()) {
		Ref<Component> component = it->next();
		component->init();
	}

	this->afterInit();
}


void GameObject::update(Input* input, ReadOnlyTimer* timer) {
	this->onUpdate(input, timer);

	Ref<Iterator<Component> > it = this->components->iterator();

	while(it->hasNext()) {
		Ref<Component> component = it->next();
		component->update(input, timer);
	}

	this->afterUpdate(input, timer);
}

void GameObject::destroy() {
	this->onDestroy();

	Ref<Iterator<Component> > it = this->components->iterator();

	while(it->hasNext()) {
		Ref<Component> component = it->next();
		component->destroy();
	}

	this->afterDestroy();
}

void GameObject::addComponent(Component* component) {
	if (!this->components->contains(component)) {
		this->components->add(component);

		// attach some other componet
		component->setGameObject(this);
	}
}

Component* GameObject::getFirstComponent(const Type* type) {
	Ref<Iterator<Component> > it = this->components->iterator();

	while(it->hasNext()) {
		Ref<Component> component = it->next();

		if (component->isTypeOf(type)) {
			return component.retain();
		} 
	}

	return null;
}

List<Component>* GameObject::getComponents(const Type* type) {
	List<Component>* results = new ArrayList<Component>();

	Ref<Iterator<Component> > it = this->components->iterator();

	while(it->hasNext()) {
		Ref<Component> component = it->next();

		if (component->isTypeOf(type)) {
			results->add(component);
		}
	}
	
	return results;	
}

bool GameObject::hasComponent(const Type* type) {
	Ref<Iterator<Component> > it = this->components->iterator();

	while(it->hasNext()) {
		Ref<Component> component = it->next();

		if (component->isTypeOf(type)) {
			return true;
		} 
	}

	return false;
}

bool GameObject::hasTag(const String& tagName) {
	Ref<Iterator<String> > it = this->tags->iterator();

	while(it->hasNext()) {
		Ref<String> tag = it->next();

		if (tag->equals(tagName)) {
			return true;
		} 
	}

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
	Ref<GameObject> parent = this->getParent();

	if (parent!=null && this->active 
		&& parent->isActiveInHierarchy() ) {
		return true;
	}

	return this->active;
}

GameObject* GameObject::getParent() {
	Ref<Transform> pt = this->transform->getParent();

	if (pt != null) {
		return pt->getGameObject();
	}

	return null;
}

List<GameObject>* GameObject::getChildren() {
	List<GameObject>* children = new ArrayList<GameObject>();

	int count = this->transform->childCount();

	for (int i=0; i<count; i++) {
		Ref<Transform> ts = this->transform->getChild(i);
		Ref<GameObject> child = ts->getGameObject();

		children->add(child);
	}

	return children;
}

Transform* GameObject::getTransform() {
	return (Transform*)this->transform->retain();
}

Vector3 GameObject::getPosition() {
	return this->transform->transformDirection(Vector3::ZERO);
}

// Events stub
void GameObject::onInit() {
	// do nothing
}

void GameObject::onUpdate(Input* input, ReadOnlyTimer* timer) {
	// do nothing
}

void GameObject::onDestroy() {
	// do nothing
}

void GameObject::afterInit() {
	// do nothing
}

void GameObject::afterUpdate(Input* input, ReadOnlyTimer* timer) {
	// do nothing
}

void GameObject::afterDestroy() {
	// do nothing
}
