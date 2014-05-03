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
 * Created:     2014/05/01
 **********************************************************************/

#include <dragon/lang/Float.h>
#include <dragon/lang/Math.h>
#include <dragon/lang/StringBuffer.h>
#include <dragon/lang/gc/Reference.h>

#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/scene/Bounds.h>
#include <com/dragon3d/util/math/Mathf.h>

Import dragon::lang;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::scene;
Import com::dragon3d::util::math;

const Type* Bounds::TYPE = TypeOf<Bounds>();
static Logger* logger = Logger::getLogger(Bounds::TYPE, ERROR);

Bounds::Bounds() 
    :center(Vector3::ZERO), extents(Vector3::ONE){

}

Bounds::Bounds(const Vector3& center) 
    :center(center), extents(Vector3::ONE) {

}

Bounds::Bounds(const Vector3& center, const Vector3& size) 
    :center(center), extents(size) {

}

Bounds::~Bounds() {

}

/**
 * get the center of bounding box
 * 
 * @return [description]
 */
Vector3 Bounds::getCenter() {
    return this->center;
}

/**
 * set the center of bounidng box
 * 
 * @param center [description]
 */
void Bounds::setCenter(const Vector3& center) {
    this->center = center;
}

/**
 * get the extents of bounds
 * 
 * @return [description]
 */
Vector3 Bounds::getExtents() {
    return this->extents;
}

/**
 * set the extents of bounds.
 * 
 * @param extents [description]
 */
void Bounds::setExtents(const Vector3& extents) {
    this->extents = extents;
}

Vector3 Bounds::getMax() {
    return this->center.add(this->extents);
}


Vector3 Bounds::getMin() {
    return this->center.substract(this->extents);
}

Vector3 Bounds::getSize() {
    return this->extents.multiply(2.0);
}


bool Bounds::contains(const Vector3& point) {
    return Math::abs(this->center.x - point.x) < this->extents.x
        && Math::abs(this->center.y - point.y) < this->extents.y
        && Math::abs(this->center.z - point.z) < this->extents.z;
}

void Bounds::encapsulate(const Vector3& point) {
    Vector3 max = this->getMax();
    Vector3 min = this->getMin();

    max = Vector3::max(max, point);
    min = Vector3::min(min, point);

    this->setMinMax(min, max);
}


void Bounds::encapsulate(Bounds* bounds) {
    Vector3 max = this->getMax();
    Vector3 min = this->getMin();

    max = Vector3::max(max, bounds->getMax());
    min = Vector3::min(min, bounds->getMin());

    this->setMinMax(min, max);
}

void Bounds::expand(float amount) {
    this->extents = this->extents.multiply(amount);
}

void Bounds::expand(const Vector3& amount) {
    this->extents = Vector3::scale(this->extents, amount);
}

/**
 * <code>clip</code> determines if a line segment intersects the current test plane.
 * 
 * @param denom
 *            the denominator of the line segment.
 * @param numer
 *            the numerator of the line segment.
 * @param t
 *            test values of the plane.
 * @return true if the line segment intersects the plane, false otherwise.
 */
bool Bounds::clip(float denom, float numer, float* t) {
    // Return value is 'true' if line segment intersects the current test
    // plane. Otherwise 'false' is returned in which case the line segment
    // is entirely clipped.
    if (denom > 0.0) {
        if (numer > denom * t[1]) {
            return false;
        }
        if (numer > denom * t[0]) {
            t[0] = numer / denom;
        }
        return true;
    } else if (denom < 0.0) {
        if (numer > denom * t[0]) {
            return false;
        }
        if (numer > denom * t[1]) {
            t[1] = numer / denom;
        }
        return true;
    } else {
        return numer <= 0.0;
    }
}

bool Bounds::intersectRay(Ray3* ray) {
    Vector3 diff = ray->getOrigin().substract(this->center);
    Vector3 direction = ray->getDirection();

    float t[] = {0.0f, Float::POSITIVE_INFINITY};

    // Check for degenerate cases and pad using zero tolerance. Should give close enough result.
    float x = this->extents.x;
    if (x < Mathf::EPSILON && x >= 0) {
        x = Mathf::EPSILON;
    }

    float y = this->extents.y;
    if (y < Mathf::EPSILON && y >= 0) {
        y = Mathf::EPSILON;
    }

    float z = this->extents.z;
    if (z < Mathf::EPSILON && z >= 0) {
        z = Mathf::EPSILON;
    }

    bool notEntirelyClipped = clip(direction.getX(), -diff.getX() - x, t)
            && clip(-direction.getX(), diff.getX() - x, t) && clip(direction.getY(), -diff.getY() - y, t)
            && clip(-direction.getY(), diff.getY() - y, t) && clip(direction.getZ(), -diff.getZ() - z, t)
            && clip(-direction.getZ(), diff.getZ() - z, t);

    return notEntirelyClipped && (t[0] != 0.0 || t[1] != Float::POSITIVE_INFINITY);
}


