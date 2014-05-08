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


#ifndef Vector3_Math_Util_Dragon3d_Com_H
#define Vector3_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>

BeginPackage4(com, dragon3d, util, math)

Import dragon::lang;
Import com::dragon3d::util::math;

/**
 * Representation of 3D vectors and points.
 * 
 */
class _DragonExport Vector3 extends(Object) {
public:
    static const Type* TYPE;
    
public:
    static const Vector3 ZERO; //Shorthand for writing Vector3(0, 0, 0)
    static const Vector3 ONE; //Shorthand for writing Vector3(1, 1, 1)

    static const Vector3 FORWARD; //Shorthand for writing Vector3(0, 0, 1)
    static const Vector3 BACK; //Shorthand for writing Vector3(0, 0, -1)

    static const Vector3 UP; //Shorthand for writing Vector3(0, 1, 0)
    static const Vector3 DOWN; //Shorthand for writing Vector3(0, -1, 0)

    static const Vector3 RIGHT; //Shorthand for writing Vector3(1, 0, 0)
    static const Vector3 LEFT; //Shorthand for writing Vector3(-1, 0, 0)

public:
    /**
     * Returns the angle in degrees between from and to. This is always the smallest.
     * 
     * @param  from [description]
     * @param  to   [description]
     * @return      [description]
     */
    static float angle(const Vector3& from, const Vector3& to);

    /**
     * Returns a copy of vector with its magnitude clamped to maxLength.
     * 
     * @param  vector    [description]
     * @param  maxLength [description]
     * @return           [description]
     */
    static Vector3 clampMagnitude(const Vector3& vector, float maxLength);

    /**
     * Cross Product of two vectors.
     * 
     * The cross product of two vectors results in a third vector which is perpendicular 
     * to the two input vectors. The result's magnitude is equal to the magnitudes of the two 
     * inputs multiplied together and then multiplied by the sine of the angle between the inputs. 
     * You can determine the direction of the result vector using the "left hand rule".
     * 
     * @param  lhs [description]
     * @param  rhs [description]
     * @return     [description]
     */
    static Vector3 cross(const Vector3& lhs, const Vector3& rhs);

    /**
     * Returns the distance between a and b.
     * 
     * @param  a [description]
     * @param  b [description]
     * @return   [description]
     */
    static float distance(const Vector3& a, const Vector3& b);

    /**
     * Linearly interpolates between two vectors.
     *
     * Interpolates between from and to by the fraction t. This is most commonly used to find a point 
     * some fraction of the way along a line between two endpoints (eg, to move an object gradually 
     * between those points). This fraction is clamped to the range [0...1]. When t = 0 returns from. 
     * When t = 1 returns to. When t = 0.5 returns the point midway between from and to.
     * 
     * @param  from [description]
     * @param  to   [description]
     * @param  t    [description]
     * @return      [description]
     */
    static Vector3 lerp(const Vector3& from, const Vector3& to, float t);

    /**
     * Returns a vector that is made from the largest components of two vectors.
     * 
     * @param  lhs [description]
     * @param  rhs [description]
     * @return     [description]
     */
    static Vector3 max(const Vector3& lhs, const Vector3& rhs);

    /**
     * Returns a vector that is made from the smallest components of two vectors.
     * 
     * @param  lhs [description]
     * @param  rhs [description]
     * @return     [description]
     */
    static Vector3 min(const Vector3& lhs, const Vector3& rhs);

    /**
     * Retures a vector that is centre of two vectors.
     * 
     * @param  lhs [description]
     * @param  rhs [description]
     * @return     [description]
     */
    static Vector3 centre(const Vector3& lhs, const Vector3& rhs);

