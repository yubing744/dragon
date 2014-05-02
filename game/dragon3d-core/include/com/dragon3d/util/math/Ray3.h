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
#include <com/dragon3d/util/math/Plane.h>

BeginPackage4(com, dragon3d, util, math)

Import dragon::lang;
Import com::dragon3d::util::math;

/**
 * Representation of rays.
 *
 * A ray is an infinite line starting at origin and going in some direction.
 * 
 * @param  Object [description]
 * @return        [description]
 */
class _DragonExport Ray3 extends(Object) {
public:
    static const Type* TYPE;
    
public:
    Ray3(const Vector3& origin, const Vector3& direction);

public:
    /**
     * get the origin of ray.
     * 
     * @return [description]
     */
    Vector3 getOrigin();

    /**
     * [getDirection description]
     * @return [description]
     */
    Vector3 getDirection();

    /**
     * Returns a point at distance units along the ray.
     * 
     * @param  distance [description]
     * @return          [description]
     */
    Vector3 getPoint(float distance);

    /**
     * Determine whether a ray intersect with a triangle
     * 
     * @param  plane [description]
     * @param  t     [description]
     * @return       [description]
     */
    bool intersectPlane(Plane* plane, float* t);

    /**
     * Determine whether a ray intersect with a triangle
     *
     * v0, v1, v2: vertices of triangle
     * t(out): weight of the intersection for the ray
     * u(out), v(out): barycentric coordinate of intersection
     * 
     * @param  v0 [description]
     * @param  v1 [description]
     * @param  v2 [description]
     * @param  t  [description]
     * @param  u  [description]
     * @param  v  [description]
     * @return    [description]
     */
    bool intersectTriangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, float* t, float* u, float* v);
    bool intersectTriangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, float* t);

protected:
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
