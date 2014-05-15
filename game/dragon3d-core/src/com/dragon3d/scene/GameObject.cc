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

    // init component
	Ref<Iterator<Component> > itc = this->components->iterator();

	while(itc->hasNext()) {
		Ref<Component> component = itc->next();
		component->init();
	}

    // init children
    Ref<List<GameObject> > children = this->getChildren();
    Ref<Iterator<GameObject> > it = children->iterator();

    while(it->hasNext()) {
        Ref<GameObject> child = it->next();
        child->init();
    }

	this->afterInit();
}


void GameObject::update(Input* input, ReadOnlyTimer* timer) {
	this->onUpdate(input, timer);

    // update componet
	Ref<Iterator<Component> > itc = this->components->iterator();

	while(itc->hasNext()) {
		Ref<Component> component = itc->next();
		component->update(input, timer);
	}

    // update children
    Ref<List<GameObject> > children = this->getChildren();
    Ref<Iterator<GameObject> > it = children->iterator();

    while(it->hasNext()) {
        Ref<GameObject> child = it->next();
        child->update(input, timer);
    }

	this->afterUpdate(input, timer);
}

void GameObject::destroy() {
	this->onDestroy();

    // destroy componet
	Ref<Iterator<Component> > itc = this->components->iterator();

	while(itc->hasNext()) {
		Ref<Component> component = itc->next();
		component->destroy();
	}

    // destroy children
    Ref<List<GameObject> > children = this->getChildren();
    Ref<Iterator<GameObject> > it = children->iterator();

    while(it->hasNext()) {
        Ref<GameObject> child = it->next();
        child->destroy();
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

List<Component>* GameObject::getComponents(const Type* type, bool includeInactive) {
	List<Component>* results = new ArrayList<Component>();

	Ref<Iterator<Component> > it = this->components->iterator();

	while(it->hasNext()) {
		Ref<Component> comp = it->next();

		if ((comp->isActived() || includeInactive) 
            && comp->isTypeOf(type)) {
			results->add(comp);
		}
	}
	
	return results;	
}

List<Component>* GameObject::getComponents(const Type* type) {
    return this->getComponents(type, false);
}

List<Component>* GameObject::getComponentsInChildren(const Type* type, bool includeInactive) {
    List<Component>* results = new ArrayList<Component>();

    Ref<List<Component> > thisComps = this->getComponents(type);
    results->addAll(thisComps);

    Ref<List<GameObject> > gameObjects = this->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();
        Ref<List<Component> > childComps = gameObject->getComponentsInChildren(type, includeInactive);
        results->addAll(childComps);
    }

    return results;
}

List<Component>* GameObject::getComponentsInChildren(const Type* type) {
    return getComponentsInChildren(type, false);   
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


void GameObject::setParent(GameObject* gameObject) {
    Transform* ts = this->transform;
    Ref<Transform> pts = gameObject->getTransform();

    if (ts != null) {
	    ts->setParent(pts);
	}
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


void GameObject::setPosition(float x, float y, float z) {
    Ref<Transform> ts = this->getTransform();
    ts->setPosition(Vector3(x, y, z));
}

//---------------------------------------------------------
//
void GameObject::addChild(GameObject* gameObject) {
    Transform* ts = this->transform;
    Ref<Transform> gts = gameObject->getTransform();
    gts->setParent(ts);
}

void GameObject::removeChild(GameObject* gameObject) {
    Ref<Transform> gts = gameObject->getTransform();
    gts->setParent(null); 
}

GameObject* GameObject::findFirstWithName(const String& name) {
    List<GameObject>* finded = new ArrayList<GameObject>();

    Ref<List<GameObject> > gameObjects = this->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();

        if (gameObject->getName()->equals(name)) {
            return gameObject;
        }
    }

    return null;
}   

List<GameObject>* GameObject::findWithName(const String& name) {
    List<GameObject>* finded = new ArrayList<GameObject>();

    Ref<List<GameObject> > gameObjects = this->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();

        if (gameObject->getName()->equals(name)) {
            finded->add(gameObject);
        }
    }

    return finded;
}

GameObject* GameObject::findFirstWithType(const Type* type) {
    Ref<List<GameObject> > gameObjects = this->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();

        if (gameObject->hasComponent(type)) {
            return gameObject;
        }
    }

    return null;
}

List<GameObject>* GameObject::findWithType(const Type* type) {
    List<GameObject>* finded = new ArrayList<GameObject>();

    Ref<List<GameObject> > gameObjects = this->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();

        if (gameObject->hasComponent(type)) {
            finded->add(gameObject);
        }
    }

    return finded;
}

GameObject* GameObject::findFirstWithTag(const String& tag) {
    Ref<List<GameObject> > gameObjects = this->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();

        if (gameObject->hasTag(tag)) {
            return gameObject;
        }
    }

    return null;
}

List<GameObject>* GameObject::findWithTag(const String& tag) {
    List<GameObject>* finded = new ArrayList<GameObject>();

    Ref<List<GameObject> > gameObjects = this->getChildren();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();

        if (gameObject->hasTag(tag)) {
            finded->add(gameObject);
        }
    }

    return finded;
}


//---------------------------------------------------------
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
