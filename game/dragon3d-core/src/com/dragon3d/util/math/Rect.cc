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


#include <com/dragon3d/util/math/Rect.h>


Import com::dragon3d::util::math;

const Type* Rect::TYPE = TypeOf<Rect>();

Rect Rect::minMaxRect(float left, float top, float right, float bottom) {
    return Rect(left, top, right - left, bottom - top);
}

Rect::Rect() 
    :x(0.0f), y(0.0f), width(1.0f), height(1.0f) {

}

Rect::Rect(float x, float y, float width, float height)
    :x(x), y(y), width(width), height(height)  {

}

Vector2 Rect::getCenter() {
    return Vector2(x + width / 2, y + height / 2);
}

float Rect::getLeft() {
    return x;
}

float Rect::getTop() {
    return y;
}

float Rect::getRight() {
    return x + width;
}

float Rect::getBottom() {
    return y + height;
}

/**
 * Returns true if the x and y components of point is a point inside this rectangle.
 * 
 * @param  p [description]
 * @return   [description]
 */
bool Rect::contains(Vector2 p) {
    return (this->getLeft() <= p.x && this->getRight() >= p.x) 
        && (this->getTop() <= p.y && this->getBottom() >= p.y);
}

void Rect::set(float x, float y, float width, float height) {
    this->x = x;
    this->y = x;

    this->width = width;
    this->height = height;
}

