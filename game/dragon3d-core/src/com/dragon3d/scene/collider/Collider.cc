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
 * Created:     2014/05/14
 **********************************************************************/

#include <dragon/lang/Float.h>
#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/scene/collider/Collider.h>

Import dragon::lang;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::scene::collider;

const Type* Collider::TYPE = TypeOf<Collider>();
static Logger* logger = Logger::getLogger(Collider::TYPE, ERROR);

Collider::Collider() :enabled(true) {
    this->bounds = new Bounds();
}

Collider::~Collider() {
    SafeRelease(this->bounds);
}

bool Collider::isTypeOf(const Type* type) {
    return Collider::TYPE->equals(type) 
        || Component::isTypeOf(type);
}

Bounds* Collider::getBounds() {
    return (Bounds*)this->bounds->retain();
}

bool Collider::isEnabled() {
    return this->enabled;
}

Vector3 Collider::closestPointOnBounds(const Vector3& position) {
    Bounds* bounds = this->bounds;
    float distance = bounds->sqrDistance(position);

    Vector3 v = position.substract(bounds->getCenter());
    Ref<Ray3> ray = new Ray3(position, v);
    return ray->getPoint(distance);
}

bool Collider::raycast(Ray3* ray, RaycastHit** hitInfo, float distance) {
    Bounds* bounds = this->bounds;

    float castDistance = 0.0f;

    if (bounds->intersectRay(ray, &castDistance) && castDistance<=distance) {
        RaycastHit* hit = new RaycastHit(this, castDistance);
        *hitInfo = hit;

        return true;
    }

    return false;
}

bool Collider::raycast(Ray3* ray, RaycastHit** hitInfo) {
    float maxFloat = Float::POSITIVE_INFINITY;
    return raycast(ray, hitInfo, maxFloat);
}
