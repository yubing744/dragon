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
 * Created:     2013/10/12
 **********************************************************************/


#include <gtest/gtest.h>
#include <com/dragon3d/util/math/Matrix4x4.h>
#include <com/dragon3d/util/math/Mathf.h>

Import com::dragon3d::util::math;

void ASSERT_MATRIX4X4_EQ(const Matrix4x4& mat, 
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33) {

    ASSERT_FLOAT_EQ(m00, mat.m[0][0]); ASSERT_FLOAT_EQ(m01, mat.m[0][1]); ASSERT_FLOAT_EQ(m02, mat.m[0][2]); ASSERT_FLOAT_EQ(m03, mat.m[0][3]);
    ASSERT_FLOAT_EQ(m10, mat.m[1][0]); ASSERT_FLOAT_EQ(m11, mat.m[1][1]); ASSERT_FLOAT_EQ(m12, mat.m[1][2]); ASSERT_FLOAT_EQ(m13, mat.m[1][3]);
    ASSERT_FLOAT_EQ(m20, mat.m[2][0]); ASSERT_FLOAT_EQ(m21, mat.m[2][1]); ASSERT_FLOAT_EQ(m22, mat.m[2][2]); ASSERT_FLOAT_EQ(m23, mat.m[2][3]);
    ASSERT_FLOAT_EQ(m30, mat.m[3][0]); ASSERT_FLOAT_EQ(m31, mat.m[3][1]); ASSERT_FLOAT_EQ(m32, mat.m[3][2]); ASSERT_FLOAT_EQ(m33, mat.m[3][3]);
}

TEST(Com_Dragon3d_Util_Math_Matrix4x4Test, New) {
    Matrix4x4* o = new Matrix4x4();
    SafeDelete(o);
}

TEST(Com_Dragon3d_Util_Math_Matrix4x4Test, Perspective) {
    Matrix4x4 mat = Matrix4x4::perspective(60, 1, 0.3, 1000);

    ASSERT_MATRIX4X4_EQ(mat,
        1.732051,0,0,0,
        0,1.732051,0,0,
        0,0,-1.0006,-1,
        0,0,-0.60018,0
    );
}

TEST(Com_Dragon3d_Util_Math_Matrix4x4Test, ortho_normal) {
    Matrix4x4 mat = Matrix4x4::ortho(10, 330, 10, 330, 10, 100);

    ASSERT_MATRIX4X4_EQ(mat,
        0.00625, 0, 0, 0, 
        0, 0.00625, 0, 0, 
        0, 0, -0.02222222, 0, 
        -1.0625, -1.0625, -1.222222, 1
    );
}




