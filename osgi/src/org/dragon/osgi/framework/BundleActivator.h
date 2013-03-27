#include "osgi_framework.h"

#ifndef OSGI_Framework_BundleActivator_H 
#define OSGI_Framework_BundleActivator_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport BundleActivator
{
public:
	virtual ~BundleActivator(){};

public:
	virtual void start(P<BundleContext> context) 
		throw(Exception)=0;

	virtual void stop(P<BundleContext> context) 
		throw(Exception)=0;
};

EndPackageOSGIFramework

#endif