bool Bounds::intersects(Bounds* bb) {
    if (this->center.getX() + this->extents.getX() < bb->center.getX() - bb->extents.getX()
            || this->center.getX() - this->extents.getX() > bb->center.getX() + bb->extents.getX()) {
        return false;
    } else if (this->center.getY() + this->extents.getY() < bb->center.getY() - bb->extents.getY()
            || this->center.getY() - this->extents.getY() > bb->center.getY() + bb->extents.getY()) {
        return false;
    } else if (this->center.getZ() + this->extents.getZ() < bb->center.getZ() - bb->extents.getZ()
            || this->center.getZ() - this->extents.getZ() > bb->center.getZ() + bb->extents.getZ()) {
        return false;
    } else {
        return true;
    }
}

void Bounds::setMinMax(const Vector3& min, const Vector3& max) {
    this->center = Vector3::centre(min, max);
    this->extents = max.substract(this->center);
}

float Bounds::sqrDistance(const Vector3& point) {
    // compute coordinates of point in box coordinate system
    Vector3 closest = point.substract(this->center);

    // project test point onto box
    double sqrDistance = 0.0;
    double delta;

    Vector3 extents = this->getExtents();

    if (closest.getX() < -extents.getX()) {
        delta = closest.getX() + extents.getX();
        sqrDistance += delta * delta;
        closest.setX(-extents.getX());
    } else if (closest.getX() > extents.getX()) {
        delta = closest.getX() - extents.getX();
        sqrDistance += delta * delta;
        closest.setX(extents.getX());
    }

    if (closest.getY() < -extents.getY()) {
        delta = closest.getY() + extents.getY();
        sqrDistance += delta * delta;
        closest.setY(-extents.getY());
    } else if (closest.getY() > extents.getY()) {
        delta = closest.getY() - extents.getY();
        sqrDistance += delta * delta;
        closest.setY(extents.getY());
    }

    if (closest.getZ() < -extents.getZ()) {
        delta = closest.getZ() + extents.getZ();
        sqrDistance += delta * delta;
        closest.setZ(-extents.getZ());
    } else if (closest.getZ() > extents.getZ()) {
        delta = closest.getZ() - extents.getZ();
        sqrDistance += delta * delta;
        closest.setZ(extents.getZ());
    }

    return Math::sqrt(sqrDistance);
}


const Array<Vector3> Bounds::getCorners() {
    Array<Vector3> store(8);

    for (int i = 0; i < store.size(); i++) {
        store[i] = Vector3();
    }

    store[0].set(center.getX() + extents.x, center.getY() + extents.y, center.getZ() + extents.z);
    store[1].set(center.getX() + extents.x, center.getY() + extents.y, center.getZ() - extents.z);
    store[2].set(center.getX() + extents.x, center.getY() - extents.y, center.getZ() + extents.z);
    store[3].set(center.getX() + extents.x, center.getY() - extents.y, center.getZ() - extents.z);
    store[4].set(center.getX() - extents.x, center.getY() + extents.y, center.getZ() + extents.z);
    store[5].set(center.getX() - extents.x, center.getY() + extents.y, center.getZ() - extents.z);
    store[6].set(center.getX() - extents.x, center.getY() - extents.y, center.getZ() + extents.z);
    store[7].set(center.getX() - extents.x, center.getY() - extents.y, center.getZ() - extents.z);

    return store;
}

// Some transform matrices are not in decomposed form and in this
// situation we need to use a different, more robust, algorithm
// for computing the new bounding box.
Bounds* Bounds::transform(const Matrix4x4& matrix) {
    const Array<Vector3> corners = this->getCorners();

    Vector3 init = matrix.multiplyPoint(corners[0]);
    Bounds* box = new Bounds(init, Vector3::ZERO);

    if (logger->isDebugEnabled()) {
        logger->debug("transform bounds:");

        Ref<String> srcInitInfo = corners[0].toString();
        Ref<String> vInfo = init.toString();
        logger->debug("the src init p:" + srcInitInfo);
        logger->debug("the init p:" + vInfo);
    }

    for(int i=1; i<corners.size(); i++) {
        Vector3 tmp = matrix.multiplyPoint(corners[i]);

        if (logger->isDebugEnabled()) {
            Ref<String> tmpInfo = tmp.toString();
            logger->debug("the tmp p:" + tmpInfo);
        }

        box->encapsulate(tmp);
    }

    return box;
}


String* Bounds::toString() const {
    StringBuffer* sb = new StringBuffer();

    sb->append("Bounds [\r\n");

    {
        String* tmp = String::format("    center : [%.2f, %.2f, %.2f],\r\n", this->center.x, this->center.y, this->center.z);
        sb->append(tmp);
        SafeRelease(tmp);
    }

    {
        String* tmp = String::format("    extents : [%.2f, %.2f, %.2f],\r\n", this->extents.x, this->extents.y, this->extents.z);
        sb->append(tmp);
        SafeRelease(tmp);
    }

    sb->append("]\r\n");

    String* ret = sb->toString();
    SafeRelease(sb);

    return ret;
}
