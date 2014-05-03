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

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <dragon/lang/StringBuffer.h>
#include <com/dragon3d/util/math/Matrix4x4.h>
#include <com/dragon3d/util/math/Mathf.h>

Import com::dragon3d::util::math;

const Type* Matrix4x4::TYPE = TypeOf<Matrix4x4>();

const Matrix4x4 Matrix4x4::IDENTITY = Matrix4x4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

const Matrix4x4 Matrix4x4::ZERO = Matrix4x4(
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
);

Matrix4x4 Matrix4x4::multiply(const Matrix4x4& matrixA, const Matrix4x4& matrixB){
    return matrixA.multiply(matrixB);
}

Matrix4x4 Matrix4x4::ortho(float left, float right, float bottom, float top, float nearZ, float farZ) {
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;

    Matrix4x4 ortho = Matrix4x4::IDENTITY;

    ortho.m[0][0] = 2.0f / deltaX;
    ortho.m[3][0] = -(right + left) / deltaX;
    ortho.m[1][1] = 2.0f / deltaY;
    ortho.m[3][1] = -(top + bottom) / deltaY;
    ortho.m[2][2] = -2.0f / deltaZ;
    ortho.m[3][2] = -(nearZ + farZ) / deltaZ;

    return ortho;
}

Matrix4x4 Matrix4x4::frustum(float left, float right, float bottom, float top, float nearZ, float farZ) {
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;

    Matrix4x4 frust;

    if ((nearZ <= 0.0f) || (farZ <= 0.0f) ||
         (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f))
         return Matrix4x4::ZERO;

    frust.m[0][0] = 2.0f * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

    frust.m[1][1] = 2.0f * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

    frust.m[2][0] = (right + left) / deltaX;
    frust.m[2][1] = (top + bottom) / deltaY;
    frust.m[2][2] = -(nearZ + farZ) / deltaZ;
    frust.m[2][3] = -1.0f;

    frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

    return frust;
}

Matrix4x4 Matrix4x4::perspective(float fovy, float aspect, float zNear, float zFar) {
   float frustumW, frustumH;
  
   frustumH = tanf(fovy / 360.0f * Mathf::PI) * zNear;
   frustumW = frustumH * aspect;

   return frustum(-frustumW, frustumW, -frustumH, frustumH, zNear, zFar);
}


Matrix4x4 Matrix4x4::lookAt(float eyex, float eyey, float eyez, float centerx,
    float centery, float centerz, float upx, float upy, float upz)
{
    Matrix4x4 result = Matrix4x4::IDENTITY;

    
    Vector3 forward;
    Vector3 side;
    Vector3 up;

    Matrix4x4 view = Matrix4x4::IDENTITY;

    forward.x = centerx - eyex;
    forward.y = centery - eyey;
    forward.z = centerz - eyez;

    up.x = upx;
    up.y = upy;
    up.z = upz;

    forward = forward.normalize();

    // Side = forward x up
    side = Vector3::cross(forward, up);
    side = side.normalize();

    // Recompute up as: up = side x forward
    up = Vector3::cross(side, forward);

    view.m[0][0] = side.x; view.m[1][0] = side.y; view.m[2][0] = side.z;
    view.m[0][1] = up.x; view.m[1][1] = up.y; view.m[2][1] = up.z;
    view.m[0][2] = -forward.x; view.m[1][2] = -forward.y; view.m[2][2] = -forward.z;

    result = result.translate(-eyex, -eyey, -eyez);
    result = result.multiply(view);
   
    return result;
}

Matrix4x4 Matrix4x4::lookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {
    return lookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}

Matrix4x4 Matrix4x4::TRS(const Vector3& pos, const Quaternion& q, const Vector3& s) {
    Matrix4x4 result = Matrix4x4::IDENTITY;

    result = result.scale(s);
    result = result.rotate(q);
    result = result.translate(pos);

    return result;
}

// ------------------------------------------------------
Matrix4x4::Matrix4x4(void){
    memset(this, 0x0, sizeof(Matrix4x4));
}

Matrix4x4::Matrix4x4(float* f4x4){
    for (int i=0; i<16; i++) {
        m[i / 4][i % 4] = f4x4[i];
    }
}

