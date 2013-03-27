#include "osgi_internal.h"

#ifndef OSGI_Internal_FrameworkEventImpl_H 
#define OSGI_Internal_FrameworkEventImpl_H
#pragma once


BeginPackageOSGIInternal

class _DragonExport FrameworkEventImpl :public FrameworkEvent,public Object
{
public:
	FrameworkEventImpl();
	FrameworkEventImpl(int type, P<Bundle> bundle, String message, P<Throwable> throwable);

	virtual TYPE getType();

	virtual String getMessage();

	virtual P<Throwable> getThrowable();

	virtual P<Bundle> getBundle();

private:
	P<Bundle> bundle;
	P<Throwable> throwable;
	int	type;
	String message;
};

EndPackageOSGIInternal

#endif