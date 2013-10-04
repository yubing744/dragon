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

BeginPackage4(com, dragon3d, util, math)

Import com::dragon3d::util::math;

class _DragonExport Matrix4x4 {
public:
    const static Matrix4x4 IDENTITY;

public:
    static Matrix4x4 multiply(const Matrix4x4& matrixA, const Matrix4x4& matrixB);

//---------------------------------------------------
public:
    Matrix4x4(void);
    Matrix4x4(float* f4x4);
    Matrix4x4(
        float x11, float x12, float x13, float x14,
        float x21, float x22, float x23, float x24,
        float x31, float x32, float x33, float x34,
        float x41, float x42, float x43, float x44
    );

public:
    void identity();
    Matrix4x4 multiply(const Matrix4x4& matrix);
    bool inverse();

public:
    float m[4][4];
    
};//Matrix4x4

EndPackage4 //(com, dragon3d, util, math)

#endif //Matrix4x4_Math_Util_Dragon3d_Com_H
