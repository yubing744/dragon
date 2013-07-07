#include "osgi_internal.h"

#ifndef OSGI_Internal_ServiceRegistrationImpl_H 
#define OSGI_Internal_ServiceRegistrationImpl_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageOSGIInternal

Import org::dragon::osgi::framework;

class _DragonExport ServiceRegistrationImpl :public ServiceRegistration, Object
{
public:
	ServiceRegistrationImpl();
	ServiceRegistrationImpl(P<ServiceRegistry> registry, 
		P<BundleContext> context, P<Array<String>> clazzes, P<Object> service);	

	virtual P<ServiceReference> getReference();
	virtual void setProperties(P<Map<String,String>> properties);
	virtual void unregister();
	virtual P<Object> getService(P<BundleContext> user);
	virtual bool ungetService(P<BundleContext> user);
	virtual	P<Array<String>> getClasses();

private:
	P<ServiceRegistry> registry;
	P<BundleContext> context;
	P<Array<String>> clazzes;
	P<Object> service;
	P<ServiceReference> reference;

};

EndPackageOSGIInternal

#endif