Matrix4x4::Matrix4x4(const Matrix4x4& matrix) {
    memcpy(this->m, matrix.m, sizeof(float) * 16);
}

Matrix4x4::Matrix4x4(
        float x11, float x12, float x13, float x14,
        float x21, float x22, float x23, float x24,
        float x31, float x32, float x33, float x34,
        float x41, float x42, float x43, float x44
    ) {
    m[0][0] = x11; m[0][1] = x12; m[0][2] = x13; m[0][3] = x14;
    m[1][0] = x21; m[1][1] = x22; m[1][2] = x23; m[1][3] = x24;
    m[2][0] = x31; m[2][1] = x32; m[2][2] = x33; m[2][3] = x34;
    m[3][0] = x41; m[3][1] = x42; m[3][2] = x43; m[3][3] = x44;
}

Matrix4x4& Matrix4x4::operator= (const Matrix4x4& matrix) {
    memcpy(this->m, matrix.m, sizeof(float) * 16);
    return *this;
}

// -------------------------------------------------------

Matrix4x4 Matrix4x4::inverse() const {
  int i,j,k;               
  int pvt_i[4], pvt_j[4];      /* Locations of pivot elements */
  float pvt_val;               /* Value of current pivot element */
  float hold;                  /* Temporary storage */
  float determinat;            

  Matrix4x4 result = *this;

  determinat = 1.0f;

  for (k=0; k<4; k++)  {
    /* Locate k'th pivot element */
    pvt_val=result.m[k][k];            /* Initialize for search */
    pvt_i[k]=k;
    pvt_j[k]=k;

    for (i=k; i<4; i++) {
      for (j=k; j<4; j++) {
        if (fabs(result.m[i][j]) > fabs(pvt_val)) {
          pvt_i[k]=i;
          pvt_j[k]=j;
          pvt_val=result.m[i][j];
        }
      }
    }

    /* Product of pivots, gives determinant when finished */
    determinat*=pvt_val;
    if (fabs(determinat)<Mathf::EPSILON) {    
        return Matrix4x4::ZERO;  /* Matrix is singular (zero determinant) */
    }

    /* "Interchange" rows (with sign change stuff) */
    i=pvt_i[k];
    if (i!=k) {               /* If rows are different */
      for (j=0; j<4; j++) {
        hold=-result.m[k][j];
        result.m[k][j]=result.m[i][j];
        result.m[i][j]=hold;
      }
    }

    /* "Interchange" columns */
    j=pvt_j[k];
    if (j!=k) {              /* If columns are different */
      for (i=0; i<4; i++) {
        hold=-result.m[i][k];
        result.m[i][k]=result.m[i][j];
        result.m[i][j]=hold;
      }
    }
    
    /* Divide column by minus pivot value */
    for (i=0; i<4; i++) {
      if (i!=k) result.m[i][k]/=( -pvt_val) ; 
    }

    /* Reduce the matrix */
    for (i=0; i<4; i++) {
      hold = result.m[i][k];
      for (j=0; j<4; j++) {
        if (i!=k && j!=k) result.m[i][j]+=hold*result.m[k][j];
      }
    }

    /* Divide row by pivot */
    for (j=0; j<4; j++) {
      if (j!=k) result.m[k][j]/=pvt_val;
    }

    /* Replace pivot by reciprocal (at last we can touch it). */
    result.m[k][k] = 1.0f/pvt_val;
  }

  /* That was most of the work, one final pass of row/column interchange */
  /* to finish */
  for (k=4-2; k>=0; k--) { /* Don't need to work with 1 by 1 corner*/
    i=pvt_j[k];            /* Rows to swap correspond to pivot COLUMN */
    if (i!=k) {            /* If rows are different */
      for(j=0; j<4; j++) {
        hold = result.m[k][j];
        result.m[k][j]=-result.m[i][j];
        result.m[i][j]=hold;
      }
    }

    j=pvt_i[k];           /* Columns to swap correspond to pivot ROW */
    if (j!=k)             /* If columns are different */
    for (i=0; i<4; i++) {
      hold=result.m[i][k];
      result.m[i][k]=-result.m[i][j];
      result.m[i][j]=hold;
    }
  }
    
  return result;
}


