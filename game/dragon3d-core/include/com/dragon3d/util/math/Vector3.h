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

BeginPackage4(com, dragon3d, util, math)

Import com::dragon3d::util::math;

class _DragonExport Vector3 {
public:
    static const Vector3 ZERO; //Shorthand for writing Vector3(0, 0, 0)
    static const Vector3 ONE; //Shorthand for writing Vector3(1, 1, 1)

    static const Vector3 FORWARD; //Shorthand for writing Vector3(0, 0, 1)
    static const Vector3 UP; //Shorthand for writing Vector3(0, 1, 0)
    static const Vector3 RIGHT; //Shorthand for writing Vector3(1, 0, 0)
    static const Vector3 LEFT; //Shorthand for writing Vector3(-1, 0, 0)

public:
    Vector3(void);
    Vector3(float x, float y, float z);
    virtual ~Vector3();

public:
    float x;
    float y;
    float z;
};//Vector3

EndPackage4 //(com, dragon3d, util, math)

#endif //Vector3_Math_Util_Dragon3d_Com_H
