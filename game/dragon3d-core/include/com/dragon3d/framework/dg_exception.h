#pragma once

#include "dg_config.h"

#if !defined(DG_EXCEPTION)
#define DG_EXCEPTION

class DGException
{
public:
	DGException(void);
	DGException(char* msg);
	virtual ~DGException(void);

public:
	char* message;
};

#endif