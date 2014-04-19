#pragma once

#include "dg_config.h"

#if !defined(DG_ASSERT_RESOURCE)
#define DG_ASSERT_RESOURCE

#include <stdio.h>
#include <string>

#include "dg_log.h"
#include "dg_resource.h"
#include "dg_android.h"

using std::string;

class DGAssertResource
	:public DGResource
{
public:
	DGAssertResource(AAssetManager* mgr, const char* path);
	virtual ~DGAssertResource(void);

public:
	virtual int read(void *buffer, size_t size, size_t count);
	virtual int seek(long offset, int fromwhere);
	virtual long tell();
	virtual DGuint length();

public:
	DGboolean open();
	void close();

private:
	AAssetManager* mgr;
	string path;
	AAsset* asset;
	long cursor;
private:
	static DGLog* LOG;
};

#endif