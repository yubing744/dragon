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
 * Created:     2014/05/01
 **********************************************************************/


#ifndef Bounds_Scene_Dragon3d_Com_H
#define Bounds_Scene_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

#include <dragon/lang/String.h>
#include <dragon/util/List.h>
#include <com/dragon3d/scene/Component.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Quaternion.h>
#include <com/dragon3d/util/math/Matrix4x4.h>
#include <com/dragon3d/util/math/Ray3.h>

BeginPackage3(com, dragon3d, scene)

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::scene;
Import com::dragon3d::util::math;

class_ Bounds extends(Object) {
public:
    static const Type* TYPE;
    
public:
    Bounds();
    Bounds(const Vector3& center);
    Bounds(const Vector3& center, const Vector3& size);
    virtual ~Bounds();

public:
    /**
     * Is point contained in the bounding box?
     * 
     * @param  point [description]
     * @return       [description]
     */
    bool contains(const Vector3& point);

    /**
     * Grows the Bounds to include the point.
     * 
     * @param point [description]
     */
    void encapsulate(const Vector3& point);

    /**
     * Grow the bounds to encapsulate the bounds.
     * 
     * @param bounds [description]
     */
    void encapsulate(Bounds* bounds);

    /**
     * Expand the bounds by increasing its size by amount along each side.
     * 
     * @param amount [description]
     */
    void expand(float amount);

    /**
     * Expand the bounds by increasing its size by amount along each side.
     * 
     * @param amount [description]
     */
    void expand(const Vector3& amount);


    /**
     * Does ray intersect this bounding box?
     * 
     * @param  ray [description]
     * @return     [description]
     */
    bool intersectRay(Ray3* ray);

    /**
     * Does another bounding box intersect with this bounding box?
     * 
     * @param  bounds [description]
     * @return        [description]
     */
    bool intersects(Bounds* bounds);

    /**
     * Sets the bounds to the min and max value of the box.
     *
     * Using this function is faster than assigning min and max separately.
     * 
     * @param min [description]
     * @param max [description]
     */
    void setMinMax(const Vector3& min, const Vector3& max);

    /**
     * The smallest squared distance between the point and this bounding box.
     * 
     * @param  point [description]
     * @return       [description]
     */
    float sqrDistance(const Vector3& point);

    /**
     * tranform this bounds to new one.
     * 
     * @param  matrix [description]
     * @return       [description]
     */
    Bounds* transform(const Matrix4x4& matrix);

    /**
     * Returns a nicely formatted string for the bounds.
     * 
     * @return [description]
     */
    String* toString() const;

protected:
    /**
     * <code>clip</code> determines if a line segment intersects the current test plane.
     * 
     * @param denom
     *            the denominator of the line segment.
     * @param numer
     *            the numerator of the line segment.
     * @param t
     *            test values of the plane.
     * @return true if the line segment intersects the plane, false otherwise.
     */
    bool clip(float denom, float numer, float* t);

public:

    /**
     * get the center of bounding box
     * 
     * @return [description]
     */
    Vector3 getCenter();

    /**
     * set the center of bounidng box
     * 
     * @param center [description]
     */
    void setCenter(const Vector3& center);

    /**
     * get the extends of bounds
     * 
     * @return [description]
     */
    Vector3 getExtents();

    /**
     * set the extends of bounds.
     * 
     * @param extends [description]
     */
    void setExtents(const Vector3& extents);

    /**
     * Get The maximal point of the box. This is always equal to center+extents.
     * 
     * @return [description]
     */
    Vector3 getMax();

    /**
     * The minimal point of the box. This is always equal to center-extents.
     * 
     * @return [description]
     */
    Vector3 getMin();

    /**
     *  The total size of the box. This is always twice as large as the extents.
     *      
     * @return [description]
     */
    Vector3 getSize();

    /**
     * get the all eight corner.
     * 
     */
    const Array<Vector3> getCorners();

protected:
    /**
     * The center of the bounding box.
     * 
     */
    Vector3 center; 

    /**
     * The extents of the box. This is always half of the size.
     */
    Vector3 extents;

};//Bounds

EndPackage3 //(com, dragon3d, scene)

#endif //Bounds_Scene_Dragon3d_Com_H
