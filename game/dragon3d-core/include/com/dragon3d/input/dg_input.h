#pragma once

#include "dg_config.h"

#ifndef DG_INPUT
#define DG_INPUT

class DGInput
{
public:
	DGInput(void);
	virtual ~DGInput(void);

public:
	virtual DGboolean getKey(char keyCode) = 0;
	virtual DGboolean getAxis(const char* axis) = 0;
};

#endif
