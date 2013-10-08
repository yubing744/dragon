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
 * Created:     2013/10/08
 **********************************************************************/


#include <gtest/gtest.h>
#include <com/dragon3d/util/math/Quaternion.h>
#include <com/dragon3d/util/math/Mathf.h>

Import com::dragon3d::util::math;

TEST(Com_Dragon3d_Util_Math_QuaternionTest, New) {
    Quaternion* o = new Quaternion();
    SafeDelete(o);
}

TEST(Com_Dragon3d_Util_Math_QuaternionTest, Euler_01) {
    Quaternion rot = Quaternion::euler(30, 0, 0);

    //printf("x:%f y:%f z:%f\n", rot.x, rot.y, rot.z);

    ASSERT_FLOAT_EQ(0.258819, rot.x);
    ASSERT_FLOAT_EQ(0, rot.y);
    ASSERT_FLOAT_EQ(0, rot.z);
}

TEST(Com_Dragon3d_Util_Math_QuaternionTest, Euler_02) {
    Quaternion rot = Quaternion::euler(30, 30, 0);

    //printf("x:%f y:%f z:%f\n", rot.x, rot.y, rot.z);

    ASSERT_FLOAT_EQ(0.25, rot.x);
    ASSERT_FLOAT_EQ(0.25, rot.y);
    ASSERT_FLOAT_EQ(-0.0669873, rot.z);
}

TEST(Com_Dragon3d_Util_Math_QuaternionTest, Euler_03) {
    Quaternion rot = Quaternion::euler(30, 30, 30);

    //printf("x:%f y:%f z:%f\n", rot.x, rot.y, rot.z);

    ASSERT_FLOAT_EQ(0.3061862, rot.x);
    ASSERT_FLOAT_EQ(0.1767767, rot.y);
    ASSERT_FLOAT_EQ(0.1767767, rot.z);
}


TEST(Com_Dragon3d_Util_Math_QuaternionTest, multiply_01) {
    Quaternion rot1 = Quaternion::euler(30, 30, 30);
    Quaternion rot2 = Quaternion::euler(30, 30, 30);

    Quaternion result = rot1.multiply(rot2);
    printf("x:%f y:%f z:%f\n", result.x, result.y, result.z);

    ASSERT_FLOAT_EQ(0.5624999, result.x);
    ASSERT_FLOAT_EQ(0.3247595, result.y);
    ASSERT_FLOAT_EQ(0.3247595, result.z);
}
