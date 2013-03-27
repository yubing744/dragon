#include "osgi_framework.h"

#ifndef OSGI_Framework_FrameworkListener_H 
#define OSGI_Framework_FrameworkListener_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport FrameworkListener :public EventListener
{
public:
	virtual ~FrameworkListener(){};

	virtual void frameworkEvent(P<FrameworkEvent> event)=0;
};

EndPackageOSGIFramework

#endif