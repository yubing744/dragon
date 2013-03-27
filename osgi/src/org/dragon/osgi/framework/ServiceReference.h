#include "osgi_framework.h"

#ifndef OSGI_Framework_ServiceReference_H 
#define OSGI_Framework_ServiceReference_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport ServiceReference :public Comparable<ServiceReference>
{
public:
	virtual ~ServiceReference(){};

public:
	virtual P<Object> getProperty(String key)=0;
	virtual P<Bundle> getBundle()=0;
	virtual Array<P<Bundle>> getUsingBundles()=0;
	virtual int compareTo(ServiceReference& o)=0;
	virtual P<ServiceRegistration> getRegistration()=0;

};

EndPackageOSGIFramework

#endif