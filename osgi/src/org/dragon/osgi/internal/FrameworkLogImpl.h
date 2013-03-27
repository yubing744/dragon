#include "osgi_internal.h"

#ifndef OSGI_Internal_FrameworkLogImpl_H 
#define OSGI_Internal_FrameworkLogImpl_H
#pragma once


BeginPackageOSGIInternal

class _DragonExport FrameworkLogImpl :public FrameworkLog,public Object
{
public:
	FrameworkLogImpl();
	FrameworkLogImpl(P<Framework> framework);

	virtual void setLevel(int level);

	virtual void info(String message);
	virtual void debug(String message);
	virtual void warn(String message);
	virtual void error(String message);

	virtual void setWriter(P<Writer> newWriter, bool append);

protected:
	void log(String message);

private:
	P<List<P<Writer>>> getWriters();

private:
	P<Framework> framework;
	P<List<P<Writer>>> writers;
	int level;
};

EndPackageOSGIInternal

#endif