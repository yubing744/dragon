#include "osgi_internal.h"

#ifndef OSGI_Internal_ServiceRegistryImpl_H 
#define OSGI_Internal_ServiceRegistryImpl_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageOSGIInternal

Import org::dragon::osgi::framework;

class _DragonExport ServiceRegistryImpl :public ServiceRegistry, Object
{
public:
	ServiceRegistryImpl();
	ServiceRegistryImpl(P<Framework> framework);

	virtual P<ServiceRegistration> registerService(P<BundleContext> context, P<Array<String>> clazzes,
		P<Object> service, P<Map<String,String>> properties);

	virtual void unregisterServices(P<BundleContext> context);

	virtual void unregisterService(P<BundleContext> context, P<ServiceRegistration> registration);

	virtual P<ServiceReference> getServiceReference(P<BundleContext> context, String clazz);

	virtual P<Array<P<ServiceReference>>> getServiceReferences(P<BundleContext> context, String clazz,
			String filterstring, bool allservices);

	virtual P<Object> getService(P<BundleContext> context, P<ServiceReference> reference);

	virtual bool ungetService(P<BundleContext> context, P<ServiceReference> reference);

private:
	P<Framework> framework;
	P<Map<String,P<List<P<ServiceRegistration>>>>> publishedServicesByClass;
	P<Map<String,P<List<P<ServiceRegistration>>>>> publishedServicesByContext;
	P<List<P<ServiceRegistration>>> allPublishedServices;

};

EndPackageOSGIInternal

#endif