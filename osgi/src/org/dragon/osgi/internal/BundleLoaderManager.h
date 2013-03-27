#include "osgi_internal.h"

#ifndef OSGI_Internal_BundleLoaderManager_H 
#define OSGI_Internal_BundleLoaderManager_H
#pragma once


BeginPackageOSGIInternal

class _DragonExport BundleLoaderManager :public BundleLoader,public Object
{
public:
	BundleLoaderManager();
	BundleLoaderManager(P<Framework> framework);

	virtual bool isAvailable(String location);
	virtual P<BundleLoader> findAvailableLoader(String location);
	virtual P<BundleData> loadBundle(String location);
	virtual void registerBundleLoader(P<BundleLoader> bundleLoader);

protected:
	virtual void init();

public:
	static P<BundleLoaderManager> GetInstance();

private:
	P<Framework> framework;
	P<List<P<BundleLoader>>> bundleLoaders;

private:
	static P<BundleLoaderManager> plm;
};

typedef BundleLoaderManager BLM;

EndPackageOSGIInternal

#endif