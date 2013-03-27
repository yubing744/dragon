#include "osgi_framework.h"

#ifndef OSGI_Framework_Framework_H 
#define OSGI_Framework_Framework_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport Framework :public Bundle
{
public:
	virtual ~Framework(){};

public:
	virtual void init() throw(BundleException)=0;
	virtual void setConfiguration(P<Map<String,String>> configuration)=0;
	
	virtual P<Bundle> installBundle(String location) 
		throw(BundleException)=0;
	virtual P<List<P<Bundle>>> installBundles(String location) 
		throw(BundleException)=0;

	virtual void startBundle(long bundleId)=0;
	virtual void startBundle(String symbolicName)=0;

	virtual void stopBundle(long bundleId)=0;
	virtual void stopBundle(String symbolicName)=0;

	virtual P<Bundle> getBundle(long id)=0;
	virtual P<Bundle> getBundle(String symbolicName) 
		throw(BundleException)=0;
	virtual P<Array<P<Bundle>>> getBundles() 
		throw(BundleException)=0;


	virtual P<FrameworkClassLoader> getClassLoader()=0;
	virtual P<FrameworkLog> getLog()=0;
	virtual P<ServiceRegistry> getServiceRegistry()=0;
};

EndPackageOSGIFramework

#endif