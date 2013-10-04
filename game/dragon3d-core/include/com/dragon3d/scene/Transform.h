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
 * Created:     2013/09/28
 **********************************************************************/


#ifndef Transform_Scene_Dragon3d_Com_H
#define Transform_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Quaternion.h>

BeginPackage3(com, dragon3d, scene)

Import com::dragon3d::scene;
Import com::dragon3d::util::math;

enum Space {
    World,
    Self
};

class _DragonExport Transform {
public:
    
public:
    Transform(void);
    virtual ~Transform(void);

public:
    void translate(const Vector3& translation, Space relativeTo);
    void rotate(const Vector3& eulerAngles, Space relativeTo);
    void rotate(float xAngle, float yAngle, float zAngle, Space relativeTo);

    void translate(const Vector3& translation);
    void rotate(const Vector3& eulerAngles);
    void rotate(float xAngle, float yAngle, float zAngle);

public:
    // transform in world space
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;

    // transform relative to the parent transform.
    Vector3 localPosition;
    Quaternion localRotation;
    Vector3 localScale;
	
};//Transform

EndPackage3 //(com, dragon3d, scene)

#endif //Transform_Scene_Dragon3d_Com_H
