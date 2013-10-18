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


#include <com/dragon3d/util/math/Mathf.h>

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cfloat>

Import std;
Import com::dragon3d::util::math;

const float Mathf::PI = 3.141592654f;

const float Mathf::EPSILON = (1e-8);

float Mathf::max(float x, float y) {
    return x < y ? y : x;
}

float Mathf::min(float x, float y) {
    return x > y ? y : x;
}

float Mathf::sin(float a){
    return ::sin(a);
}

float Mathf::cos(float a){
    return ::cos(a);
}

float Mathf::sqrt(float a) {
    return ::sqrtf(a);
}

float Mathf::safeAcos(float x) {
    if (x <= -1.0f) {
        return Mathf::PI;
    }
    if (x >= 1.0f) {
        return 0.0f;
    }

    return acos(x);
}