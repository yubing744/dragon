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
 * Created:     2013/09/20
 **********************************************************************/


#include <com/dragon3d/util/math/Mathf.h>
#include <com/dragon3d/util/math/Ray3.h>

Import com::dragon3d::util::math;

const Type* Ray3::TYPE = TypeOf<Ray3>();

Ray3::Ray3(const Vector3& origin, const Vector3& direction) 
    :origin(origin), direction(direction){
    this->direction = direction.normalize();
}

Vector3 Ray3::getOrigin() {
    return this->origin;
}

Vector3 Ray3::getDirection() {
    return this->direction;
}

Vector3 Ray3::getPoint(float distance) {
    return Vector3(origin.x + direction.x * distance, 
        origin.y + direction.y * distance,
        origin.z + direction.z * distance);
}


bool Ray3::intersectPlane(Plane* plane, float* enter) {
    Vector3 normal = plane->getNormal();
    float nu = normal.dot(this->getDirection());

    if (nu>-Mathf::EPSILON && nu<Mathf::EPSILON) {
        return false;
    }

    Vector3 p1 = normal.multiply(plane->getDistance());

    float numerator = normal.dot(p1) - normal.dot(this->getOrigin());
    float t = numerator / nu;

    if (t < 0) {
        return false;
    }

    *enter = t;

    return true;
}


bool Ray3::intersectTriangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, float* t, float* u, float* v) {
    // http://www.cnblogs.com/graphics/archive/2010/08/09/1795348.html
    
    const Vector3& orig = this->origin;
    const Vector3& dir = this->direction;

    // E1
    Vector3 E1 = v1.substract(v0);

    // E2
    Vector3 E2 = v2.substract(v0);

    // P
    Vector3 P = Vector3::cross(dir, E2);

    // determinant
    float det = E1.dot(P);

    // keep det > 0, modify T accordingly
    Vector3 T;

    if(det >0){
        T = orig.substract(v0);
    } else {
        T = v0.substract(orig);
        det = -det;
    }

    // If determinant is near zero, ray lies in plane of triangle
    if(det < Mathf::EPSILON)
        return false;

    // Calculate u and make sure u <= 1
    *u = T.dot(P);
    if( *u < 0.0f || *u > det )
        return false;

    // Q
    Vector3 Q = Vector3::cross(T, E1);

    // Calculate v and make sure u + v <= 1
    *v = dir.dot(Q);
    if( *v < 0.0f || *u + *v > det )
        return false;

    // Calculate t, scale parameters, ray intersects triangle
    *t = E2.dot(Q);

    float fInvDet = 1.0f / det;

    *t *= fInvDet;
    *u *= fInvDet;
    *v *= fInvDet;

    return true; 
}

bool Ray3::intersectTriangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, float* t) {
    float u, v;
    return intersectTriangle(v0, v1, v2, t, &u, &v);
}
