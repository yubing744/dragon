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

Matrix4x4 Matrix4x4::multiply(const Matrix4x4& matrixA, const Matrix4x4& matrixB){
    const Matrix4x4* srcA = &matrixA;
    const Matrix4x4* srcB = &matrixB;

    Matrix4x4 result;

    for (int i=0; i<4; i++){
        result.m[i][0] =    (srcA->m[i][0] * srcB->m[0][0]) +
                            (srcA->m[i][1] * srcB->m[1][0]) +
                            (srcA->m[i][2] * srcB->m[2][0]) +
                            (srcA->m[i][3] * srcB->m[3][0]) ;

        result.m[i][1] =    (srcA->m[i][0] * srcB->m[0][1]) + 
                            (srcA->m[i][1] * srcB->m[1][1]) +
                            (srcA->m[i][2] * srcB->m[2][1]) +
                            (srcA->m[i][3] * srcB->m[3][1]) ;

        result.m[i][2] =    (srcA->m[i][0] * srcB->m[0][2]) + 
                            (srcA->m[i][1] * srcB->m[1][2]) +
                            (srcA->m[i][2] * srcB->m[2][2]) +
                            (srcA->m[i][3] * srcB->m[3][2]) ;

        result.m[i][3] =    (srcA->m[i][0] * srcB->m[0][3]) + 
                            (srcA->m[i][1] * srcB->m[1][3]) +
                            (srcA->m[i][2] * srcB->m[2][3]) +
                            (srcA->m[i][3] * srcB->m[3][3]) ;
    }

    return result;
}


Matrix4x4::Matrix4x4(void){
    memset(this, 0x0, sizeof(Matrix4x4));
}

Matrix4x4::Matrix4x4(float* f4x4){
    for (int i=0; i<16; i++) {
        m[i / 4][i % 4] = f4x4[i];
    }
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


void Matrix4x4::identity() {
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
    m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}

Matrix4x4 Matrix4x4::multiply(const Matrix4x4& matrix){
    return Matrix4x4::multiply(*this, matrix);
}

bool Matrix4x4::inverse(){
  int i,j,k;               
  int pvt_i[4], pvt_j[4];        /* Locations of pivot elements */
  float pvt_val;               /* Value of current pivot element */
  float hold;                  /* Temporary storage */
  float determinat;            

  determinat = 1.0f;
  for (k=0; k<4; k++)  {
    /* Locate k'th pivot element */
    pvt_val=m[k][k];            /* Initialize for search */
    pvt_i[k]=k;
    pvt_j[k]=k;
    for (i=k; i<4; i++) {
      for (j=k; j<4; j++) {
        if (fabs(m[i][j]) > fabs(pvt_val)) {
          pvt_i[k]=i;
          pvt_j[k]=j;
          pvt_val=m[i][j];
        }
      }
    }

    /* Product of pivots, gives determinant when finished */
    determinat*=pvt_val;
    if (fabs(determinat)<Mathf::EPSILON) {    
      return(false);  /* Matrix is singular (zero determinant) */
    }

    /* "Interchange" rows (with sign change stuff) */
    i=pvt_i[k];
    if (i!=k) {               /* If rows are different */
      for (j=0; j<4; j++) {
        hold=-m[k][j];
        m[k][j]=m[i][j];
        m[i][j]=hold;
      }
    }

    /* "Interchange" columns */
    j=pvt_j[k];
    if (j!=k) {              /* If columns are different */
      for (i=0; i<4; i++) {
        hold=-m[i][k];
        m[i][k]=m[i][j];
        m[i][j]=hold;
      }
    }
    
    /* Divide column by minus pivot value */
    for (i=0; i<4; i++) {
      if (i!=k) m[i][k]/=( -pvt_val) ; 
    }

    /* Reduce the matrix */
    for (i=0; i<4; i++) {
      hold = m[i][k];
      for (j=0; j<4; j++) {
        if (i!=k && j!=k) m[i][j]+=hold*m[k][j];
      }
    }

    /* Divide row by pivot */
    for (j=0; j<4; j++) {
      if (j!=k) m[k][j]/=pvt_val;
    }

    /* Replace pivot by reciprocal (at last we can touch it). */
    m[k][k] = 1.0f/pvt_val;
  }

  /* That was most of the work, one final pass of row/column interchange */
  /* to finish */
  for (k=4-2; k>=0; k--) { /* Don't need to work with 1 by 1 corner*/
    i=pvt_j[k];            /* Rows to swap correspond to pivot COLUMN */
    if (i!=k) {            /* If rows are different */
      for(j=0; j<4; j++) {
        hold = m[k][j];
        m[k][j]=-m[i][j];
        m[i][j]=hold;
      }
    }

    j=pvt_i[k];           /* Columns to swap correspond to pivot ROW */
    if (j!=k)             /* If columns are different */
    for (i=0; i<4; i++) {
      hold=m[i][k];
      m[i][k]=-m[i][j];
      m[i][j]=hold;
    }
  }
    
  return true;
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

