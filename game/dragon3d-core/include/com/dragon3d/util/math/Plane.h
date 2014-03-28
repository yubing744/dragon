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


#ifndef Plane_Math_Util_Dragon3d_Com_H
#define Plane_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Ray3.h>

BeginPackage4(com, dragon3d, util, math)

Import dragon::lang;
Import com::dragon3d::util::math;

/**
 * Representation of planes.
 *
 * A plane is defined by a normal vector and distance from the origin to the plane.
 * 
 */
class _DragonExport Plane extends(Object) {
public:
    Plane(const Vector3& inNormal, const Vector3& inPoint);
    Plane(const Vector3& inNormal, float d);
    Plane(const Vector3& a, const Vector3& b, const Vector3& c);
    
public:
    /**
     * Returns a signed distance from plane to point.
     *
     * The value returned is positive if the point is on the side of the plane into which the plane's normal is facing, and negative otherwise.
     * 
     * @param  inPt [description]
     * @return      [description]
     */
    float getDistanceToPoint(const Vector3& inPt);

    /**
     * Is a point on the positive side of the plane?
     * 
     * @param  inPt [description]
     * @return      [description]
     */
    bool getSide(const Vector3& inPt);

    /**
     * Intersects a ray with the plane.
     *
     * This function sets enter to the distance along the ray, where it intersects the plane. 
     * If the ray is parallel to the plane, function returns false and sets enter to zero. 
     * If the ray is pointing in the opposite direction than the plane, function returns false 
     * and sets enter to the distance along the ray (negative value).
     * 
     * @param  ray   [description]
     * @param  enter [description]
     * @return       [description]
     */
    bool raycast(const Ray3* ray, float* enter);

    /**
     * Are two points on the same side of the plane?
     * 
     * @param  inPt0 [description]
     * @param  inPt1 [description]
     * @return       [description]
     */
    bool sameSide(const Vector3& inPt0, const Vector3& inPt1);

    /**
     * Sets a plane using three points that lie within it. The points go around clockwise as 
     * you look down on the top surface of the plane.
     * 
     * @param a [description]
     * @param b [description]
     * @param c [description]
     */
    void set3Points(const Vector3& a, const Vector3& b, const Vector3& c);

    /**
     * Sets a plane using a point that lies within it plus a normal to orient it (note that the 
     * normal must be a normalised vector).
     * 
     * @param inNormal [description]
     * @param inPoint  [description]
     */
    void setNormalAndPosition(const Vector3& inNormal, const Vector3& inPoint);

public:
    /**
     * Distance from the origin to the plane.
     */
    float distance; 
    
    /**
     * Normal vector of the plane.
     * 
     */
    Vector3 normal;

};//Plane

EndPackage4 //(com, dragon3d, util, math)

#endif //Plane_Math_Util_Dragon3d_Com_H
