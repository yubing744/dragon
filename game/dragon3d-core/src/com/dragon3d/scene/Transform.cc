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
#include <com/dragon3d/scene/GameObject.h>

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

bool Transform::isTypeOf(const Type* type) {
    if (Transform::TYPE->equals(type) 
        || Component::TYPE->equals(type)) {
        return true;
    }

    return false;
}

void Transform::init() {
    // init children
    List<Transform>* children = this->children;

    if (children!=null && children->size()>0) {
        Ref<Iterator<Transform> > it = children->iterator();

        while(it->hasNext()) {
            Ref<Transform> child = it->next();
            Ref<GameObject> cgo = child->getGameObject();

            if (cgo!=null) {
                cgo->init();
            }
        }
    }
}

void Transform::update(Input* input, ReadOnlyTimer* timer) {
    // update children
    List<Transform>* children = this->children;

    if (children!=null && children->size()>0) {
        Ref<Iterator<Transform> > it = children->iterator();

        while(it->hasNext()) {
            Ref<Transform> child = it->next();
            Ref<GameObject> cgo = child->getGameObject();
            
            if (cgo!=null) {
                cgo->update(input, timer);
            }
        }
    }
}

void Transform::destroy() {
    // destroy children
    List<Transform>* children = this->children;

    if (children!=null && children->size()>0) {
        Ref<Iterator<Transform> > it = children->iterator();

        while(it->hasNext()) {
            Ref<Transform> child = it->next();
            Ref<GameObject> cgo = child->getGameObject();
            
            if (cgo!=null) {
                cgo->destroy();
            }
        }
    }
}

//-------------------------------------------------------------------------
void Transform::translate(const Vector3& translation, Space relativeTo) {
    Vector3 localTranslation = translation;

    if (World == relativeTo && this->parent != null) {
        Matrix4x4 matrix = this->parent->getWorldToLocalMatrix();
        localTranslation = matrix.multiplyVector(localTranslation);
    }

    this->setLocalPosition(this->position.add(localTranslation));
}

void Transform::translate(const Vector3& translation){
    this->translate(translation, Self);
}

void Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo){
    Quaternion offset = Quaternion::euler(xAngle, yAngle, zAngle);

    if (World == relativeTo) {
        if (this->parent != null) {
            // R_offset * R_parent * R_local / R_parent
            // R_offset * R_parent * R_local * ( 1 / R_parent)
            this->rotation = offset.multiply(this->parent->getRotation()).multiply(this->rotation).multiply(this->parent->getRotation().invert());
        } else {
            this->rotation = offset.multiply(this->rotation);
        }
    } else {
        this->rotation = this->rotation.multiply(offset);
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
    Matrix4x4 matrix = this->getWorldToLocalMatrix();
    Vector3 localPos = matrix.multiplyPoint(p);
    this->setLocalPosition(localPos);
}
    
Vector3 Transform::getPosition() {
    Matrix4x4 matrix = this->getLocalToWorldMatrix();
    Vector3 pos = matrix.multiplyPoint(Vector3::ZERO);
    return pos;
}

void Transform::setRotation(const Quaternion& r) {
    Quaternion localRotation = r;

    if (this->parent != null) {
        Quaternion q = this->parent->getRotation();
        localRotation = q.invert().multiply(r);
    }

    this->setLocalRotation(localRotation);
}

Quaternion Transform::getRotation() {
    Quaternion ret = this->rotation;

    if (this->parent != null) {
        ret = this->parent->getRotation().multiply(ret);
    }

    return ret;
}

void Transform::setScale(const Vector3& s) {
    Vector3 localScale = s;

    if (this->parent != null) {
        localScale = Vector3::divideScale(s, this->parent->getScale());
    }

    this->setLocalScale(localScale);
}

Vector3 Transform::getScale() {
    Vector3 scale = this->scale;

    if (this->parent != null) {
        scale = Vector3::scale(this->parent->getScale(), scale);
    }

    return scale;
}

void Transform::setLocalPosition(const Vector3& p) {
    this->position = p;
    this->changed = true;
}

Vector3 Transform::getLocalPosition() {
    return this->position;
}

void Transform::setLocalRotation(const Quaternion& r) {
    this->rotation = r;
    this->changed = true;
}

Quaternion Transform::getLocalRotation() {
    return this->rotation;
}

void Transform::setLocalScale(const Vector3& s) {
    this->scale = s;
    this->changed = true;
}

Vector3 Transform::getLocalScale() {
    return this->scale;
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
   return this->changed || this->parent!=null;
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
        Matrix4x4 tmp = Matrix4x4::TRS(position, rotation, scale);

        if (this->parent != null) {
            tmp = tmp.multiply(this->parent->getLocalToWorldMatrix());
        }

        this->localToWorldMatrix = tmp;
        this->worldToLocalMatrix = tmp.inverse();

        this->changed = false;
    }  
}

void Transform::setParent(Transform* parent) {
    if (parent != null) {
        if (this->parent != null) {
            this->parent->children->remove(this);
        }

        SafeReplace(this->parent, parent);
        parent->children->add(this);

        this->changed = true;
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
void Transform::lookAt(const Vector3& worldPosition, const Vector3& worldUp) {
    Vector3 eye = this->getPosition();
    Vector3 center = worldPosition;
    Vector3 up = worldUp;
    
    Matrix4x4 ts = Matrix4x4::lookAt(eye, center, up);
    ts = ts.inverse();

    Quaternion newRot = ts.getQuaternion();

    this->setLocalRotation(newRot);
}

void Transform::lookAt(const Vector3& worldPosition) {
    this->lookAt(worldPosition, Vector3::UP);
}

void Transform::lookAt(Transform* target) {
    this->lookAt(target, Vector3::UP);
}

void Transform::lookAt(Transform* target, const Vector3& worldUp) {
    Vector3 worldPosition = target->getPosition();
    this->lookAt(worldPosition, worldUp);
}