Matrix4x4 Matrix4x4::transpose() const {
    Matrix4x4 result = *this;

    result.m[0][0] = this->m[0][0];
    result.m[0][1] = this->m[1][0];
    result.m[0][2] = this->m[2][0];
    result.m[0][3] = this->m[3][0];

    result.m[1][0] = this->m[0][1];
    result.m[1][1] = this->m[1][1];
    result.m[1][2] = this->m[2][1];
    result.m[1][3] = this->m[3][1];

    result.m[2][0] = this->m[0][2];
    result.m[2][1] = this->m[1][2];
    result.m[2][2] = this->m[2][2];
    result.m[2][3] = this->m[3][2];

    result.m[3][0] = this->m[0][3];
    result.m[3][1] = this->m[1][3];
    result.m[3][2] = this->m[2][3];
    result.m[3][3] = this->m[3][3];

    return result;
}

Matrix4x4 Matrix4x4::multiply(const Matrix4x4& matrix) const {
    const Matrix4x4* srcA = this;
    const Matrix4x4* srcB = &matrix;

    Matrix4x4 result;

    for (int i=0; i<4; i++){
        result.m[i][0] =  (srcA->m[i][0] * srcB->m[0][0]) +
                          (srcA->m[i][1] * srcB->m[1][0]) +
                          (srcA->m[i][2] * srcB->m[2][0]) +
                          (srcA->m[i][3] * srcB->m[3][0]) ;

        result.m[i][1] =  (srcA->m[i][0] * srcB->m[0][1]) + 
                          (srcA->m[i][1] * srcB->m[1][1]) +
                          (srcA->m[i][2] * srcB->m[2][1]) +
                          (srcA->m[i][3] * srcB->m[3][1]) ;

        result.m[i][2] =  (srcA->m[i][0] * srcB->m[0][2]) + 
                          (srcA->m[i][1] * srcB->m[1][2]) +
                          (srcA->m[i][2] * srcB->m[2][2]) +
                          (srcA->m[i][3] * srcB->m[3][2]) ;

        result.m[i][3] =  (srcA->m[i][0] * srcB->m[0][3]) + 
                          (srcA->m[i][1] * srcB->m[1][3]) +
                          (srcA->m[i][2] * srcB->m[2][3]) +
                          (srcA->m[i][3] * srcB->m[3][3]) ;
    }

    return result;
}

Matrix4x4 Matrix4x4::multiply(float scalar) const {
    Matrix4x4 result = *this;

    result.m[0][0] *= scalar;
    result.m[0][1] *= scalar;
    result.m[0][2] *= scalar;
    result.m[0][3] *= scalar;

    result.m[1][0] *= scalar;
    result.m[1][1] *= scalar;
    result.m[1][2] *= scalar;
    result.m[1][3] *= scalar;

    result.m[2][0] *= scalar;
    result.m[2][1] *= scalar;
    result.m[2][2] *= scalar;
    result.m[2][3] *= scalar;

    result.m[3][0] *= scalar;
    result.m[3][1] *= scalar;
    result.m[3][2] *= scalar;
    result.m[3][3] *= scalar;

    return result;
}

Matrix4x4 Matrix4x4::translate(float tx, float ty, float tz) const {
    Matrix4x4 result = Matrix4x4::IDENTITY;

    result.m[3][0] = tx;
    result.m[3][1] = ty;
    result.m[3][2] = tz;

    return multiply(result);
}

Matrix4x4 Matrix4x4::translate(const Vector3& t) const {
    return translate(t.x, t.y, t.z);
}

