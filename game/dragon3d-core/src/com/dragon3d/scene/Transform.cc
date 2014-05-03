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

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/ArrayList.h>
#include <com/dragon3d/scene/Transform.h>
#include <dragon/util/logging/Logger.h>

Import dragon::util;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::scene;

const Type* Transform::TYPE = TypeOf<Transform>();
static Logger* logger = Logger::getLogger(Transform::TYPE, INFO);

Transform::Transform() 
    :parent(null), 
    position(Vector3::ZERO),
    rotation(Quaternion::IDENTITY),
    scale(Vector3::ONE),

    worldToLocalMatrix(Matrix4x4::IDENTITY),
    localToWorldMatrix(Matrix4x4::IDENTITY),

    changed(true) {

    this->children = new ArrayList<Transform>();
}


Transform::~Transform(void){
    if (this->parent != null) {
        this->parent->children->remove(this);
        this->parent = null;
    }

    this->detachChildren();
    SafeRelease(this->children);
}

void Transform::translate(const Vector3& translation, Space relativeTo) {
    if (World == relativeTo || this->parent == null) {
        this->position = this->position.add(translation);
    } else {
        this->position = this->parent->position.add(translation);
    }

    this->changed = true;
}

void Transform::translate(const Vector3& translation){
    this->translate(translation, Self);
}

void Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo){
    Quaternion offset = Quaternion::euler(xAngle, yAngle, zAngle);

    if (World == relativeTo || this->parent == null) {
        this->rotation = this->rotation.multiply(offset);
    } else {
        this->rotation = this->parent->rotation.multiply(offset);
    }

    this->changed = true;
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

void Transform::rotateAround(const Vector3& point, const Vector3& axis, float angle) {
    throw "not implements!";
}

// -------------------------------------------------------------


void Transform::setPosition(const Vector3& p) {
    if (this->position != p) {
        this->position = p;

        this->changed = true;
    }
}
    
Vector3 Transform::getPosition() {
    return this->position;
}

void Transform::setRotation(const Quaternion& r) {
    if (this->rotation != r) {
        this->rotation = r;

        this->changed = true;
    }
}

Quaternion Transform::getRotation() {
    return this->rotation;
}

void Transform::setScale(const Vector3& s) {
    if (this->scale != s) {
        this->scale = s;
        this->changed = true;
    }
}

Vector3 Transform::getScale() {
    return this->scale;
}

void Transform::setLocalPosition(const Vector3& p) {
    Vector3 p1 = p;

    if (this->parent != null) {
        p1 = this->parent->position.substract(p);
    } 

    this->setPosition(p1);
}

Vector3 Transform::getLocalPosition() {
    if (this->parent != null) {
        return this->position.substract(this->parent->position);
    } else {
        return this->position;
    }
}

void Transform::setLocalRotation(const Quaternion& r) {
    Quaternion r1 = r;

    if (this->parent != null) {
        r1 = this->parent->rotation.subtract(r);
    } 

    this->setRotation(r1);
}

Quaternion Transform::getLocalRotation() {
    if (this->parent != null) {
        return this->rotation.subtract(this->parent->rotation);
    } else {
        return this->rotation;
    }
}

void Transform::setLocalScale(const Vector3& s) {
    Vector3 s1 = s;

    if (this->parent != null) {
        s1 = this->parent->scale.substract(s);
    } 

    this->setScale(s1);
}

Vector3 Transform::getLocalScale() {
    if (this->parent != null) {
        return this->scale.substract(this->parent->scale);
    } else {
        return this->scale;
    }
}


Transform* Transform::getRoot() {
    Transform* t = this;

    while(t->parent != null) {
        t = t->parent;
    }

    return t;
}

Vector3 Transform::getRight() {
    const Array<Vector3> axes = this->rotation.toAxes();
    return axes[0];
}

Vector3 Transform::getUp() {
    const Array<Vector3> axes = this->rotation.toAxes();
    return axes[1];
}

Vector3 Transform::getForward() {
    const Array<Vector3> axes = this->rotation.toAxes();
    return axes[2];
}

Vector3 Transform::getEulerAngles() {
    return this->rotation.getEulerAngles();
}

void Transform::setEulerAngles(const Vector3& angles) {
    this->rotation = Quaternion::euler(angles);
    this->changed = true;
}

Vector3 Transform::getLocalEulerAngles() {
    Quaternion localRotation = this->getLocalRotation();
    return localRotation.getEulerAngles();
}

void Transform::setLocalEulerAngles(const Vector3& angles) {
    Quaternion localRotation = Quaternion::euler(angles);
    this->setLocalRotation(localRotation);
}

bool Transform::hasChanged() {
   return this->changed || (this->parent!=null && this->parent->hasChanged()); 
}

Matrix4x4 Transform::getWorldToLocalMatrix() {
    this->recalculatedMatrix();

    return this->worldToLocalMatrix;
}

Matrix4x4 Transform::getLocalToWorldMatrix() {
    this->recalculatedMatrix();

    return this->localToWorldMatrix;
}

void Transform::recalculatedMatrix() {
    if (this->hasChanged()) {
        this->localToWorldMatrix = Matrix4x4::TRS(position, rotation, scale);
        this->worldToLocalMatrix = this->localToWorldMatrix.inverse();

        this->changed = false;
    }  
}

void Transform::setParent(Transform* parent) {
    SafeReplace(this->parent, parent);

    if (parent != null) {
        parent->children->add(this);
    }
}
    
Transform* Transform::getParent() {
    if (this->parent != null) {
        return (Transform*)this->parent->retain();
    }

    return null;
}

void Transform::detachChildren() {
    Ref<Iterator<Transform> > it = this->children->iterator();

    while(it->hasNext()) {
        Ref<Transform> transform = it->next();
        transform->setParent(null);
    }
}

Transform* Transform::getChild(int index) {
    if (this->children!=null && index >=0 
        && (index < this->children->size())) {
        return this->children->get(index);
    }

    return null;
}

int Transform::childCount() {
    if (this->children != null) {
        return this->children->size();
    }

    return 0;
}

// -----------------------------------------------------------
// recursion find transform
// 
Transform* TransformInternalfind(List<Transform>* children, String* name) {
    if (children != null) {
        Ref<Iterator<Transform> > it = children->iterator();

        while(it->hasNext()) {
            Ref<Transform> transform = it->next();
            Ref<String> tName = transform->getName();

            if (tName != null && name!=null && 
                name->equals(tName.raw())) {
                return transform;
            }
        }
    }

    return null;
}

Transform* Transform::internalRecursionFind(const String* path) {
    int pos = path->indexOf('/');

    Ref<Transform> finded = null;

    if (pos > 0) {
        Ref<String> first = path->substring(0, pos);
        finded = TransformInternalfind(this->children, first);

        if (finded != null && pos < path->length()) {
            Ref<String> lastPath = path->substring(pos);
            finded = finded->internalRecursionFind(lastPath);
        }
    }

    return finded.retain();
}

Transform* Transform::find(const String& name) {
    const String* path = &name;
    return this->internalRecursionFind(path);
}

// -------------------------------------------
// transform point and vector

// transform
Vector3 Transform::transformPoint(const Vector3& p) {
    Matrix4x4 matrix = this->getWorldToLocalMatrix();
    return matrix.multiplyPoint(p);
}

Vector3 Transform::transformPoint(float x, float y, float z) {
    return this->transformPoint(Vector3(x, y, z));
}


Vector3 Transform::transformDirection(const Vector3& d) {
    Matrix4x4 matrix = this->getWorldToLocalMatrix();
    return matrix.multiplyVector(d);
}

Vector3 Transform::transformDirection(float x, float y, float z) {
    return this->transformDirection(Vector3(x, y, z));
}

// inverse transform
Vector3 Transform::inverseTransformPoint(const Vector3& p) {
    Matrix4x4 matrix = this->getLocalToWorldMatrix();
    return matrix.multiplyPoint(p);
}

Vector3 Transform::inverseTransformPoint(float x, float y, float z) {
    return this->inverseTransformPoint(Vector3(x, y, z));
}

Vector3 Transform::inverseTransformDirection(const Vector3& d) {
    Matrix4x4 matrix = this->getLocalToWorldMatrix();
    return matrix.multiplyVector(d);
}

Vector3 Transform::inverseTransformDirection(float x, float y, float z) {
    return this->inverseTransformDirection(Vector3(x, y, z));
}

// lookAt
void Transform::lookAt(const Vector3& worldPosition) {
    this->lookAt(worldPosition, Vector3::UP);
}

void Transform::lookAt(const Vector3& worldPosition, const Vector3& worldUp) {
    Vector3 eye = this->getPosition();
    Vector3 center = worldPosition;
    Vector3 up = worldUp;
    
    Matrix4x4 ts = Matrix4x4::lookAt(eye, center, up);
    ts = ts.inverse();

    Vector3 newPos = ts.getTranslation();
    Quaternion newRot = ts.getQuaternion();

    this->setPosition(newPos);
    this->setLocalRotation(newRot);
}

void Transform::lookAt(Transform* target) {
    this->lookAt(target, Vector3::UP);
}

void Transform::lookAt(Transform* target, const Vector3& worldUp) {
    Vector3 worldPosition = this->transformPoint(Vector3::ZERO);
    this->lookAt(worldPosition, worldUp);
}
