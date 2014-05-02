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
 * Created:     2013/10/05
 **********************************************************************/

#include <com/dragon3d/util/math/Mathf.h>
#include <com/dragon3d/util/math/Plane.h>

Import com::dragon3d::util::math;

const Type* Plane::TYPE = TypeOf<Plane>();

Plane::Plane()
    :normal(Vector3::UP), distance(0.0f) {

}

Plane::Plane(const Vector3& inNormal, const Vector3& inPoint) {
    throw "not implements";
}

Plane::Plane(const Vector3& inNormal, float d) 
    :normal(inNormal), distance(d) {
    this->normal = this->normal.normalize();
}

Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c) {
    throw "not implements";
}

float Plane::getDistance() {
    return this->distance;
}

Vector3 Plane::getNormal() {
    return this->normal;
}

float Plane::getDistanceToPoint(const Vector3& inPt) {
    return this->normal.dot(inPt) - this->distance;
}


bool Plane::getSide(const Vector3& inPt) {
    return this->getDistanceToPoint(inPt) > 0;
}

bool Plane::sameSide(const Vector3& inPt0, const Vector3& inPt1) {
    throw this->getSide(inPt0) * this->getSide(inPt1) > 0;
}

void Plane::set3Points(const Vector3& a, const Vector3& b, const Vector3& c) {
    this->normal = b.substract(a);
    this->normal = Vector3::cross(this->normal, Vector3(c.getX() - a.getX(), c.getY() - a.getY(), c.getZ() - a.getZ()));
    this->normal = this->normal.normalize();

    this->distance = this->normal.dot(a);
}

void Plane::setNormalAndPosition(const Vector3& inNormal, const Vector3& inPoint) {
    throw "not implements";
}

void Plane::setNormalAndDistance(const Vector3& inNormal, float distance) {
    this->normal = inNormal;
    this->normal = this->normal.normalize();

    this->distance = distance;
}