Matrix4x4 Matrix4x4::rotate(float angle, float x, float y, float z) const {
   float sinAngle, cosAngle;
   float mag = sqrtf(x * x + y * y + z * z);
      
   sinAngle = sinf(angle * Mathf::PI / 180.0f);
   cosAngle = cosf(angle * Mathf::PI / 180.0f);

   if (mag > 0.0f){
      float xx, yy, zz, xy, yz, zx, xs, ys, zs;
      float oneMinusCos;

      Matrix4x4 rotMat;
   
      x /= mag;
      y /= mag;
      z /= mag;

      xx = x * x;
      yy = y * y;
      zz = z * z;
      xy = x * y;
      yz = y * z;
      zx = z * x;

      xs = x * sinAngle;
      ys = y * sinAngle;
      zs = z * sinAngle;

      oneMinusCos = 1.0f - cosAngle;

      rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
      rotMat.m[0][1] = (oneMinusCos * xy) - zs;
      rotMat.m[0][2] = (oneMinusCos * zx) + ys;
      rotMat.m[0][3] = 0.0f; 

      rotMat.m[1][0] = (oneMinusCos * xy) + zs;
      rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
      rotMat.m[1][2] = (oneMinusCos * yz) - xs;
      rotMat.m[1][3] = 0.0f;

      rotMat.m[2][0] = (oneMinusCos * zx) - ys;
      rotMat.m[2][1] = (oneMinusCos * yz) + xs;
      rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
      rotMat.m[2][3] = 0.0f; 

      rotMat.m[3][0] = 0.0f;
      rotMat.m[3][1] = 0.0f;
      rotMat.m[3][2] = 0.0f;
      rotMat.m[3][3] = 1.0f;

      return multiply(rotMat);
   } else {
      return Matrix4x4::ZERO;
   }
}

Matrix4x4 Matrix4x4::rotate(const Quaternion& q) const {
    float norm = q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z;
    float s = norm > 0.0 ? 2.0 / norm : 0.0;

    Matrix4x4 rotMat = Matrix4x4::IDENTITY;

    // compute xs/ys/zs first to save 6 multiplications, since xs/ys/zs
    // will be used 2-4 times each.
    float xs = q.x * s;
    float ys = q.y * s;
    float zs = q.z * s;

    float xx = q.x * xs;
    float xy = q.x * ys;
    float xz = q.x * zs;
    float xw = q.w * xs;
    float yy = q.y * ys;
    float yz = q.y * zs;
    float yw = q.w * ys;
    float zz = q.z * zs;
    float zw = q.w * zs;

    // using s=2/norm (instead of 1/norm) saves 9 multiplications by 2 here
    rotMat.m[0][0] = 1.0f - (yy + zz);
    rotMat.m[0][1] = xy - zw;
    rotMat.m[0][2] = xz + yw;
    rotMat.m[0][3] = 0.0f; 

    rotMat.m[1][0] = xy + zw;
    rotMat.m[1][1] = 1.0f - (xx + zz);
    rotMat.m[1][2] = yz - xw;
    rotMat.m[1][3] = 0.0f;

    rotMat.m[2][0] = xz - yw;
    rotMat.m[2][1] = yz + xw;
    rotMat.m[2][2] = 1.0 - (xx + yy);
    rotMat.m[2][3] = 0.0f; 

    rotMat.m[3][0] = 0.0f;
    rotMat.m[3][1] = 0.0f;
    rotMat.m[3][2] = 0.0f;
    rotMat.m[3][3] = 1.0f;

    return multiply(rotMat);;
}

Matrix4x4 Matrix4x4::rotate(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) const {
    Matrix4x4 temp = Matrix4x4::IDENTITY;

    temp.m[0][0] = xAxis.x; temp.m[0][1] = yAxis.x; temp.m[0][2] = zAxis.x;
    temp.m[1][0] = xAxis.y; temp.m[1][1] = yAxis.y; temp.m[1][2] = zAxis.y;
    temp.m[2][0] = xAxis.z; temp.m[2][1] = yAxis.z; temp.m[2][2] = zAxis.z;

    return multiply(temp);;
}


Matrix4x4 Matrix4x4::scale(float sx, float sy, float sz) const {
    Matrix4x4 tmp = Matrix4x4::IDENTITY;

    tmp.m[0][0] = sx;
    tmp.m[1][1] = sy;
    tmp.m[2][2] = sz;

    return multiply(tmp);
}

Matrix4x4 Matrix4x4::scale(const Vector3& v) const {
    return this->scale(v.x, v.y, v.z);
}

