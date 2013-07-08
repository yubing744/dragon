#pragma once

#include "dg_config.h"

#ifndef DG_PLATFORM_CALLBACK
#define DG_PLATFORM_CALLBACK

class DGPlatformCallback
{
public:
	DGPlatformCallback(void);
	virtual ~DGPlatformCallback(void);

public:
	virtual void start() = 0;
	virtual void draw() = 0;
	virtual void resize(DGuint width, DGuint height) = 0;
	virtual void update(DGfloat deltaTime) = 0;
	virtual void key(DGubyte charCode, DGboolean pressed, DGuint wParam, DGuint lParam) = 0;
};

#endif