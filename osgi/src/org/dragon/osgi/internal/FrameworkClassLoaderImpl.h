#include "osgi_internal.h"

#ifndef OSGI_Internal_FrameworkClassLoaderImpl_H 
#define OSGI_Internal_FrameworkClassLoaderImpl_H
#pragma once


BeginPackageOSGIInternal

class _DragonExport FrameworkClassLoaderImpl :public FrameworkClassLoader, Object
{
public:
	FrameworkClassLoaderImpl();
	FrameworkClassLoaderImpl(P<Framework> framework);

	virtual P<Class<Object>> loadClass(String className);
	virtual P<BundleClassLoader> getBundleClassLoader(String symbolicName);

	virtual void createBundleClassLoader(P<BundleData> bundleData);

	virtual bool isPackageExposed(String packageName);

private:
	P<Framework> framework;
	P<Map<String,P<BundleClassLoader>>> bundleClassLoaders;
};

EndPackageOSGIInternal

#endif