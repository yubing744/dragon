#include "ServiceRegistrationImpl.h"

Import OSGIInternal;

ServiceRegistrationImpl::ServiceRegistrationImpl(){}

ServiceRegistrationImpl::ServiceRegistrationImpl(P<ServiceRegistry> registry, 
	P<BundleContext> context, P<Array<String>> clazzes, P<Object> service)
{
	this->registry = registry;
	this->context = context;
	this->clazzes = clazzes;
	this->service = service;

	this->reference = new ServiceReferenceImpl(this);
}

P<ServiceReference> ServiceRegistrationImpl::getReference()
{
	return this->reference;
}

void ServiceRegistrationImpl::setProperties(P<Map<String,String>> properties)
{

}

void ServiceRegistrationImpl::unregister()
{
	registry->unregisterService(context, this);
}

P<Object> ServiceRegistrationImpl::getService(P<BundleContext> user)
{
	return this->service;
}

bool ServiceRegistrationImpl::ungetService(P<BundleContext> user)
{
	return this->registry->ungetService(user, this->getReference());
}

P<Array<String>> ServiceRegistrationImpl::getClasses()
{
	return this->clazzes;
}