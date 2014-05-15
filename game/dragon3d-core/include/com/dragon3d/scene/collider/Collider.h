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
 * Created:     2014/05/14
 **********************************************************************/


#ifndef Collider_Collider_Scene_Dragon3d_Com_H
#define Collider_Collider_Scene_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <com/dragon3d/scene/Component.h>
#include <com/dragon3d/scene/Bounds.h>
#include <com/dragon3d/util/intersection/RaycastHit.h>

BeginPackage4(com, dragon3d, scene, collider)

Import dragon::lang;
Import com::dragon3d::scene;
Import com::dragon3d::util::intersection;

class_ Collider extends(Component) {
public:
    static const Type* TYPE;
    
public:
    Collider();
    virtual ~Collider();

public:
    /**
     * the component is type of type.
     * 
     * @param  type [description]
     * @return      [description]
     */
    virtual bool isTypeOf(const Type* type);

public:
    /**
     * The closest point to the bounding box of the attached collider.
     * 
     * @param  position [description]
     * @return          [description]
     */
    Vector3 closestPointOnBounds(const Vector3& position);

    /**
     * Casts a Ray that ignores all Colliders except this one.
     * 
     * @param  ray      [description]
     * @param  hitInfo  [description]
     * @param  distance [description]
     * @return          [description]
     */
    bool raycast(Ray3* ray, RaycastHit** hitInfo, float distance);
    bool raycast(Ray3* ray, RaycastHit** hitInfo);

public:
    /** 
     * get the bounds of collider.
     */
    virtual Bounds* getBounds();

    /**
     * check if enabled.
     * 
     * @return [description]
     */
    virtual bool isEnabled();

protected:
    Bounds* bounds;
    bool enabled;
};//Collider

EndPackage4 //(com, dragon3d, scene, collider)

#endif //Collider_Collider_Scene_Dragon3d_Com_H
