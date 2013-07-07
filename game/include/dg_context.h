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