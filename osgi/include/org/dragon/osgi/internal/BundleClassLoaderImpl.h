#include "osgi_internal.h"

#ifndef OSGI_Internal_BundleClassLoaderImpl_H 
#define OSGI_Internal_BundleClassLoaderImpl_H
#pragma once


BeginPackageOSGIInternal

class _DragonExport BundleClassLoaderImpl :public BundleClassLoader, Object
{
public:
	BundleClassLoaderImpl();
	BundleClassLoaderImpl(P<ClassLoader> parent,P<BundleData> bundleData);

	virtual P<Class<Object>> loadClass(String className);
	virtual bool isPackageExposed(String packageName);

protected:
	void init();
	bool checkFile(String dllFile);

private:
	P<ClassLoader> parent;
	P<BundleData> bundleData;
	P<List<P<Library>>> libs;
	P<Library> nativeLib;
	P<Set<String>> packages;
};

EndPackageOSGIInternal

#endif