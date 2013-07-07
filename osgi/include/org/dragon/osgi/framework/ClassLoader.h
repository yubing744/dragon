#include "osgi_framework.h"

#ifndef OSGI_Framework_ClassLoader_H 
#define OSGI_Framework_ClassLoader_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport ClassLoader
{
public:
	virtual ~ClassLoader(){};

	virtual P<Class<Object>> loadClass(String className)=0;

};

EndPackageOSGIFramework

#endif