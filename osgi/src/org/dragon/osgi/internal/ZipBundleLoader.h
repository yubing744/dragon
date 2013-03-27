#include "osgi_internal.h"

#ifndef OSGI_Internal_ZipBundleLoader_H 
#define OSGI_Internal_ZipBundleLoader_H
#pragma once


BeginPackageOSGIInternal

class _DragonExport ZipBundleLoader :public BundleLoader,public Object
{
public:
	ZipBundleLoader();
	ZipBundleLoader(P<Framework> framework);

	virtual bool isAvailable(String location);
	virtual P<BundleData> loadBundle(String location);

private:
	P<Framework> framework;
};

EndPackageOSGIInternal

#endif