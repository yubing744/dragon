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


#ifndef FirstPersonController_Controller_Input_Dragon3d_Com_H
#define FirstPersonController_Controller_Input_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, input, controller)

Import com::dragon3d::input::controller;

class _DragonExport FirstPersonController {
public:
	FirstPersonController();
	virtual ~FirstPersonController();

public:
	
protected:
	
};//FirstPersonController

EndPackage4 //(com, dragon3d, input, controller)

#endif //FirstPersonController_Controller_Input_Dragon3d_Com_H

/*
#pragma once

#include "dg_game_object.h"

#ifndef DG_FIRST_PERSON_CONTROLLSER
#define DG_FIRST_PERSON_CONTROLLSER

#include "dg_camera.h"

static const float PIOVER_180 = 0.0174532925f;

class DGFirstPersonController :
	public DGGameObject
{
public:
	DGFirstPersonController(void);
	virtual ~DGFirstPersonController(void);

public:
	virtual void init(DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

private:
	DGfloat walkbias;
	DGfloat walkbiasangle;

	DGfloat forwardSpeed;
	DGfloat turnSpeed;
	DGfloat angle;

private:
	DGCamera* camera;
};

#endif

#pragma once

#include "dg_config.h"
#include "dg_camera.h"

#if !defined(DG_FIRST_PERSON_CAMERA)
#define DG_FIRST_PERSON_CAMERA

static const float piover180 = 0.0174532925f;

class DGFirstPersonCamera :
	public DGCamera
{
public:
	DGFirstPersonCamera(void);
	~DGFirstPersonCamera(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);

private:
	GLfloat walkbias;
	GLfloat walkbiasangle;

	DGfloat forwardSpeed;
	DGfloat turnSpeed;
	DGfloat angle;
};

#endif

 */