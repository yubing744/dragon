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
 * Created:     2013/10/04
 **********************************************************************/


#include <com/dragon3d/util/math/Vector3.h>

#include <dragon/lang/Math.h>
#include <dragon/lang/IllegalArgumentException.h>

#include <com/dragon3d/util/math/Mathf.h>

Import dragon::lang;
Import com::dragon3d::util::math;

const Type* Vector3::TYPE = TypeOf<Vector3>();

const Vector3 Vector3::ZERO = Vector3(0, 0 ,0);
const Vector3 Vector3::ONE = Vector3(1, 1 ,1);

const Vector3 Vector3::FORWARD = Vector3(0, 0 ,1);
const Vector3 Vector3::BACK = Vector3(0, 0 ,-1); 

const Vector3 Vector3::UP = Vector3(0, 1 ,0); 
const Vector3 Vector3::DOWN = Vector3(0, -1 ,0);

const Vector3 Vector3::RIGHT = Vector3(1, 0 ,0);
const Vector3 Vector3::LEFT = Vector3(-1, 0 ,0);


float Vector3::angle(const Vector3& from, const Vector3& to) {
    return 0.0f;
}

Vector3 Vector3::clampMagnitude(const Vector3& vector, float maxLength) {
    return Vector3::ZERO;
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {
    return Vector3(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

float Vector3::distance(const Vector3& a, const Vector3& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;

    return Math::sqrt(dx*dx + dy*dy + dz*dz);
}

Vector3 Vector3::lerp(const Vector3& from, const Vector3& to, float t) {
    float x = from.x * (1 - t) + (to.x - from.x) * t;
    float y = from.y * (1 - t) + (to.y - from.y) * t;
    float z = from.z * (1 - t) + (to.z - from.z) * t;

    return Vector3(x, y, z);
} 

Vector3 Vector3::max(const Vector3& lhs, const Vector3& rhs) {
    float x = Math::max(lhs.x, rhs.x);
    float y = Math::max(lhs.y, rhs.y);
    float z = Math::max(lhs.z, rhs.z);

    return Vector3(x, y, z);
}

Vector3 Vector3::min(const Vector3& lhs, const Vector3& rhs) {
    float x = Math::min(lhs.x, rhs.x);
    float y = Math::min(lhs.y, rhs.y);
    float z = Math::min(lhs.z, rhs.z);

    return Vector3(x, y, z);
}

Vector3 Vector3::centre(const Vector3& lhs, const Vector3& rhs) {
    float x = (lhs.x + rhs.x) / 2;
    float y = (lhs.y + rhs.y) / 2;
    float z = (lhs.z + rhs.z) / 2;

    return Vector3(x, y, z);}


Vector3 Vector3::moveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta) {
    throw "not implements"; 
}

void Vector3::orthoNormalize(const Vector3& normal, const Vector3& tangent) {
    throw "not implements";
}

void Vector3::orthoNormalize(const Vector3& normal, const Vector3& tangent, const Vector3& binormal) {
    throw "not implements";
}

Vector3 Vector3::project(const Vector3& vector, const Vector3& onNormal) {
    throw "not implements";
}

Vector3 Vector3::reflect(const Vector3& inDirection, const Vector3& inNormal) {
    throw "not implements";
}

Vector3 Vector3::rotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta) {
    throw "not implements";
}

Vector3 Vector3::scale(const Vector3& a, const Vector3& b) {
    return Vector3(
        a.x * b.x,
        a.y * b.y,
        a.z * b.z
    );
}

Vector3 Vector3::slerp(const Vector3& from, const Vector3& to, float t) {
    throw "not implements";
}

Vector3 Vector3::smoothDamp(const Vector3& current, const Vector3& target, const Vector3& currentVelocity, float smoothTime) {
    throw "not implements";
}

Vector3 Vector3::smoothDamp(const Vector3& current, const Vector3& target, const Vector3& currentVelocity, float smoothTime, float maxSpeed) {
    throw "not implements";
}

Vector3 Vector3::smoothDamp(const Vector3& current, const Vector3& target, const Vector3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime) {
    throw "not implements";
}


// --------------------------------------------------
Vector3::Vector3() 
    : x(0.0f), y(0.0f), z(0.0f) {

}

Vector3::Vector3(float x, float y) 
    : x(x), y(y), z(0.0f) {

}

Vector3::Vector3(float x, float y, float z) 
    : x(x), y(y), z(z) {

}

Vector3::Vector3(const Vector3& a) 
    : x(a.x), y(a.y), z(a.z) {

}

bool Vector3::operator==(const Vector3& a) const {
    return x==a.x && y==a.y && z==a.z;
}

bool Vector3::operator!=(const Vector3& a) const {
    return x!=a.x || y!=a.y || z!=a.z;
}

float Vector3::length() const {
    return Math::sqrt(lengthSquared());
}

float Vector3::lengthSquared() const {
    return x*x + y*y + z*z;
}

Vector3 Vector3::normalize() const {
    const float lengthSq = lengthSquared();

    if (Math::abs(lengthSq) >  Mathf::EPSILON) {
        return multiply(1.0f / Math::sqrt(lengthSq));
    }

    return *this;
}

Vector3 Vector3::add(const Vector3& a) const {
    return Vector3(x + a.x, y + a.y, z + a.z);
}

Vector3 Vector3::substract(const Vector3& a) const {
    return Vector3(x - a.x, y - a.y, z - a.z);
}

Vector3 Vector3::multiply(float d) const {
    return Vector3(x * d, y * d, z * d);
}

Vector3 Vector3::divide(float scalar) const {
    if (Math::abs(scalar) >  Mathf::EPSILON) {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    throw new IllegalArgumentException(new String("scalar can't be zero"));
}

float Vector3::dot(const Vector3& a) const {
    return x * a.x + y * a.y + z * a.z;
}

void Vector3::set(float new_x, float new_y, float new_z) {
    this->x = new_x;
    this->y = new_y;
    this->z = new_z;
}

float Vector3::getValue(int index) {
    switch (index) {
        case 0:
            return this->x;
        case 1:
            return this->y;
        case 2:
            return this->z;
    }

    throw new IllegalArgumentException("index must be either 0, 1, 2");
}

void Vector3::setValue(int index, float value) {
    switch (index) {
        case 0:
            this->x = value;
            return;
        case 1:
            this->y = value;
            return;
        case 2:
            this->z = value;
            return;
    }

    throw new IllegalArgumentException("index must be either 0, 1, 2");
}

const float* Vector3::getData() const {
    return (float*)(&this->x);
}

const Array<float> Vector3::toFloatArray() const {
    return Array<float>(getData(), 3, false);
}

