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