#include "osgi_framework.h"

#ifndef OSGI_Framework_FrameworkFactory_H 
#define OSGI_Framework_FrameworkFactory_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport FrameworkFactory
{
public:
	virtual ~FrameworkFactory(){};

public:
	virtual P<Framework> newFramework(P<Map<String,String>> configuration)=0;
};

EndPackageOSGIFramework

#endif