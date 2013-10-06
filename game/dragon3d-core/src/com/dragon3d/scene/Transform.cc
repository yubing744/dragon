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


#include <com/dragon3d/scene/Transform.h>

Import com::dragon3d::scene;


Transform::Transform(void) {
    this->position = Vector3::ZERO;
    this->rotation = Quaternion::IDENTITY;
    this->scale = Vector3::ZERO;

    this->localPosition = Vector3::ZERO;
    this->localRotation = Quaternion::IDENTITY;
    this->localScale = Vector3::ZERO;
}


Transform::~Transform(void){

}

void Transform::translate(const Vector3& translation, Space relativeTo){
    if (World == relativeTo) {
        this->position.x += translation.x;
        this->position.y += translation.y;
        this->position.z += translation.z;
    } else if (Self == relativeTo) {
        this->localPosition.x += translation.x;
        this->localPosition.y += translation.y;
        this->localPosition.z += translation.z;
    }
}

void Transform::translate(const Vector3& translation){
    this->translate(translation, Self);
}

void Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo){
    if (World == relativeTo) {
        this->rotation.x += xAngle;
        this->rotation.y += yAngle;
        this->rotation.z += zAngle;
    } else if (Self == relativeTo) {
        this->localRotation.x += xAngle;
        this->localRotation.y += yAngle;
        this->localRotation.z += zAngle;
    }
}

void Transform::rotate(float xAngle, float yAngle, float zAngle){
    this->rotate(xAngle, yAngle, zAngle, Self);
}

void Transform::rotate(const Vector3& eulerAngles, Space relativeTo){
    this->rotate(eulerAngles.x, eulerAngles.y, eulerAngles.z, relativeTo);
}

void Transform::rotate(const Vector3& eulerAngles){
    this->rotate(eulerAngles.x, eulerAngles.y, eulerAngles.z, Self);
}

Transform* Transform::getRoot() {
    Transform* t = this;

    while(t->parent != null) {
        t = t->parent;
    }

    return t;
}

Vector3 Transform::getUp() {
    throw "not implement!";
}

Vector3 Transform::getRight() {
    throw "not implement!";
}

Vector3 Transform::getForward() {
    throw "not implement!";
}

Vector3 Transform::getEulerAngles() {
    throw "not implement!";
}

void Transform::setEulerAngles(const Vector3& angles) {
    throw "not implement!";
}

Vector3 Transform::getLocalEulerAngles() {
    throw "not implement!";
}

void Transform::setLocalEulerAngles(const Vector3& angles) {
    throw "not implement!";
}

Matrix4x4 Transform::getWorldToLocalMatrix() {
    throw "not implement!";
}

void Transform::setWorldToLocalMatrix(const Matrix4x4& matrix) {
    throw "not implement!";
}

Matrix4x4 Transform::getLocalToWorldMatrix() {
    throw "not implement!";
}

void Transform::setLocalToWorldMatrix(const Matrix4x4& matrix) {
    throw "not implement!";
}

void Transform::setParent(Transform* parent) {
    throw "not implement!";
}
    
Transform* Transform::getParent() {
    return this->parent;
}

void Transform::detachChildren() {
    Iterator<Transform>* it = this->children->iterator();

    while(it->hasNext()) {
        Transform* transform = it->next();
        transform->setParent(null);
    }
}

Transform* Transform::getChild(int index) {
    if (index >=0 && index<this->children->size()) {
        return this->children->get(index);
    }

    return null;
}

int Transform::childCount() {
    return this->children->size();
}

Transform* Transform::find(const String& name) {
    throw "not implement!";
}
