#include "osgi_internal.h"

#ifndef OSGI_Internal_LinksBundleLoader_H 
#define OSGI_Internal_LinksBundleLoader_H
#pragma once


BeginPackageOSGIInternal

class _DragonExport LinksBundleLoader :public BundleLoader,public Object
{
public:
	LinksBundleLoader();
	LinksBundleLoader(P<Framework> framework);

	virtual bool isAvailable(String location);
	virtual P<BundleData> loadBundle(String location);

private:
	P<Framework> framework;
};

EndPackageOSGIInternal

#endif