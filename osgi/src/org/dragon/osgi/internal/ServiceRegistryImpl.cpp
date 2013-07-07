#include "ServiceRegistryImpl.h"

Import OSGIInternal;

ServiceRegistryImpl::ServiceRegistryImpl(){}

ServiceRegistryImpl::ServiceRegistryImpl(P<Framework> framework)
{
	this->framework = framework;
	this->publishedServicesByClass = new HashMap<String,P<List<P<ServiceRegistration>>>>();
	this->publishedServicesByContext = new HashMap<String,P<List<P<ServiceRegistration>>>>();
	this->allPublishedServices = new ArrayList<P<ServiceRegistration>>();
}

P<ServiceRegistration> ServiceRegistryImpl::registerService(P<BundleContext> context, P<Array<String>> clazzes,
		P<Object> service, P<Map<String,String>> properties)
{
	P<ServiceRegistration> serviceRegistration = new ServiceRegistrationImpl(this, context, clazzes, service);

	// Add the ServiceRegistrationImpl to the list of Services published by BundleContextImpl.
	String contextId = context->getBundle()->getSymbolicName();
	P<List<P<ServiceRegistration>>> contextServices = publishedServicesByContext->get(contextId);
	if (contextServices == (P<List<P<ServiceRegistration>>>)null) 
	{
		contextServices = new ArrayList<P<ServiceRegistration>>();
		publishedServicesByContext->put(contextId, contextServices);
	}

	contextServices->add(serviceRegistration);


	// Add the ServiceRegistrationImpl to the list of Services published by Class Name.
	int size = clazzes->size();
	for ( int i = 0; i < size; ++i )
	{
		String clazz = clazzes->get(i);
		P<List<P<ServiceRegistration>>> services = publishedServicesByClass->get(clazz);

		if ( services == (P<List<P<ServiceRegistration>>>)null)
		{
			services = new ArrayList<P<ServiceRegistration>>();
			publishedServicesByClass->put(clazz, services);
		}

		services->add(serviceRegistration);
	}

	// Add the ServiceRegistrationImpl to the list of all published Services.
	allPublishedServices->add(serviceRegistration);
	
	return serviceRegistration;
}

P<ServiceReference> ServiceRegistryImpl::getServiceReference(P<BundleContext> context, String clazz)
{
	P<Array<P<ServiceReference>>> references = getServiceReferences(context, clazz, null, false);

	if (references != null && references->size() > 0)
	{
		return references->get(0);
	}

	return null;
}

P<Array<P<ServiceReference>>> ServiceRegistryImpl::getServiceReferences(P<BundleContext> context, String clazz,
			String filterstring, bool allservices)
{
	P<List<P<ServiceRegistration>>> result;

	if (clazz == (String)null) 
	{ 
		result = allPublishedServices;
	} 
	else 
	{		
		result = publishedServicesByClass->get(clazz);
	}

	if ((result == (P<List<P<ServiceRegistration>>>)null) || (result->size() == 0)) 
	{
		result = new ArrayList<P<ServiceRegistration>>();
	}

	int size = result->size();
	P<Array<P<ServiceReference>>> theResult = new Array<P<ServiceReference>>(size);
	for (int i = 0; i < size; i++)
	{
		P<ServiceRegistration> serviceRegistration = result->get(i);
		theResult->set(i, serviceRegistration->getReference());
	}

	return theResult;
}

P<Object> ServiceRegistryImpl::getService(P<BundleContext> context, P<ServiceReference> reference)
{
	return reference->getRegistration()->getService(context);
}

bool ServiceRegistryImpl::ungetService(P<BundleContext> context, P<ServiceReference> reference)
{
	return true;
}

void ServiceRegistryImpl::unregisterServices(P<BundleContext> context)
{
	String contextId = context->getBundle()->getSymbolicName();
	P<List<P<ServiceRegistration>>> contextServices = publishedServicesByContext->get(contextId);

	int size = contextServices->size();
	for( int i = 0; i < size; ++i )
	{
		P<ServiceRegistration> registration = contextServices->get(i);

		//remove registration from publishedServicesByContext
		P<Array<String>> clazzes = registration->getClasses();

		int size = clazzes->size();
		for ( int i = 0; i < size; ++i )
		{
			String clazz = clazzes->get(i);
			P<List<P<ServiceRegistration>>> services = publishedServicesByClass->get(clazz);

			if ( services != null)
			{
				services->remove(registration);
			}
		}

		//remove registration from allPublishedServices
		allPublishedServices->remove(registration);
	}

	//remove registration from publishedServicesByContext
	publishedServicesByContext->remove(contextId);
}

void ServiceRegistryImpl::unregisterService(P<BundleContext> context, P<ServiceRegistration> registration)
{
	//remove registration from publishedServicesByContext
	String contextId = context->getBundle()->getSymbolicName();
	P<List<P<ServiceRegistration>>> contextServices = publishedServicesByContext->get(contextId);
	contextServices->remove(registration);


	//remove registration from publishedServicesByClass
	P<Array<String>> clazzes = registration->getClasses();

	int size = clazzes->size();
	for ( int i = 0; i < size; ++i )
	{
		String clazz = clazzes->get(i);
		P<List<P<ServiceRegistration>>> services = publishedServicesByClass->get(clazz);

		if ( services != null)
		{
			services->remove(registration);
		}
	}

	//remove registration from allPublishedServices
	allPublishedServices->remove(registration);
}