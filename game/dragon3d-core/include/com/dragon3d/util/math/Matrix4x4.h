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


#ifndef Matrix4x4_Math_Util_Dragon3d_Com_H
#define Matrix4x4_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Quaternion.h>

BeginPackage4(com, dragon3d, util, math)

Import dragon::lang;
Import com::dragon3d::util::math;

/**
 * A standard 4x4 transformation matrix.
 * 
 */
class _DragonExport Matrix4x4 extends(Object) {
public:
    /**
     * Returns the identity matrix
     */
    const static Matrix4x4 IDENTITY;

    /**
     * Returns a matrix with all elements set to zero
     */
    const static Matrix4x4 ZERO;

public:
    /**
     * Multiplies two matrices.
     *
     * The returned result is lhs * rhs.
     * 
     * @param  matrixA [description]
     * @param  matrixB [description]
     * @return         [description]
     */
    static Matrix4x4 multiply(const Matrix4x4& matrixA, const Matrix4x4& matrixB);

    /**
     * Creates an orthogonal projection matrix.
     *
     * The returned matrix is such that views left to right, bottom to top area, with zNear and zFar depth clipping planes.
     * 
     * @param  left   [description]
     * @param  right  [description]
     * @param  bottom [description]
     * @param  top    [description]
     * @param  zNear  [description]
     * @param  zFar   [description]
     * @return        [description]
     */
    static Matrix4x4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);

    /**
     * Creates a frustum matrix.
     * 
     * @param  left   [description]
     * @param  right  [description]
     * @param  bottom [description]
     * @param  top    [description]
     * @param  zNear  [description]
     * @param  zFar   [description]
     * @return        [description]
     */
    static Matrix4x4 frustum(float left, float right, float bottom, float top, float zNear, float zFar);

    /**
     * Creates a perspective projection matrix.
     *
     * fov is the vertical field-of-view in degrees of the perspective matrix, aspect is the aspect ratio (width divided by height). zNear and zFar set up the depth clipping planes.
     * 
     * @param  fov    [description]
     * @param  aspect [description]
     * @param  zNear  [description]
     * @param  zFar   [description]
     * @return        [description]
     */
    static Matrix4x4 perspective(float fov, float aspect, float zNear, float zFar);

    /**
     * create a lookAt matrix.
     * 
     * @param  view [description]
     * @param  up   [description]
     * @return      [description]
     */
    static Matrix4x4 lookAt(
        float eyex, float eyey, float eyez, 
        float centerx,float centery, float centerz, 
        float upx, float upy, float upz
    );
    static Matrix4x4 lookAt(const Vector3& eye, const Vector3& view, const Vector3& up);

    /**
     * Creates a translation, rotation and scaling matrix.
     * 
     * @param  pos [description]
     * @param  q   [description]
     * @param  s   [description]
     * @return     [description]
     */
    static Matrix4x4 TRS(const Vector3& pos, const Quaternion& q, const Vector3& s);


//---------------------------------------------------
public:
    Matrix4x4();
    Matrix4x4(float* f4x4);
    Matrix4x4(const Matrix4x4& matrix);
    Matrix4x4(
        float x11, float x12, float x13, float x14,
        float x21, float x22, float x23, float x24,
        float x31, float x32, float x33, float x34,
        float x41, float x42, float x43, float x44
    );

public:
    Matrix4x4& operator= (const Matrix4x4& matrix);

public:
    /**
     * get The inverse of this matrix
     * 
     * @return [description]
     */
    Matrix4x4 inverse() const;

    /**
     * Returns the transpose of this matrix
     * 
     * @return [description]
     */
    Matrix4x4 transpose() const;

    /**
     * Multiplies this matrices.
     * 
     * @param  matrix [description]
     * @return        [description]
     */
    Matrix4x4 multiply(const Matrix4x4& matrix) const;

    /**
     * translate the matrix
     * 
     * @param  tx [description]
     * @param  ty [description]
     * @param  tz [description]
     * @return    [description]
     */
    Matrix4x4 translate(float tx, float ty, float tz) const;
    Matrix4x4 translate(const Vector3& t) const;

    /**
     * ratate the matrix.
     * 
     * @param  angle [description]
     * @param  x     [description]
     * @param  y     [description]
     * @param  z     [description]
     * @return       [description]
     */
    Matrix4x4 rotate(float angle, float x, float y, float z) const;
    Matrix4x4 rotate(const Quaternion& q) const;
    Matrix4x4 rotate(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) const;

    /**
     * scale the matrix
     * 
     * @param  v [description]
     * @return   [description]
     */
    Matrix4x4 scale(float x, float y, float z) const;
    Matrix4x4 scale(const Vector3& v) const;


public:
    /**
     * get translation
     * 
     * @return [description]
     */
    Vector3 getTranslation() const;

    /**
     * get quaternion
     * 
     * @return [description]
     */
    Quaternion getQuaternion() const;

public:
    virtual String* toString() const;

public:
    const float* getData() const;
    const Array<float> toFloatArray() const;

public:
    float m[4][4];
    
};//Matrix4x4

EndPackage4 //(com, dragon3d, util, math)

#endif //Matrix4x4_Math_Util_Dragon3d_Com_H
