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

Import dragon::lang;
Import com::dragon3d::util::math;

const Vector3 Vector3::ZERO = Vector3(0, 0 ,0);
const Vector3 Vector3::ONE = Vector3(1, 1 ,1);

const Vector3 Vector3::FORWARD = Vector3(0, 0 ,1);
const Vector3 Vector3::BACK = Vector3(0, 0 ,-1); 

const Vector3 Vector3::UP = Vector3(0, 1 ,0); 
const Vector3 Vector3::DOWN = Vector3(0, -1 ,0);

const Vector3 Vector3::RIGHT = Vector3(1, 0 ,0);
const Vector3 Vector3::LEFT = Vector3(-1, 0 ,0);


float Vector3::angle(Vector3 from, Vector3 to) {
    return 0.0f;
}

Vector3 Vector3::clampMagnitude(Vector3 vector, float maxLength) {
    return Vector3::ZERO;
}

Vector3 Vector3::cross(Vector3 lhs, Vector3 rhs) {
    return Vector3::ZERO;
}

float Vector3::distance(Vector3 a, Vector3 b) {
    return 0.0f;
}

float Vector3::dot(Vector3 lhs, Vector3 rhs) {
    return 0.0f;
}

Vector3 Vector3::lerp(Vector3 from, Vector3 to, float t) {
    return Vector3::ZERO;
}

Vector3 Vector3::max(Vector3 lhs, Vector3 rhs) {
    return Vector3::ZERO;
}

Vector3 Vector3::min(Vector3 lhs, Vector3 rhs) {
    return Vector3::ZERO;
}

Vector3 Vector3::moveTowards(Vector3 current, Vector3 target, float maxDistanceDelta) {
    return Vector3::ZERO;  
}

void Vector3::orthoNormalize(Vector3 normal, Vector3 tangent) {

}

void Vector3::orthoNormalize(Vector3 normal, Vector3 tangent, Vector3 binormal) {

}

Vector3 Vector3::project(Vector3 vector, Vector3 onNormal) {
    return Vector3::ZERO;
}

Vector3 Vector3::reflect(Vector3 inDirection, Vector3 inNormal) {
    return Vector3::ZERO;
}

Vector3 Vector3::rotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta) {
    return Vector3::ZERO;
}

Vector3 Vector3::scale(Vector3 a, Vector3 b) {
    return Vector3::ZERO;
}

Vector3 Vector3::slerp(Vector3 from, Vector3 to, float t) {
    return Vector3::ZERO;
}

Vector3 Vector3::smoothDamp(Vector3 current, Vector3 target, Vector3 currentVelocity, float smoothTime) {
    return Vector3::ZERO;
}

Vector3 Vector3::smoothDamp(Vector3 current, Vector3 target, Vector3 currentVelocity, float smoothTime, float maxSpeed) {
    return Vector3::ZERO;
}

Vector3 Vector3::smoothDamp(Vector3 current, Vector3 target, Vector3 currentVelocity, float smoothTime, float maxSpeed, float deltaTime) {
    return Vector3::ZERO;
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

Vector3::~Vector3() {

}


float Vector3::length() {
    return Math::sqrt(lengthSquared());
}


float Vector3::lengthSquared() {
    return x*x + y*y + z*z;
}


Vector3 Vector3::normalized() {

}


void Vector3::normalize() {

}


void Vector3::set(float new_x, float new_y, float new_z) {

}

float Vector3::getValue(int index) {

}

void Vector3::setValue(int index, float value) {

}


