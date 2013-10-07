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


#include <com/dragon3d/util/math/Matrix4x4.h>
#include <com/dragon3d/util/math/Mathf.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>
 
Import com::dragon3d::util::math;

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

    Matrix4x4 ortho;

    if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f))
        return Matrix4x4::ZERO;

    memset(&ortho, 0x0, sizeof(Matrix4x4));

    ortho.m[0][0] = 1.0f;
    ortho.m[1][1] = 1.0f;
    ortho.m[2][2] = 1.0f;
    ortho.m[3][3] = 1.0f;

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

    memset(&frust, 0x0, sizeof(Matrix4x4));

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

Matrix4x4 Matrix4x4::TRS(const Vector3& pos, const Quaternion& q, const Vector3& s) {
    Matrix4x4 result = Matrix4x4::IDENTITY;

    result = result.translate(pos);
    result = result.rotate(q);
    result = result.scale(s);

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

Matrix4x4 Matrix4x4::translate(float tx, float ty, float tz) const {
    Matrix4x4 result = Matrix4x4::IDENTITY;

    result.m[3][0] += (this->m[0][0] * tx + this->m[1][0] * ty + this->m[2][0] * tz);
    result.m[3][1] += (this->m[0][1] * tx + this->m[1][1] * ty + this->m[2][1] * tz);
    result.m[3][2] += (this->m[0][2] * tx + this->m[1][2] * ty + this->m[2][2] * tz);
    result.m[3][3] += (this->m[0][3] * tx + this->m[1][3] * ty + this->m[2][3] * tz);

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

    Matrix4x4 rotMat;

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

Matrix4x4 Matrix4x4::scale(float sx, float sy, float sz) const {
    Matrix4x4 scaleMat = Matrix4x4::IDENTITY;

    scaleMat.m[0][0] *= sx;
    scaleMat.m[0][1] *= sx;
    scaleMat.m[0][2] *= sx;
    scaleMat.m[0][3] *= sx;

    scaleMat.m[1][0] *= sy;
    scaleMat.m[1][1] *= sy;
    scaleMat.m[1][2] *= sy;
    scaleMat.m[1][3] *= sy;

    scaleMat.m[2][0] *= sz;
    scaleMat.m[2][1] *= sz;
    scaleMat.m[2][2] *= sz;
    scaleMat.m[2][3] *= sz;

    return multiply(scaleMat);
}

Matrix4x4 Matrix4x4::scale(const Vector3& v) const {
    return this->scale(v.x, v.y, v.z);
}

/*
string Matrix4x4::toString(){
    char buf[256];
    
    string sb;
    sb.append("Matrix4x4 [\r\n");

    for (int i=0; i<4; i++) {
        memset(buf, 0, sizeof(char) * 256);
        sprintf(buf, "    [%.2f, %.2f, %.2f, %.2f],\r\n", m[i][0], m[i][1], m[i][2], m[i][3]);
        sb.append(buf);
    }

    sb.append("]\r\n");

    return sb;
}
*/

