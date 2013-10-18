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


#include <com/dragon3d/util/math/Plane.h>

Import com::dragon3d::util::math;

Plane::Plane(const Vector3& inNormal, const Vector3& inPoint) {

}

Plane::Plane(const Vector3& inNormal, float d) {

}

Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c) {

}

float Plane::getDistanceToPoint(const Vector3& inPt) {
    return 0.0f;
}


bool Plane::getSide(const Vector3& inPt) {
    return false;
}


bool Plane::raycast(const Ray3* ray, float* enter) {
    return false;
}

bool Plane::sameSide(const Vector3& inPt0, const Vector3& inPt1) {
    return false;
}

void Plane::set3Points(const Vector3& a, const Vector3& b, const Vector3& c) {

}

void Plane::setNormalAndPosition(const Vector3& inNormal, const Vector3& inPoint) {

}
