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


#ifndef Application_Framework_Dragon3d_Com_H
#define Application_Framework_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage3(com, dragon3d, framework)

Import com::dragon3d::framework;

class _DragonExport Application {
public:
	Application();
	virtual ~Application();

public:
	virtual void startup();
	
};//Application

EndPackage3 //(com, dragon3d, framework)

#endif //Application_Framework_Dragon3d_Com_H

/*

#pragma once

#include "dg_config.h"

#if !defined(DG_ENGINE)
#define DG_ENGINE

#include <vector>

#include "dg_vector3.h"
#include "dg_scene.h"
#include "dg_screen.h"
#include "dg_platform.h"
#include "dg_platform_callback.h"
#include "dg_graphics_lib.h"
#include "dg_log.h"
#include "dg_input_manager.h"
#include "dg_model_manager.h"
#include "dg_camera.h"

using std::vector;

class DGEngine
	:public DGPlatformCallback
{
public:
	DGEngine(void);
	virtual ~DGEngine(void);

public:
	virtual DGboolean init(DGPlatform* platform, const char* title, DGuint width, DGuint height);
	virtual DGScene* createScene();
	virtual void setupCamera(DGCamera* camera);

public: // Implements Interface DGPlatformCallback
	virtual void start();
	virtual void run();
	virtual void draw();
	virtual void resize(DGuint width, DGuint height);
	virtual void update(DGfloat deltaTime);
	virtual void key(DGubyte charCode, DGboolean pressed, DGuint wParam, DGuint lParam);

public: // Getter
    DGPlatform* getPlatform() {
        return this->platform;
    };

    DGGraphicsLib* getGraphicsLib() {
        return this->glib;
    };

    DGScreen* getScreen() {
        return this->screen;
    };

	DGInput* getInput() {
		return this->inputManager;
	};

	DGModelManager* getModelManager() {
		return this->modelManager;
	};

private:
    DGScreen* screen; //Inner Variable
	DGInputManager* inputManager; //Inner Variable
	DGModelManager* modelManager; //Inner Variable
	DGPlatform* platform; //Out Variable
	DGGraphicsLib* glib; //Out Variable

	vector<DGScene*> scenes;
	vector<DGCamera*> cameras;

public:
	DGuint targetFrameRate;
	DGuint currentFrameRate;

	DGfloat frameInterval;
    char name[256];

private:
	static DGLog* LOG;
};

#endif



#pragma once

#include "dg_config.h"

#if !defined(DG_CONTEXT)
#define DG_CONTEXT

#include "dg_input.h"
#include "dg_screen.h"
#include "dg_platform.h"
#include "dg_graphics_lib.h"

class DGEngine;

class DGContext
{
public:
    DGContext(DGEngine* engine){
        this->engine = engine;
    }

public:
    DGEngine* getEngine() {
        return engine;
    };

    DGPlatform* getPlatform();
    DGGraphicsLib* getGraphicsLib();
    DGScreen* getScreen();
	DGfloat getFrameInterval();
	DGInput* getInput();

private:
    DGEngine* engine;
};

#endif

 */