#include "osgi_framework.h"

#ifndef OSGI_Framework_SystemBundleActivator_H 
#define OSGI_Framework_SystemBundleActivator_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport SystemBundleActivator : public BundleActivator
{
public:
	virtual ~SystemBundleActivator(){};

public:
	virtual void start(P<BundleContext> context) 
		throw(Exception)=0;

	virtual void stop(P<BundleContext> context) 
		throw(Exception)=0;

	virtual void setFramework(P<Framework> framework) 
		throw(Exception)=0;
};

EndPackageOSGIFramework

#endif