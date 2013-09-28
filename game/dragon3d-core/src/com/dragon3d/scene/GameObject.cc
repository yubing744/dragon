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

Import com::dragon3d::scene;

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

/*

#include "dg_game_object.h"
#include "dg_graphics_lib.h"

DGGameObject::DGGameObject(void) {
	this->transform = new DGTransform();
}

DGGameObject::DGGameObject(DGTransform* transform) {
	this->transform = transform;
}

DGGameObject::~DGGameObject(void){

}

void DGGameObject::init(DGContext* ctx){
	//初始化组件
	int csize = components.size();
	for(int i=0; i<csize; i++) {
		DGComponent* com = components[i];
        com->init(this, ctx);
	}

	//初始化孩子节点
	int size = children.size();
	for(int i=0; i<size; i++) {
		DGGameObject* child = children[i];
		child->init(ctx);
	}
}

void DGGameObject::update(DGContext* ctx){
	//更新组件
	int csize = components.size();
	for(int i=0; i<csize; i++) {
		DGComponent* com = components[i];
		if (com->isActive()) {
			com->update(ctx);
		}
	}

	//更新孩子节点
	int size = children.size();
	for(int i=0; i<size; i++) {
		DGGameObject* child = children[i];
		child->update(ctx);
	}
}

void DGGameObject::draw(DGContext* ctx){
	DGGraphicsLib* gl = ctx->getGraphicsLib();

	// 世界坐标系变换
	DGTransform* tf = this->transform;
	if (tf) {
		//平移动
		gl->translate(tf->position.x, tf->position.y, tf->position.z);

		//旋转
		gl->rotate(tf->rotation.x, 1.0f, 0.0f, 0.0f);
		gl->rotate(tf->rotation.y, 0.0f, 1.0f, 0.0f);
		gl->rotate(tf->rotation.z, 0.0f, 0.0f, 1.0f);

		//缩放
		gl->scale(tf->scale.x, tf->scale.y, tf->scale.z);
	}

	// 本地坐标系变换
	tf = this->transform;
	if (tf) {
		//平移动
		gl->translate(tf->localPosition.x, tf->localPosition.y, tf->localPosition.z);

		//旋转
		gl->rotate(tf->localRotation.x, 1.0f, 0.0f, 0.0f);
		gl->rotate(tf->localRotation.y, 0.0f, 1.0f, 0.0f);
		gl->rotate(tf->localRotation.z, 0.0f, 0.0f, 1.0f);

		//缩放
		gl->scale(tf->localScale.x, tf->localScale.y, tf->localScale.z);
	}

	//绘制组件
	int csize = components.size();
	for(int i=0; i<csize; i++) {
		DGComponent* com = components[i];

		if (com->isActive()) {
			gl->pushMatrix();
			com->draw(ctx);
			gl->popMatrix();
		}
	}

	//绘制孩子
	int size = children.size();
	for(int i=0; i<size; i++) {
		DGGameObject* child = children[i];

		gl->pushMatrix();
		child->draw(ctx);
		gl->popMatrix();
	}
}

void DGGameObject::destroy(){
	//销毁组件
	int csize = components.size();
	for(int i=0; i<csize; i++) {
		DGComponent* com = components[i];
		com->destroy();
	}

	//销毁孩子节点
	int size = children.size();
	for(int i=0; i<size; i++) {
		DGGameObject* child = children[i];
		child->destroy();
	}
}

void DGGameObject::addChild(DGGameObject* child) {
	this->children.push_back(child);
}

void DGGameObject::addComponent(DGComponent* component){
	this->components.push_back(component);
}

DGComponent* DGGameObject::findComponent(const char* name){
	int size = children.size();

	for(int i=0; i<size; i++) {
		DGComponent* com = components[i];
		if (com->getName().compare(name) == 0) {
			return com;
		}
	}

	return NULL;
}

 */