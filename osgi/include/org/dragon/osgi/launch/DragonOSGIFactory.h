#include "osgi_launch.h"

#ifndef OSGI_Launch_DragonOSGIFactory_H 
#define OSGI_Launch_DragonOSGIFactory_H 
#pragma once

BeginPackageOSGILaunch 

Import org::dragon::osgi::framework;

class _DragonExport DragonOSGIFactory :public FrameworkFactory ,Object
{

public:
	virtual P<Framework> newFramework(P<Map<String,String>> configuration);
};

EndPackageOSGILaunch

#endif