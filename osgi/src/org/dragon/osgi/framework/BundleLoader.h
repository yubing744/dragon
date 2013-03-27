#include "osgi_framework.h"

#ifndef OSGI_Framework_BundleLoader_H 
#define OSGI_Framework_BundleLoader_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport BundleLoader
{
public:
	virtual ~BundleLoader(){};

	virtual bool isAvailable(String location)=0;
	virtual P<BundleData> loadBundle(String location)=0;

};

EndPackageOSGIFramework

#endif