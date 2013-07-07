#include "osgi_framework.h"

#ifndef OSGI_Framework_BundleContext_H 
#define OSGI_Framework_BundleContext_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport BundleContext
{
public:
	virtual ~BundleContext(){};

public:
	virtual P<Bundle> getBundle()=0;
	virtual P<Bundle> getBundle(long id)=0;
	virtual P<Bundle> getBundle(String symbolicName)=0;

	virtual String getProperty(String key)=0;

	virtual P<Bundle> installBundle(String location) 
		throw(BundleException)=0;

	virtual P<ServiceReference> getServiceReference(String clazz)=0;

	virtual P<Array<P<ServiceReference>>> getServiceReferences(String clazz, String filter)=0;

	virtual P<ServiceRegistration> registerService(String clazz, P<Object> service,
			P<Map<String,String>> properties)=0;

	virtual P<ServiceRegistration> registerService(P<Array<String>> clazzes, P<Object> service,
			P<Map<String,String>> properties)=0;

	virtual P<Object> getService(P<ServiceReference> reference)=0;
	virtual bool ungetService(P<ServiceReference> reference)=0;
};

EndPackageOSGIFramework

#endif