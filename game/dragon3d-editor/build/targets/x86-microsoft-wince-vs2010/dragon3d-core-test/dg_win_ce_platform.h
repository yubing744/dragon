#pragma once

#include "dg_config.h"

#ifndef DG_WIN_CE_PLATFORM
#define DG_WIN_CE_PLATFORM

#include <windows.h>

#include "dg_win_platform.h"
#include "dg_opengl_es_20_lib.h"

class DGWinCEPlatform
	:public DGWinPlatform
{
public:
	DGWinCEPlatform(void);
	virtual ~DGWinCEPlatform(void);

public:
	virtual DGboolean createGraphicsLib();

};

#endif
