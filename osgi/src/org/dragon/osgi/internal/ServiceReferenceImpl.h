#include "osgi_internal.h"

#ifndef OSGI_Internal_ServiceReferenceImpl_H 
#define OSGI_Internal_ServiceReferenceImpl_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageOSGIInternal

Import org::dragon::osgi::framework;

class _DragonExport ServiceReferenceImpl :public ServiceReference, Object
{
public:
	ServiceReferenceImpl();
	ServiceReferenceImpl(P<ServiceRegistration> serviceRegistration);

	virtual P<Object> getProperty(String key);
	virtual P<Bundle> getBundle();
	virtual Array<P<Bundle>> getUsingBundles();
	virtual int compareTo(ServiceReference& o);
	virtual P<ServiceRegistration> getRegistration();

private:
	P<ServiceRegistration> serviceRegistration;
};

EndPackageOSGIInternal

#endif