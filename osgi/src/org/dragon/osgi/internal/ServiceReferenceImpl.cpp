#include "ServiceReferenceImpl.h"

Import OSGIInternal;

ServiceReferenceImpl::ServiceReferenceImpl(){}

ServiceReferenceImpl::ServiceReferenceImpl(P<ServiceRegistration> serviceRegistration)
{
	this->serviceRegistration = serviceRegistration;
}

P<Object> ServiceReferenceImpl::getProperty(String key)
{
	return null;
}

P<Bundle> ServiceReferenceImpl::getBundle()
{
	return null;
}

Array<P<Bundle>> ServiceReferenceImpl::getUsingBundles()
{
	return null;
}

 
int ServiceReferenceImpl::compareTo(ServiceReference& o)
{
	return 0;
}

P<ServiceRegistration> ServiceReferenceImpl::getRegistration()
{
	return this->serviceRegistration;
}