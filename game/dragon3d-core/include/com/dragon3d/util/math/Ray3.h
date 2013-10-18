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


#ifndef Ray3_Math_Util_Dragon3d_Com_H
#define Ray3_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <com/dragon3d/util/math/Vector3.h>

BeginPackage4(com, dragon3d, util, math)

Import dragon::lang;
Import com::dragon3d::util::math;

class _DragonExport Ray3 {
public:
    Ray3(Vector3 origin, Vector3 direction);

public:
    /**
     * Returns a point at distance units along the ray.
     * 
     * @param  distance [description]
     * @return          [description]
     */
    Vector3 getPoint(float distance);

public:
    /**
     * The direction of the ray.
     *
     * Direction is always a normalized vector. If you assign a vector of non unit length, 
     * it will be normalized.
     */
    Vector3 direction; 

    /**
     * The origin point of the ray.
     * 
     */
    Vector3 origin; 
	
};//Ray3

EndPackage4 //(com, dragon3d, util, math)

#endif //Ray3_Math_Util_Dragon3d_Com_H
