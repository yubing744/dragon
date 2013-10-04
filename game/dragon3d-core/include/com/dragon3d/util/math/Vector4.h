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


#ifndef Vector4_Math_Util_Dragon3d_Com_H
#define Vector4_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, util, math)

Import com::dragon3d::util::math;

class _DragonExport Vector4 {
public:
    static const Vector4 ZERO; //Shorthand for writing Vector4(0, 0, 0, 0)
    static const Vector4 ONE; //Shorthand for writing Vector4(1, 1, 1, 1)

public:
    Vector4();
    Vector4(float x, float y, float z, float w);
    virtual ~Vector4();

public:
    float x;
    float y;
    float z;
    float w;
};//Vector4

EndPackage4 //(com, dragon3d, util, math)

#endif //Vector4_Math_Util_Dragon3d_Com_H
