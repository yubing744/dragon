#include "osgi_framework.h"

#ifndef OSGI_Framework_ServiceRegistry_H 
#define OSGI_Framework_ServiceRegistry_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport ServiceRegistry
{
public:
	virtual ~ServiceRegistry(){};

public:
	virtual P<ServiceRegistration> registerService(P<BundleContext> context, P<Array<String>> clazzes,
		P<Object> service, P<Map<String,String>> properties)=0;

	virtual void unregisterServices(P<BundleContext> context)=0;

	virtual void unregisterService(P<BundleContext> context, P<ServiceRegistration> registration)=0;

	virtual P<ServiceReference> getServiceReference(P<BundleContext> context, String clazz)=0;

	virtual P<Array<P<ServiceReference>>> getServiceReferences(P<BundleContext> context, String clazz,
			String filterstring, bool allservices)=0;

	virtual P<Object> getService(P<BundleContext> context, P<ServiceReference> reference)=0;
	virtual bool ungetService(P<BundleContext> context, P<ServiceReference> reference)=0;
};

EndPackageOSGIFramework

#endif