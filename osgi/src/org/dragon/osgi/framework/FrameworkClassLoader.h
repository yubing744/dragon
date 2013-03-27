#include "osgi_framework.h"

#ifndef OSGI_Framework_FrameworkClassLoader_H 
#define OSGI_Framework_FrameworkClassLoader_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport FrameworkClassLoader : public ClassLoader
{
public:
	virtual ~FrameworkClassLoader(){};

	virtual P<Class<Object>> loadClass(String className)=0;
	virtual P<BundleClassLoader> getBundleClassLoader(String symbolicName)=0;
	virtual void createBundleClassLoader(P<BundleData> bundleData)=0;
	virtual bool isPackageExposed(String packageName)=0;
};

EndPackageOSGIFramework

#endif