    /**
     * Moves a point current in a straight line towards a target point.
     *
     * The value returned by this function is a point maxDistanceDelta units closer to 
     * a target point along a line between current and target. If the target is closer 
     * than maxDistanceDelta then the returned value will be equal to target (ie, 
     * the movement will not overshoot the target). Negative values of maxDistanceDelta 
     * can be used to push the point away from the target.
     * 
     * @param  current          [description]
     * @param  target           [description]
     * @param  maxDistanceDelta [description]
     * @return                  [description]
     */
    static Vector3 moveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);

    /**
     * Makes vectors normalized and orthogonal to each other.
     *
     * Normalizes normal. Normalizes tangent and makes sure it is orthogonal to normal (that is, angle between 
     * them is 90 degrees).
     * 
     * @param normal  [description]
     * @param tangent [description]
     */
    static void orthoNormalize(const Vector3& normal, const Vector3& tangent);

    /**
     * Makes vectors normalized and orthogonal to each other.
     *
     * Normalizes normal. Normalizes tangent and makes sure it is orthogonal to normal. Normalizes binormal 
     * and makes sure it is orthogonal to both normal and tangent.
     *
     * Points in space are usually specified with coordinates in the standard XYZ axis system. However, 
     * you can interpret any three vectors as "axes" if they are normalized (ie, have a magnitude of 1) 
     * and are orthogonal (ie, perpendicular to each other).
     *
     * Creating your own coordinate axes is useful, say, if you want to scale a mesh in arbitrary directions 
     * rather than just along the XYZ axes - you can transform the vertices to your own coordinate system, 
     * scale them and then transform back. Often, a transformation like this will be carried out along only 
     * one axis while the other two are either left as they are or treated equally. For example, a stretching 
     * effect can be applied to a mesh by scaling up on one axis while scaling down proportionally on the other 
     * two. This means that once the first axis vector is specified, it doesn't greatly matter what the other 
     * two are as long as they are normalized and orthogonal. OrthoNormalize can be used to ensure the first 
     * vector is normal and then generate two normalized, orthogonal vectors for the other two axes.
     * 
     * @param normal   [description]
     * @param tangent  [description]
     * @param binormal [description]
     */
    static void orthoNormalize(const Vector3& normal, const Vector3& tangent, const Vector3& binormal);

    /**
     * Projects a vector onto another vector.
     *
     * To understand vector projection, imagine that onNormal is resting on a line pointing 
     * in its direction. Somewhere along that line will be the nearest point to the tip of vector. 
     * The projection is just onNormal rescaled so that it reaches that point on the line.
     *
     * The function will return a zero vector if onNormal is almost zero.
     *
     * An example of the usage of projection is a rail-mounted gun that should slide so that it 
     * gets as close as possible to a target object. The projection of the target heading along 
     * the direction of the rail can be used to move the gun by applying a force to a rigidbody, say.
     * 
     * @param  vector   [description]
     * @param  onNormal [description]
     * @return          [description]
     */
    static Vector3 project(const Vector3& vector, const Vector3& onNormal);

    /**
     * Reflects a vector off the plane defined by a normal.
     *
     * The inNormal vector defines a plane (a plane's normal is the vector that is perpendicular 
     * to its surface). the inDirection vector is treated as a directional arrow coming in to the plane. 
     * The returned value is a vector of equal magnitude to inDirection but with its direction reflected.
     * 
     * @param  inDirection [description]
     * @param  inNormal    [description]
     * @return             [description]
     */
    static Vector3 reflect(const Vector3& inDirection, const Vector3& inNormal);

    /**
     * Rotates a vector current towards target.
     *
     * This function is similar to MoveTowards except that the vector is treated as a direction rather 
     * than a position. The current vector will be rotated round toward the target direction by an angle 
     * of maxRadiansDelta, although it will land exactly on the target rather than overshoot. If the 
     * magnitudes of current and target are different then the magnitude of the result will be linearly 
     * interpolated during the rotation. If a negative value is used for maxRadiansDelta, the vector will 
     * rotate away from target until it is pointing in exactly the opposite direction, then stop.
     * 
     * @param  current           [description]
     * @param  target            [description]
     * @param  maxRadiansDelta   [description]
     * @param  maxMagnitudeDelta [description]
     * @return                   [description]
     */
    static Vector3 rotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta);

    /**
     * Multiplies two vectors component-wise.
     *
     * Every component in the result is a component of a multiplied by the same component of b.
     * 
     * @param  a [description]
     * @param  b [description]
     * @return   [description]
     */
    static Vector3 scale(const Vector3& a, const Vector3& b);

    /**
     * [divideScale description]
     * 
     * @param  a [description]
     * @param  b [description]
     * @return   [description]
     */
    static Vector3 divideScale(const Vector3& a, const Vector3& b);

    /**
     * Spherically interpolates between two vectors.
     *
     * Interpolates between from and to by amount t. The difference between this and linear interpolation (aka, "lerp")
     * is that the vectors are treated as directions rather than points in space. The direction of the returned 
     * vector is interpolated by the angle and its magnitude is interpolated between the magnitudes of from and to.
     * 
     * @param  from [description]
     * @param  to   [description]
     * @param  t    [description]
     * @return      [description]
     */
    static Vector3 slerp(const Vector3& from, const Vector3& to, float t);

    /**
     * Gradually changes a vector towards a desired goal over time.
     *
     * The vector is smoothed by some spring-damper like function, which will never overshoot. The most common use 
     * is for smoothing a follow camera.
     * 
     * @param  current         [description]
     * @param  target          [description]
     * @param  currentVelocity [description]
     * @param  smoothTime      [description]
     * @return                 [description]
     */
    static Vector3 smoothDamp(const Vector3& current, const Vector3& target, const Vector3& currentVelocity, float smoothTime);
    static Vector3 smoothDamp(const Vector3& current, const Vector3& target, const Vector3& currentVelocity, float smoothTime, float maxSpeed);
    static Vector3 smoothDamp(const Vector3& current, const Vector3& target, const Vector3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

//----------------------------------------------------------------
public:
    Vector3(void);
    Vector3(float x, float y);
    Vector3(float x, float y, float z);
    Vector3(const Vector3& a);

public:
    Vector3& operator= (const Vector3& v);

    bool operator==(const Vector3& a) const;
    bool operator!=(const Vector3& a) const;

public: // Propertys
    /**
     * get and set x.
     * 
     * @return [description]
     */
    float getX() const {return this->x; };
    void setX(float x) {this->x = x; };
    /**
     * get ans set y.
     * 
     * @return [description]
     */
    float getY() const {return this->y; };
    void setY(float y) {this->y = y; };
    /**
     * get and set z.
     * 
     * @return [description]
     */
    float getZ() const {return this->z; };
    void setZ(float z) {this->z = z; };

public:
    /**
     * Returns the length of this vector 
     * 
     * @return [description]
     */
    float length() const;

    /**
     * Returns the squared length of this vector 
     *
     * The magnitude of a vector v is calculated as Mathf.Sqrt(Vector3.Dot(v, v)). 
     * However, the Sqrt calculation is quite complicated and takes longer to execute 
     * than the normal arithmetic operations. Calculating the squared magnitude 
     * instead of using the magnitude property is much faster - the calculation 
     * is basically the same only without the slow Sqrt call. If you are using 
     * magnitudes simply to compare distances, then you can just as well compare 
     * squared magnitudes against the squares of distances since the comparison 
     * will give the same result.
     * 
     * @return [description]
     */
    float lengthSquared() const;

    /**
     * Returns this vector with a magnitude of 1
     *
     * When normalized, a vector keeps the same direction but its length is 1.0.
     *
     * Note that the current vector is unchanged and a new normalized vector is returned. 
     * If you want to normalize the current vector, use Normalize function.
     * 
     * @return [description]
     */
    Vector3 normalize() const;

    /**
     * add this vector with a new Vector3 a, and return a new Vector3.
     * 
     * @param  a [description]
     * @return   [description]
     */
    Vector3 add(const Vector3& a) const;

    /**
     * add this vector with a new Vector3 a, and return a new Vector3.
     * 
     * @param  a [description]
     * @return   [description]
     */
    Vector3 substract(const Vector3& a) const;

    /**
     * Multiplies this vector by a number, and return new Vector3.
     * 
     * @param  d [description]
     * @return   [description]
     */
    Vector3 multiply(float scalar) const;


    /**
     * Multiplies this vector by a number, and return new Vector3.
     * 
     * @param  d [description]
     * @return   [description]
     */
    Vector3 divide(float scalar) const;

    /**
     * dot multiply
     * 
     * @param  b [description]
     * @return   [description]
     */
    float dot(const Vector3& a) const;

    /**
     * negate the vector3
     * 
     * @return [description]
     */
    Vector3 negate() const;

    /**
     * Set x, y and z components of an existing Vector3.
     * 
     * @param new_x [description]
     * @param new_y [description]
     * @param new_z [description]
     */
    void set(float new_x, float new_y, float new_z);

    /**
     * get value by index.
     * 
     * @param  index [description]
     * @return       [description]
     */
    float getValue(int index);

    /**
     * set value by index.
     * 
     * @param index [description]
     * @param value [description]
     */
    void setValue(int index, float value);

    /**
     * build the Vector3 info.
     * 
     * @return [description]
     */
    String* toString() const;

public:
    const float* getData() const;
    const Array<float> toFloatArray() const;

public:
    float x; //X component of the vector.
    float y; //Y component of the vector.
    float z; //Z component of the vector.
};//Vector3

EndPackage4 //(com, dragon3d, util, math)

#endif //Vector3_Math_Util_Dragon3d_Com_H
