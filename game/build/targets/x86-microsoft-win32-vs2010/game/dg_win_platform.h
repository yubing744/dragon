#pragma once

#include "dg_config.h"

#ifndef DG_WIN_PLATFORM
#define DG_WIN_PLATFORM

#include <windows.h>

#include "dg_platform.h"
#include "dg_graphics_lib.h"

class DGWinPlatform
	:public DGPlatform
{
public:
	DGWinPlatform(void);
	virtual ~DGWinPlatform(void);

public:
	virtual void setCallback(DGPlatformCallback* callback);

	virtual DGboolean createWin(const char *title, DGuint width, DGuint height);
	virtual void showWin();

	virtual DGGraphicsLib* getGraphicsLib();

	virtual DGResource* openResource(const char* path);
	virtual void closeResource(DGResource* resource);

	virtual DGLog* getLogger(const char* tagName);

public:
	virtual DGboolean createGraphicsLib();

public:
	void draw();
	void resize(DGuint width, DGuint height);
	void update(DGfloat deltaTime);
	void key(DGubyte charCode, DGboolean pressed, DGuint wParam, DGuint lParam);

public:
	HWND hWnd;

protected:
	DGGraphicsLib* glib;
	DGPlatformCallback* callback;
};

#endif