// -------------------------------------
Vector3 Matrix4x4::getTranslation() const {
    return Vector3(m[3][0], m[3][1], m[3][2]);
}


Quaternion Matrix4x4::getQuaternion() const {
    // Uses the Graphics Gems code, from
    // ftp://ftp.cis.upenn.edu/pub/graphics/shoemake/quatut.ps.Z
    // *NOT* the "Matrix and Quaternions FAQ", which has errors!

    // the trace is the sum of the diagonal elements; see
    // http://mathworld.wolfram.com/MatrixTrace.html
    float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2];
    float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2];
    float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2];

    float x, y, z, w;
    
    float t = m00 + m11 + m22;

    // we protect the division by s by ensuring that s>=1
    if (t >= 0) { // |w| >= .5
        float s = Mathf::sqrt(t + 1); // |s|>=1 ...
        w = 0.5 * s;
        s = 0.5 / s; // so this division isn't bad
        x = (m21 - m12) * s;
        y = (m02 - m20) * s;
        z = (m10 - m01) * s;
    } else if (m00 > m11 && m00 > m22) {
        float s = Mathf::sqrt(1.0 + m00 - m11 - m22); // |s|>=1
        x = s * 0.5; // |x| >= .5
        s = 0.5 / s;
        y = (m10 + m01) * s;
        z = (m02 + m20) * s;
        w = (m21 - m12) * s;
    } else if (m11 > m22) {
        float s = Mathf::sqrt(1.0 + m11 - m00 - m22); // |s|>=1
        y = s * 0.5; // |y| >= .5
        s = 0.5 / s;
        x = (m10 + m01) * s;
        z = (m21 + m12) * s;
        w = (m02 - m20) * s;
    } else {
        float s = Mathf::sqrt(1.0 + m22 - m00 - m11); // |s|>=1
        z = s * 0.5; // |z| >= .5
        s = 0.5 / s;
        x = (m02 + m20) * s;
        y = (m21 + m12) * s;
        w = (m10 - m01) * s;
    }

    return Quaternion(x, y, z, w);
}

Vector3 Matrix4x4::multiplyPoint(const Vector3& v) const {
    Vector3 store = Vector3::ZERO;

    float x = v.getX();
    float y = v.getY();
    float z = v.getZ();

    //store.setX(m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3]);
    //store.setY(m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3]);
    //store.setZ(m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3]);

    store.setX(m[0][0] * x + m[1][0] * y + m[2][0] * z + m[3][0]);
    store.setY(m[0][1] * x + m[1][1] * y + m[2][1] * z + m[3][1]);
    store.setZ(m[0][2] * x + m[1][2] * y + m[2][2] * z + m[3][2]);

    return store;
}

Vector3 Matrix4x4::multiplyVector(const Vector3& v) const {
    Vector3 store = Vector3::ZERO;

    float x = v.getX();
    float y = v.getY();
    float z = v.getZ();

    //store.setX(m[0][0] * x + m[0][1] * y + m[0][2] * z);
    //store.setY(m[1][0] * x + m[1][1] * y + m[1][2] * z);
    //store.setZ(m[2][0] * x + m[2][1] * y + m[2][2] * z);

    store.setX(m[0][0] * x + m[1][0] * y + m[2][0] * z);
    store.setY(m[0][1] * x + m[1][1] * y + m[2][1] * z);
    store.setZ(m[0][2] * x + m[1][2] * y + m[2][2] * z);

    return store;
}

const float* Matrix4x4::getData() const {
    return (float*)(&this->m[0][0]);
}

const Array<float> Matrix4x4::toFloatArray() const {
    return Array<float>(getData(), 16, false);
}

String* Matrix4x4::toString() const {
    StringBuffer* sb = new StringBuffer();

    sb->append("Matrix4x4 [\r\n");

    for (int i=0; i<4; i++) {
        String* tmp = String::format("    [%.2f, %.2f, %.2f, %.2f],\r\n", m[i][0], m[i][1], m[i][2], m[i][3]);
        sb->append(tmp);
        SafeRelease(tmp);
    }

    sb->append("]\r\n");

    String* ret = sb->toString();
    SafeRelease(sb);

    return ret;
}

