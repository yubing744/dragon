#include "osgi_internal.h"

#ifndef OSGI_Internal_DirBundleLoader_H 
#define OSGI_Internal_DirBundleLoader_H
#pragma once


BeginPackageOSGIInternal

class _DragonExport DirBundleLoader :public BundleLoader,public Object
{
public:
	DirBundleLoader();
	DirBundleLoader(P<Framework> framework);

	virtual bool isAvailable(String location);
	virtual P<BundleData> loadBundle(String location);

private:
	String generateURL(String location, String path);

private:
	P<Framework> framework;
};

EndPackageOSGIInternal

#endif