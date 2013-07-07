#include "DragonOSGI.h"

Import OSGILaunch;

String DragonOSGI::DEFAULT_FRAMEWORK_IMPL = L"org::dragon::osgi::internal::FrameworkLauncher";

DragonOSGI::DragonOSGI(P<Map<String,String>> configuration)
{
	this->configuration = configuration;
}

void DragonOSGI::setConfiguration(P<Map<String,String>> configuration)
{
	this->configuration = configuration;
}

long DragonOSGI::getBundleId()
{
	return getImpl()->getBundleId();
}

P<BundleData> DragonOSGI::getBundleData()
{
	return getImpl()->getBundleData();
}

P<Map<String,String>> DragonOSGI::getHeaders()
{
	return getImpl()->getHeaders();
}

String DragonOSGI::getLocation()
{
	return getImpl()->getLocation();
}

String DragonOSGI::getSymbolicName()
{
	return getImpl()->getSymbolicName();
}

P<Class<Object>> DragonOSGI::loadClass(const String& name) throw(ClassNotFoundException)
{
	return getImpl()->loadClass(name);
}

int DragonOSGI::getState()
{
	return getImpl()->getState();
}

void DragonOSGI::init() throw(BundleException)
{
	getImpl()->init();
}

void DragonOSGI::start() throw(BundleException)
{
	getImpl()->start();
}

void DragonOSGI::stop() throw(BundleException)
{
	getImpl()->stop();
}

void DragonOSGI::uninstall() throw(BundleException)
{
	getImpl()->uninstall();
}

void DragonOSGI::update() throw(BundleException)
{
	getImpl()->update();
}

void DragonOSGI::update(P<InputStream> stream) throw(BundleException)
{
	getImpl()->update(stream);
}

P<Framework> DragonOSGI::createImpl()
{
	P<Framework> theFramework = null;

	if(this->configuration == (P<Map<String,String>>)null) 
		throw new BundleException();

	String frameworkImplClazz = this->configuration->get(Constants::OSGI_FRAMEWORK_IMPL);
	
	if(frameworkImplClazz == (String)null || frameworkImplClazz.equals(L""))
	{
		frameworkImplClazz = DragonOSGI::DEFAULT_FRAMEWORK_IMPL;
	}

	P<Class<Object>> clazz = null;

	try
	{
		clazz = Class<Object>::ForName(frameworkImplClazz);
	}
	catch(ClassNotFoundException& e)
	{
		throw new BundleException(e.getMessage() + String(L"\n") + frameworkImplClazz);
	}
	
	if(clazz == (P<Class<Object>>)null) 
		throw new BundleException();

	theFramework = (Framework*)clazz->newInstance();
	theFramework->setConfiguration(this->configuration);
	return theFramework;
}

P<Framework> DragonOSGI::getImpl()
{
	if (this->frameworkImpl == (P<Framework>)null)
	{
		this->frameworkImpl = createImpl();
	}

	return this->frameworkImpl;
}

P<Bundle> DragonOSGI::installBundle(String location) 
		throw(BundleException)
{
	return getImpl()->installBundle(location);
}

P<List<P<Bundle>>> DragonOSGI::installBundles(String location) 
		throw(BundleException)
{
	return getImpl()->installBundles(location);
}

P<Bundle> DragonOSGI::getBundle(String symbolicName) 
		throw(BundleException)
{
	return getImpl()->getBundle(symbolicName);
}

P<FrameworkClassLoader> DragonOSGI::getClassLoader()
{
	return getImpl()->getClassLoader();
}

P<FrameworkLog> DragonOSGI::getLog()
{
	return getImpl()->getLog();
}

P<Bundle> DragonOSGI::getBundle(long id)
{
	return getImpl()->getBundle(id);
}

P<Array<P<Bundle>>> DragonOSGI::getBundles() 
		throw(BundleException)
{
	return getImpl()->getBundles();
}

P<ServiceRegistry> DragonOSGI::getServiceRegistry()
{
	return getImpl()->getServiceRegistry();
}

void DragonOSGI::startBundle(long bundleId)
{
	return getImpl()->startBundle(bundleId);
}

void DragonOSGI::startBundle(String symbolicName)
{
	return getImpl()->startBundle(symbolicName);
}

void DragonOSGI::stopBundle(long bundleId)
{
	return getImpl()->stopBundle(bundleId);
}

void DragonOSGI::stopBundle(String symbolicName)
{
	return getImpl()->stopBundle(symbolicName);
}