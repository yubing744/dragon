#pragma once

#include "dg_config.h"

#ifndef DG_PLATFORM
#define DG_PLATFORM

#include "dg_log.h"
#include "dg_graphics_lib.h"
#include "dg_platform_callback.h"
#include "dg_resource.h"

class DGPlatform
{
public:
	DGPlatform(void);
	virtual ~DGPlatform(void);

public:
	virtual void setCallback(DGPlatformCallback* callback) = 0;

	virtual DGboolean createWin(const char *title, DGuint width, DGuint height) = 0;
	virtual void showWin() = 0;

	virtual DGGraphicsLib* getGraphicsLib() = 0;

	virtual DGResource* openResource(const char* path) = 0;
	virtual void closeResource(DGResource* resource) =0;

    virtual DGLog* getLogger(const char* tagName) = 0;

public:
	static DGPlatform* getCurrent();

protected:
	static DGPlatform* platform;
};

#endif