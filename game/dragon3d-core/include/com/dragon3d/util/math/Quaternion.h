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


#ifndef Quaternion_Math_Util_Dragon3d_Com_H
#define Quaternion_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>

#include <com/dragon3d/util/math/Vector3.h>

BeginPackage4(com, dragon3d, util, math)

Import com::dragon3d::util::math;

class _DragonExport Quaternion {
public:
    static const Quaternion IDENTITY;

public:
    /**
     * Returns a rotation that rotates z degrees around the z axis, x degrees around the x axis, 
     * and y degrees around the y axis (in that order).
     * 
     * @param  x [description]
     * @param  y [description]
     * @param  z [description]
     * @return   [description]
     */
    static Quaternion euler(float x, float y, float z);
    static Quaternion euler(const Vector3& euler);

    /**
     * Sets the values of this quaternion to the values represented by a given angle and axis of rotation. Note that
     * this method creates an object, so use fromAngleNormalAxis if your axis is already normalized. If axis == 0,0,0
     * the quaternion is set to identity.
     * 
     * @param angle
     *            the angle to rotate (in radians).
     * @param axis
     *            the axis of rotation.
     * @return this quaternion for chaining
     * @throws NullPointerException
     *             if axis is null
     */
    static Quaternion angleAxis(float angle, const Vector3& axis);
    static Quaternion angleAxis(float angle, float x, float y, float z);

public:
    Quaternion();
    Quaternion(float x, float y, float z);
    Quaternion(float x, float y, float z, float w);
    virtual ~Quaternion();

public:
    /**
     * return the squared magnitude of this quaternion.
     * 
     * @return [description]
     */
    float magnitudeSquared() const;

    /**
     * return the magnitude of this quaternion. basically sqrt
     * 
     * @return [description]
     */
    float magnitude() const;

    /**
     * normalize
     * 
     * @return [description]
     */
    Quaternion normalize() const;

    /**
     * Returns the euler angle representation of the rotation.
     * 
     * @return [description]
     */
    Vector3 getEulerAngles() const;

    /**
     * Set x, y, z and w components of an existing Quaternion.
     * 
     * @param new_x [description]
     * @param new_y [description]
     * @param new_z [description]
     * @param new_w [description]
     */
    void set(float new_x, float new_y, float new_z, float new_w);

    /**
     * Creates a rotation which rotates from fromDirection to toDirection.
     * 
     * @param fromDirection [description]
     * @param toDirection   [description]
     */
    void setFromToRotation(const Vector3& fromDirection, const Vector3& toDirection);

    /**
     * Creates a rotation with the specified forward and upwards directions.
     *
     * The result is applied to this quaternion If used to orient a Transform, 
     * the Z axis will be aligned with forward and the Y axis with upwards, 
     * assuming these vectors are orthogonal. Logs an error if the forward direction is zero.
     * 
     * @param view 
     *        The direction to look in.
     */
    void setLookRotation(const Vector3& view);
    void setLookRotation(const Vector3& view, const Vector3& up);

    /**
     * Converts a rotation to angle-axis representation.
     * 
     * @param angle [description]
     * @param axis  [description]
     */
    void toAngleAxis(float angle, const Vector3& axis) const;

    /**
     * Adds this quaternion to another.
     * 
     * @param  q [description]
     * @return   [description]
     */
    Quaternion add(const Quaternion& q) const;

    /**
     * subtract
     * 
     * @param  q [description]
     * @return   [description]
     */
    Quaternion subtract(const Quaternion& q) const;

    /**
     * multiply
     * 
     * @param  scalar [description]
     * @return        [description]
     */
    Quaternion multiply(float scalar) const;

    /**
     * multiply
     * 
     * @param  q [description]
     * @return   [description]
     */
    Quaternion multiply(const Quaternion& q) const;

public:
    float x;
    float y;
    float z;
    float w;
};//Quaternion

EndPackage4 //(com, dragon3d, util, math)

#endif //Quaternion_Math_Util_Dragon3d_Com_H
