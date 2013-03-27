#include "osgi_internal.h"

#ifndef OSGI_Internal_BundleContextImpl_H 
#define OSGI_Internal_BundleContextImpl_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageOSGIInternal

Import org::dragon::osgi::framework;

class _DragonExport BundleContextImpl :public BundleContext, Object
{
public:
	BundleContextImpl();
	BundleContextImpl(P<Framework> framework, P<Bundle> bundle);
	

	virtual P<Bundle> getBundle();
	virtual P<Bundle> getBundle(long id);
	virtual P<Bundle> getBundle(String symbolicName);

	virtual String getProperty(String key);

	virtual P<Bundle> installBundle(String location) 
		throw(BundleException);

	virtual P<Object> getService(P<ServiceReference> reference);

	virtual P<ServiceReference> getServiceReference(String clazz);

	virtual P<Array<P<ServiceReference>>> getServiceReferences(String clazz, String filter);

	virtual P<ServiceRegistration> registerService(String clazz, P<Object> service,
			P<Map<String,String>> properties);

	virtual P<ServiceRegistration> registerService(P<Array<String>> clazzes, P<Object> service,
			P<Map<String,String>> properties);

	virtual bool ungetService(P<ServiceReference> reference);

private:
	P<Framework> framework;
	P<Bundle> bundle;

};

EndPackageOSGIInternal

#endif