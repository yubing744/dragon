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


#include <com/dragon3d/scene/GameObject.h>
#include <dragon/lang/Class.h>
#include <dragon/util/ArrayList.h>

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::scene;

GameObject::GameObject() {
	this->transform = new Transform();
	this->components = new ArrayList<Component>();
}

GameObject::~GameObject() {
	SafeDelete(this->transform);

	this->components->clear();
	SafeDelete(this->components);
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
		component->transform = this->transform;
	}
}

Component* GameObject::getComponent(const Type* type) {
	Iterator<Component>* it = this->components->iterator();

	while(it->hasNext()) {
		Component* component = it->next();

		if (component->isTypeOf(type)) {
			SafeRelease(component);
			SafeDelete(it);

			return component;
		} else {
			SafeRelease(component);
		}
	}

	SafeDelete(it);
	return null;
}
