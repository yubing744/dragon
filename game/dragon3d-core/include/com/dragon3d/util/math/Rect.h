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


#ifndef Rect_Math_Util_Dragon3d_Com_H
#define Rect_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <com/dragon3d/util/math/Vector2.h>
 
BeginPackage4(com, dragon3d, util, math)

Import dragon::lang;
Import com::dragon3d::util::math;

/**
 * A 2D Rectangle defined by x, y position and width, height.
 * 
 */
class _DragonExport Rect extends(Object) {
public:
    static const Type* TYPE;
    
public:
    Rect minMaxRect(float left, float top, float right, float bottom);

public:
    Rect();
    Rect(float x, float y, float width, float height);

public:
    Vector2 getCenter();

    float getLeft();
    float getTop();
    float getRight();
    float getBottom();

    /**
     * Returns true if the x and y components of point is a point inside this rectangle.
     * 
     * @param  p [description]
     * @return   [description]
     */
    bool contains(Vector2 p);

    void set(float left, float top, float width, float height);

public:
    float x;
    float y;
    float width;
    float height;
};//Rect

EndPackage4 //(com, dragon3d, util, math)

#endif //Rect_Math_Util_Dragon3d_Com_H
