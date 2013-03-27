#include "BundleImpl.h"

Import OSGIInternal;

BundleImpl::BundleImpl(){}

BundleImpl::BundleImpl(P<Framework> framework,long id, String location)
{
	this->framework = framework;
	this->id = id;
	this->location = location;
	this->state = UNINSTALLED;
	this->bundleContext = new BundleContextImpl(this->framework,this);
}

long BundleImpl::getBundleId()
{
	return this->id;
}

P<BundleData> BundleImpl::getBundleData()
{
	return this->bundleData;
}

P<Map<String,String>> BundleImpl::getHeaders()
{
	P<Map<String,String>> headers = new HashMap<String,String>();
	return headers;
}

String BundleImpl::getLocation()
{
	return this->location;
}

String BundleImpl::getSymbolicName()
{
	return this->bundleData->getSymbolicName();
}

P<Class<Object>> BundleImpl::loadClass(const String& name) throw(ClassNotFoundException)
{
	P<ClassLoader> classLoader = framework->getClassLoader()->getBundleClassLoader(getSymbolicName());
	if (classLoader == (P<ClassLoader>)null)
	{
        throw BundleException(String(L"Bundle(SymbolicName:") + getSymbolicName() + String(L") not installed"));
    }

	return classLoader->loadClass(name);
}

int BundleImpl::getState()
{
	return this->state;
}

void BundleImpl::install() throw(BundleException)
{
	if (this->state != UNINSTALLED)
	{
        throw BundleException(String(L"Bundle(") + getLocation() + String(L") has been installed"));
    }

	this->bundleData = BLM::GetInstance()->loadBundle(this->location);

	if (this->bundleData == (P<BundleData>)null)
	{
		throw BundleException(String(L"Bundle(") + getLocation() + String(L") load failed!"));
	}

	this->state = STATE::INSTALLED;
}

void BundleImpl::resolve() throw(BundleException)
{
	// Check class loader
	P<ClassLoader> classLoader = framework->getClassLoader()->getBundleClassLoader(getSymbolicName());
	if (classLoader == (P<ClassLoader>)null)
	{
        throw BundleException(String(L"Bundle(SymbolicName:") + getSymbolicName() + String(L") not installed"));
    }

	// Resolve exported packages
	P<Array<String>> exportedPackages = bundleData->getExportedPackages();
	int size = exportedPackages->size();

	for (int i = 0; i < size; ++i)
	{
		String exportedPackage = exportedPackages->get(i);
	}


	// Resolve imported packages
	P<Array<String>> importedPackages = bundleData->getImportedPackages();
	size = importedPackages->size();

	for (int i = 0; i < size; ++i)
	{
		String importedPackage = importedPackages->get(i);

		if (!framework->getClassLoader()->isPackageExposed(importedPackage))
		{
			throw BundleException(String(L"Imported package(\"") + importedPackage + String(L"\") not found: ") + getLocation());
        }
	}

	// Resolve required bundles
	P<Array<String>> requiredBundles = bundleData->getRequiredBundles();
	size = requiredBundles->size();

	for (int i = 0; i < size; ++i)
	{
		String requiredBundle = requiredBundles->get(i);
		if (framework->getBundle(requiredBundle) == (P<Bundle>)null) 
		{
			throw BundleException(String(L"Required bundle(SymbolicName:\"") + requiredBundle + String(L"\") not installed: ") + getLocation());
        }
	}


	// Create activator.
    String activatorClass = this->bundleData->getActivator();

    try 
	{
		P<Class<Object>> clazz = classLoader->loadClass(activatorClass);

        if (clazz == (P<Class<Object>>)null)
		{
			throw ClassNotFoundException(String(L"ClassNotFoundException ") + activatorClass);
        }

        activator = (BundleActivator*)clazz->newInstance();
		this->state = STATE::RESOLVED;

    } 
	catch (Exception& e) 
	{
		throw BundleException(String(L"Init BundleActivator failed! \n") + e.getMessage());
	}
}

void BundleImpl::start() throw(BundleException)
{
	if (this->state == STATE::RESOLVED)
	{
		this->state = STATE::STARTING;

		try
		{
			Object* obj = dynamic_cast<Object*>(activator.raw());
			if (InstanceOf<SystemBundleActivator>(obj))
			{
				SystemBundleActivator* sysBundleActivator = dynamic_cast<SystemBundleActivator*>(obj);
				sysBundleActivator->setFramework(framework);
			}

			activator->start(bundleContext);

			this->state = STATE::ACTIVE;
		}
		catch(...)
		{
			this->state = STATE::RESOLVED;
			throw BundleException(String(L"Unable to start bundle(") + String::valueOf(getBundleId()) + String(L") activator: ") + Class<BundleActivator>::GetName(activator) +String(L"\n"));
		}
	}
}

void BundleImpl::stop() throw(BundleException)
{
	this->state = STATE::STOPPING;
	
	P<BundleContext> context = new BundleContextImpl();
	activator->stop(context);

	this->state = STATE::RESOLVED;	
}

void BundleImpl::uninstall() throw(BundleException)
{
	this->state = STATE::UNINSTALLED;
}

void BundleImpl::update() throw(BundleException)
{

}

void BundleImpl::update(P<InputStream> stream) throw(BundleException)
{

}