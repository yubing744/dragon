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
#include <dragon/util/ArrayList.h>

Import dragon::util;
Import com::dragon3d::scene;


Transform::Transform() 
    :parent(null) {
    this->children = new ArrayList<Transform>();

    this->position = Vector3::ZERO;
    this->rotation = Quaternion::IDENTITY;
    this->scale = Vector3::ONE;

    this->localPosition = Vector3::ZERO;
    this->localRotation = Quaternion::IDENTITY;
    this->localScale = Vector3::ONE;

    this->hasChanged = true;
}


Transform::~Transform(void){
    if (this->parent != null) {
        this->parent->children->remove(this);
    }

    this->detachChildren();
    SafeDelete(this->children);
}

void Transform::translate(const Vector3& translation, Space relativeTo) {
    if (this->parent != null) {
        if (World == relativeTo) {
            this->position = this->position.add(translation);
        } else if (Self == relativeTo) {
            this->localPosition = this->localPosition.add(translation);
        }
    } else {
        this->position = this->position.add(translation);
        this->localPosition = this->position;
    }

    this->hasChanged = true;
}

void Transform::translate(const Vector3& translation){
    this->translate(translation, Self);
}

void Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo){
    Quaternion rotateOffset = Quaternion::euler(xAngle, yAngle, zAngle);

    if (this->parent != null) {
        if (World == relativeTo) {
            this->rotation = this->rotation.multiply(rotateOffset);
        } else if (Self == relativeTo) {
            this->localRotation = this->localRotation.multiply(rotateOffset);
        }
    } else {
        this->rotation = this->rotation.multiply(rotateOffset);
        this->localRotation = this->rotation;
    }

    this->hasChanged = true;
}

void Transform::rotate(const Vector3& eulerAngles, Space relativeTo){
    this->rotate(eulerAngles.x, eulerAngles.y, eulerAngles.z, relativeTo);
}

void Transform::rotate(float xAngle, float yAngle, float zAngle){
    this->rotate(xAngle, yAngle, zAngle, Self);
}

void Transform::rotate(const Vector3& eulerAngles){
    this->rotate(eulerAngles.x, eulerAngles.y, eulerAngles.z, Self);
}


// -------------------------------------------------------------


void Transform::setPosition(const Vector3& p) {
    this->position = p;
    this->hasChanged = true;
}
    
Vector3 Transform::getPosition() {
    return this->position;
}



void Transform::setRotation(const Quaternion& r) {
    this->rotation = r;
    this->hasChanged = true;
}

Quaternion Transform::getRotation() {
    return this->rotation;
}

void Transform::setScale(const Vector3& s) {
    this->scale = s;
    this->hasChanged = true;
}

Vector3 Transform::getScale() {
    return this->scale;
}


void Transform::setLocalPosition(const Vector3& p) {
    this->localPosition = p;
    this->hasChanged = true;
}

Vector3 Transform::getLocalPosition() {
    return this->localPosition;
}

void Transform::setLocalRotation(const Quaternion& r) {
    this->localRotation = r;
    this->hasChanged = true;
}

Quaternion Transform::getLocalRotation() {
    return this->localRotation;
}

void Transform::setLocalScale(const Vector3& s) {
    this->localScale = s;
    this->hasChanged = true;
}

Vector3 Transform::getLocalScale() {
    return this->localScale;
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
    return this->rotation.getEulerAngles();
}

void Transform::setEulerAngles(const Vector3& angles) {
    this->rotation = Quaternion::euler(angles);
    this->hasChanged = true;
}

Vector3 Transform::getLocalEulerAngles() {
    return this->localRotation.getEulerAngles();
}

void Transform::setLocalEulerAngles(const Vector3& angles) {
    this->localRotation = Quaternion::euler(angles);
    this->hasChanged = true;
}

Matrix4x4 Transform::getWorldToLocalMatrix() {
    if (this->hasChanged) {
        this->recalculatedMatrix();
    }

    return this->worldToLocalMatrix;
}

void Transform::setWorldToLocalMatrix(const Matrix4x4& matrix) {
    this->worldToLocalMatrix = matrix;
}

Matrix4x4 Transform::getLocalToWorldMatrix() {
    if (this->hasChanged) {
        this->recalculatedMatrix();
    }

    return this->localToWorldMatrix;
}

void Transform::setLocalToWorldMatrix(const Matrix4x4& matrix) {
    this->localToWorldMatrix = matrix;
}


void Transform::recalculatedMatrix() {
    if (this->parent != null) {
        Matrix4x4 temp = Matrix4x4::IDENTITY;

        temp = temp.multiply(this->parent->getLocalToWorldMatrix());
        temp = temp.multiply(Matrix4x4::TRS(localPosition, localRotation, localScale));
        
        this->localToWorldMatrix = temp;
    } else {
        this->localToWorldMatrix = Matrix4x4::TRS(position, rotation, scale);
    }

    this->hasChanged = false;
}

void Transform::setParent(Transform* parent) {
    this->parent = parent;

    if (parent != null) {
        parent->children->add(this);
    }
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

// -----------------------------------------------------------
// recursion find transform
// 
Transform* TransformInternalfind(List<Transform>* children, String* name) {
    if (children != null) {
        Iterator<Transform>* it = children->iterator();

        while(it->hasNext()) {
            Transform* transform = it->next();

            if (transform->getName() != null 
                && transform->getName()->equals(name)) {
                SafeDelete(it);
                return transform;
            }
        }

        SafeDelete(it);
    }

    return null;
}

Transform* Transform::internalRecursionFind(const String* path) {
    int pos = path->indexOf('/');

    Transform* finded = null;

    if (pos > 0) {
        String* first = path->substring(0, pos);
        Transform* finded = TransformInternalfind(this->children, first);
        SafeDelete(first);

        if (finded != null && pos < path->length()) {
            String* lastPath = path->substring(pos);
            finded = finded->internalRecursionFind(lastPath);
            SafeDelete(lastPath);
        }
    }

    return finded;
}

Transform* Transform::find(const String& name) {
    const String* path = &name;
    return this->internalRecursionFind(path);
}
