#include "osgi_framework.h"

#ifndef OSGI_Framework_BundleClassLoader_H 
#define OSGI_Framework_BundleClassLoader_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport BundleClassLoader :public ClassLoader
{
public:
	virtual ~BundleClassLoader(){};

	virtual P<Class<Object>> loadClass(String className)=0;

};

EndPackageOSGIFramework

#endif