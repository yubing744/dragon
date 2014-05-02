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


#ifndef Frustum_Camera_Scene_Dragon3d_Com_H
#define Frustum_Camera_Scene_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>

#include <com/dragon3d/util/math/Color.h>
#include <com/dragon3d/util/math/Rect.h>
#include <com/dragon3d/util/math/Ray3.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Matrix4x4.h>

#include <com/dragon3d/scene/Bounds.h>

BeginPackage4(com, dragon3d, scene, camera)

Import dragon::lang;
Import com::dragon3d::scene;
Import com::dragon3d::util::math;

class_ Frustum extends(Object) {
public:
    static const Type* TYPE;

public:// planes of the frustum
    /**
     * LEFT_PLANE represents the left plane of the camera frustum.
     */
    static const int LEFT_PLANE = 0;

    /**
     * RIGHT_PLANE represents the right plane of the camera frustum.
     */
    static const int RIGHT_PLANE = 1;

    /**
     * BOTTOM_PLANE represents the bottom plane of the camera frustum.
     */
    static const int BOTTOM_PLANE = 2;

    /**
     * TOP_PLANE represents the top plane of the camera frustum.
     */
    static const int TOP_PLANE = 3;

    /**
     * FAR_PLANE represents the far plane of the camera frustum.
     */
    static const int FAR_PLANE = 4;

    /**
     * NEAR_PLANE represents the near plane of the camera frustum.
     */
    static const int NEAR_PLANE = 5;

    /**
     * FRUSTUM_PLANES represents the number of planes of the camera frustum.
     */
    static const int FRUSTUM_PLANES = 6;

public:
    Frustum();
    virtual ~Frustum();

public:
    virtual void update(float screenDepth, const Matrix4x4& projectionMatrix, const Matrix4x4& viewMatrix);
    virtual int checkBounds(Bounds* bounds);

protected:
    Array<Plane*> planes;

};//Frustum

EndPackage4 //(com, dragon3d, scene, camera)

#endif //Frustum_Camera_Scene_Dragon3d_Com_H
