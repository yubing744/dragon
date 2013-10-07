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


#include <com/dragon3d/util/math/Quaternion.h>

#include <dragon/lang/Math.h>
#include <com/dragon3d/util/math/Mathf.h>

Import dragon::lang;
Import com::dragon3d::util::math;

const Quaternion Quaternion::IDENTITY = Quaternion(0, 0, 0, 1);


Quaternion Quaternion::euler(float heading, float attitude, float bank) {
    float angle = heading * 0.5;
    float sinHeading = Math::sin(angle);
    float cosHeading = Math::cos(angle);

    angle = attitude * 0.5;
    float sinAttitude = Math::sin(angle);
    float cosAttitude = Math::cos(angle);

    angle = bank * 0.5;
    float sinBank = Math::sin(angle);
    float cosBank = Math::cos(angle);

    // variables used to reduce multiplication calls.
    float cosHeadingXcosAttitude = cosHeading * cosAttitude;
    float sinHeadingXsinAttitude = sinHeading * sinAttitude;
    float cosHeadingXsinAttitude = cosHeading * sinAttitude;
    float sinHeadingXcosAttitude = sinHeading * cosAttitude;

    float w = cosHeadingXcosAttitude * cosBank - sinHeadingXsinAttitude * sinBank;

    float x = cosHeadingXcosAttitude * sinBank + sinHeadingXsinAttitude * cosBank;
    float y = sinHeadingXcosAttitude * cosBank + cosHeadingXsinAttitude * sinBank;
    float z = cosHeadingXsinAttitude * cosBank - sinHeadingXcosAttitude * sinBank;

    return Quaternion(x, y, z, w).normalize();
}

Quaternion Quaternion::euler(const Vector3& e) {
    return euler(e.x, e.y, e.z);
}

Quaternion Quaternion::angleAxis(float angle, const Vector3& axis) {
    Vector3 normalizeAxis = axis.normalize();

    if (normalizeAxis == Vector3::ZERO) {
        return Quaternion::IDENTITY;
    }

    float halfAngle = 0.5 * angle;
    float _sin = Math::sin(halfAngle);

    float w = Math::cos(halfAngle);
    float x = _sin * normalizeAxis.x;
    float y = _sin * normalizeAxis.y;
    float z = _sin * normalizeAxis.z;

    return Quaternion(x, y, z, w);
}

Quaternion Quaternion::angleAxis(float angle, float x, float y, float z) {
    return angleAxis(angle, Vector3(x, y, z));
}

// -------------------------------------------------------
// 
Quaternion::Quaternion(void) {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::~Quaternion() {

}

// -------------------------------------------

float Quaternion::magnitudeSquared() {
    return w * w + x * x + y * y + z * z;
}

float Quaternion::magnitude() {
    float magnitudeSQ = magnitudeSquared();

    if (magnitudeSQ == 1.0) {
        return 1.0;
    }

    return Math::sqrt(magnitudeSQ);
}

Quaternion Quaternion::normalize() {
    float n = 1.0 / magnitude();

    float x = this->x * n;
    float y = this->y * n;
    float z = this->z * n;
    float w = this->w * n;

    return Quaternion(x, y, z, w);  
}

Vector3 Quaternion::getEulerAngles() {
    Vector3 result;

    float sqw = w * w;
    float sqx = x * x;
    float sqy = y * y;
    float sqz = z * z;

    float unit = sqx + sqy + sqz + sqw; // if normalized is one, otherwise

    // is correction factor
    float test = x * y + z * w;

    if (test > 0.499 * unit) { // singularity at north pole
        result.x = 2 * Math::atan2(x, w);
        result.y = Mathf::PI / 2;
        result.z = 0;
    } else if (test < -0.499 * unit) { // singularity at south pole
        result.x = -2 * Math::atan2(x, w);
        result.y = - Mathf::PI / 2;
        result.z = 0;
    } else {
        result.x = Math::atan2(2 * y * w - 2 * x * z, sqx - sqy - sqz + sqw);
        result.y = Math::asin(2 * test / unit);
        result.z = Math::atan2(2 * x * w - 2 * y * z, -sqx + sqy - sqz + sqw);
    }

    return result;
}

void Quaternion::set(float new_x, float new_y, float new_z, float new_w) {
    this->x = new_x;
    this->y = new_y;
    this->z = new_z;
}

void Quaternion::setFromToRotation(const Vector3& fromDirection, const Vector3& toDirection) {
    throw "not implements!";
}

void Quaternion::setLookRotation(const Vector3& view) {
    throw "not implements!";
}

void Quaternion::setLookRotation(const Vector3& view, const Vector3& up) {
    throw "not implements!";  
}