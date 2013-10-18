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


#include <com/dragon3d/util/math/Vector2.h>

Import com::dragon3d::util::math;

const Vector2 Vector2::ZERO = Vector2(0, 0);
const Vector2 Vector2::ONE = Vector2(1, 1);

Vector2::Vector2(void){
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}