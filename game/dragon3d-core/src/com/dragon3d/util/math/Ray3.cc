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
 * Created:     2013/09/20
 **********************************************************************/


#include <com/dragon3d/util/math/Ray3.h>

Import com::dragon3d::util::math;

Ray3::Ray3(Vector3 origin, Vector3 direction) 
    :origin(origin), direction(direction){
    direction.normalize();
}

Ray3::~Ray3() {

}


Vector3 Ray3::getPoint(float distance) {
    return Vector3(origin.x + direction.x * distance, 
        origin.y + direction.y * distance,
        origin.z + direction.z * distance);
}
