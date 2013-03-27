#include "osgi_framework.h"

#ifndef OSGI_Framework_EventListener_H 
#define OSGI_Framework_EventListener_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport EventListener
{
public:
	virtual ~EventListener(){};
};

EndPackageOSGIFramework

#endif