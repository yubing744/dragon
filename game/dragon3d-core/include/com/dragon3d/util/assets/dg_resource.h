#pragma once

#include "dg_config.h"

#ifndef DG_RESOURCE
#define DG_RESOURCE

class DGResource
{
public:
	DGResource(void){};
	virtual ~DGResource(void){};

public:
	virtual int read(void *buffer, size_t size, size_t count) = 0;
	virtual int seek(long offset, int fromwhere) = 0;
	virtual long tell() = 0;

	virtual DGuint length() = 0;
};

#endif