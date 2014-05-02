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


#ifndef Color_Math_Util_Dragon3d_Com_H
#define Color_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>

BeginPackage4(com, dragon3d, util, math)

Import dragon::lang;
Import com::dragon3d::util::math;

/**
 * Representation of RGBA colors.
 */
class _DragonExport Color extends(Object) {
public:
    static const Type* TYPE;
    
public:
    static const Color WHITE;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color BLACK;

public:
    static Color hexColor(const char* hexColor);
// -----------------------------

public:
    Color(void);

    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);

    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);

    Color(dg_byte r, dg_byte g, dg_byte b);
    Color(dg_byte r, dg_byte g, dg_byte b, dg_byte a);

    Color(const char* hexColor);

public:
    const float* getData() const;
    const Array<float> toFloatArray() const;

public:
    float r; //Red component of the color.
    float g; //Green component of the color.
    float b; //Blue component of the color.
    float a; //Alpha component of the color.

};//Color

EndPackage4 //(com, dragon3d, util, math)

#endif //Color_Math_Util_Dragon3d_Com_H
