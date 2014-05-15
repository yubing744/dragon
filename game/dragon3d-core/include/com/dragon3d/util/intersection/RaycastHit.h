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


#ifndef RaycastHit_Intersection_Util_Dragon3d_Com_H
#define RaycastHit_Intersection_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage4(com, dragon3d, scene, collider)
    class Collider;
EndPackage4 

BeginPackage4(com, dragon3d, util, intersection)

Import dragon::lang;
Import com::dragon3d::scene::collider;

class_ RaycastHit extends(Object) {
public:
    static const Type* TYPE;
    
public:
    RaycastHit(Collider* collider, float distance);
    virtual ~RaycastHit();

public:
    virtual Collider* getCollider();
    virtual float getDistance();

protected:
    Collider* collider;
    float distance;
};//RaycastHit

EndPackage4 //(com, dragon3d, util, intersection)

#endif //RaycastHit_Intersection_Util_Dragon3d_Com_H
