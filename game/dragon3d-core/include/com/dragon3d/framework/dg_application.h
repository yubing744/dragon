#pragma once

#include "dg_config.h"
#include "dg_engine.h"

#if !defined(DG_APPLICATION)
#define DG_APPLICATION


class DGApplication
{
public:
	DGApplication(){}

public:
	virtual void startup(DGEngine* engine);
	virtual void end(DGEngine* engine);
};

#endif
