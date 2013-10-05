#pragma once

#include "dg_config.h"

#if !defined(DG_FILE_RESOURCE)
#define DG_FILE_RESOURCE

#include <stdio.h>
#include <string>
#include "dg_resource.h"

using std::string;

class DGFileResource
	:public DGResource
{
public:
	DGFileResource(const char* path);
	virtual ~DGFileResource(void);

public:
	virtual int read(void *buffer, size_t size, size_t count);
	virtual int seek(long offset, int fromwhere);
	virtual long tell();
	virtual DGuint length();

public:
	DGboolean open();
	void close();

private:
	string path;
	FILE* pFile;
};

#endif