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


#ifndef Camera_Camera_Scene_Dragon3d_Com_H
#define Camera_Camera_Scene_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, scene, camera)

Import com::dragon3d::scene::camera;

class _DragonExport Camera {
public:
	Camera();
	virtual ~Camera();

public:
	
protected:
	
};//Camera

EndPackage4 //(com, dragon3d, scene, camera)

#endif //Camera_Camera_Scene_Dragon3d_Com_H


/*

#pragma once

#include "dg_game.h"
#include "dg_component.h"

#if !defined(DG_CAMERA)
#define DG_CAMERA

class DGCamera
	:public DGComponent
{
public:
	DGCamera(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void setup(DGContext* ctx);

public:
	DGVector3 eye;
	DGVector3 center;
	DGVector3 up;

	DGfloat fovy;
	DGfloat aspect;
	DGfloat zNear;
	DGfloat zFar;

private:
	DGLog* log; //Out Variable
};

#endif


 */
