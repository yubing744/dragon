#include "BundleContextImpl.h"

Import OSGIInternal;

BundleContextImpl::BundleContextImpl(){}

BundleContextImpl::BundleContextImpl(P<Framework> framework, P<Bundle> bundle)
{
	this->framework = framework;
	this->bundle = bundle;
}

P<Bundle> BundleContextImpl::getBundle()
{
	return this->bundle;
}

P<Bundle> BundleContextImpl::getBundle(long id)
{
	return this->framework->getBundle(id);
}

P<Bundle> BundleContextImpl::getBundle(String symbolicName)
{
	return this->framework->getBundle(symbolicName);
}

String BundleContextImpl::getProperty(String key)
{
	return null;
}

P<Bundle> BundleContextImpl::installBundle(String location) 
		throw(BundleException)
{
	return this->framework->installBundle(location);
}

P<Object> BundleContextImpl::getService(P<ServiceReference> reference)
{
	if (reference != null)
	{
		return framework->getServiceRegistry()->getService(this, reference);
	}

	return null;
}

P<ServiceReference> BundleContextImpl::getServiceReference(String clazz)
{
	return framework->getServiceRegistry()->getServiceReference(this, clazz);
}

P<Array<P<ServiceReference>>> BundleContextImpl::getServiceReferences(String clazz, String filter)
{
	return framework->getServiceRegistry()->getServiceReferences(this, clazz, filter, false);
}

P<ServiceRegistration> BundleContextImpl::registerService(String clazz, P<Object> service,
	P<Map<String,String>> properties)
{
	P<Array<String>> clazzes = new Array<String>(1);
	clazzes->set(0,clazz);
	return framework->getServiceRegistry()->registerService(this, clazzes, service, properties);
}

P<ServiceRegistration> BundleContextImpl::registerService(P<Array<String>> clazzes, P<Object> service,
	P<Map<String,String>> properties)
{
	return framework->getServiceRegistry()->registerService(this, clazzes, service, properties);
}

bool BundleContextImpl::ungetService(P<ServiceReference> reference)
{
	return framework->getServiceRegistry()->ungetService(this,reference);
}