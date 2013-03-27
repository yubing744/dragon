#include "FrameworkLauncher.h"

Import OSGIInternal;

FrameworkLauncher::FrameworkLauncher(P<Map<String,String>> configuration)
{
	this->configuration = configuration;
}

long FrameworkLauncher::getBundleId()
{
	return 0;
}

P<BundleData> FrameworkLauncher::getBundleData()
{
	return null;
}

P<Map<String,String>> FrameworkLauncher::getHeaders()
{
	P<Map<String,String>> headers = new HashMap<String,String>();
	return headers;
}

String FrameworkLauncher::getLocation()
{
	return String();
}

String FrameworkLauncher::getSymbolicName()
{
	return String(L"org.dragon.osgi_1.0.0");
}

P<Class<Object>> FrameworkLauncher::loadClass(const String& name) throw(ClassNotFoundException)
{
	return LM::GetInstance()->getClassForName(name);
}

void FrameworkLauncher::setConfiguration(P<Map<String,String>> configuration)
{
	this->configuration = configuration;
}

int FrameworkLauncher::getState()
{
	return this->state;
}

void FrameworkLauncher::init() throw(BundleException)
{
	//init private var;
	this->bundleSequence = 1;
	this->bundles =new HashMap<String,P<Bundle>>();
	this->logger = new FrameworkLogImpl();
	this->classLoader = new FrameworkClassLoaderImpl(this);
	this->serviceRegistry = new ServiceRegistryImpl(this);
	this->isStoped = false;
	this->frameworkListeners = new HashSet<P<FrameworkListener>>();


	//install bundles
	if(this->configuration == (P<Map<String,String>>)null) 
		throw new BundleException(L"The configuration can not be null!");
	
	String bundleLocation = this->configuration->get(Constants::BUNDLE_LOCATION);
	if(bundleLocation !=null && !bundleLocation.equals(L""))
	{
		this->installBundles(bundleLocation);
	}

	String bundleLinks = this->configuration->get(Constants::BUNDLE_LINKS);
	if(bundleLinks !=null && !bundleLinks.equals(L""))
	{
		this->installBundles(bundleLinks);
	}

	logger->info(L"FrameworkLauncher init Done!");
}

void FrameworkLauncher::start() throw(BundleException)
{
	if (this->state == STATE::RESOLVED)
	{
		this->state = STATE::STARTING;
		this->fireFrameworkEvent(FrameworkEvent::TYPE::STARTED);

		logger->info(L"FrameworkLauncher start... ");

		registerSystemService();

		P<Iterator<P<Map<String,P<Bundle>>::Entry>>> it=bundles->iterator();

		while(it->hasNext())
		{
			P<Map<String,P<Bundle>>::Entry> entry=it->next();
			P<Bundle> bundle=entry->getValue();

			try 
			{
				bundle->start();
			}
			catch (BundleException& e) 
			{
				logger->warn(String(L"Bundle") + bundle->getSymbolicName() + String(L" start failed!\n") + e.getMessage());
			}
		}

		this->state = STATE::ACTIVE;

		while (!isStoped)
		{
			Thread::sleep(100);
		}
	}

}

void FrameworkLauncher::registerSystemService()
{
	this->bundleContext = new BundleContextImpl(this, this);
	//Object* theFramework = dynamic_cast<Object*>(this);
	//this->bundleContext->registerService(Class<Framework>::GetName(), theFramework, null);

	Object* theLog = dynamic_cast<Object*>(this->logger.raw());
	this->bundleContext->registerService(Class<FrameworkLog>::GetName(),theLog , null);
}

void FrameworkLauncher::stop() throw(BundleException)
{
	if (this->state == STATE::ACTIVE)
	{
		this->state = STATE::STOPPING;
		logger->info(L"FrameworkLauncher stopping... ");

		//this->serviceRegistry->unregisterServices();

		P<Iterator<P<Map<String,P<Bundle>>::Entry>>> it=bundles->iterator();

		while(it->hasNext())
		{
			P<Map<String,P<Bundle>>::Entry> entry=it->next();
			P<Bundle> bundle=entry->getValue();

			try 
			{
				bundle->stop();
			}
			catch (BundleException& e) 
			{
				logger->warn(String(L"Bundle") + bundle->getSymbolicName() + String(L" stop failed!\n") + e.getMessage());
			}
		}

		this->state = STATE::RESOLVED;
	}
}

void FrameworkLauncher::uninstall() throw(BundleException)
{
	this->isStoped = true;
	this->state = STATE::UNINSTALLED;
}


void FrameworkLauncher::update() throw(BundleException)
{

}

void FrameworkLauncher::update(P<InputStream> stream) throw(BundleException)
{

}

P<Bundle> FrameworkLauncher::installBundle(String location) 
		throw(BundleException)
{
	P<BundleImpl> bundle = new BundleImpl(this, bundleSequence++, location);

	bundle->install();

	//Create bundle class loader
	try 
	{
        classLoader->createBundleClassLoader(bundle->getBundleData());
	} 
	catch (BundleException& e)
	{
		throw BundleException(String(L"Can not create bundle(ID:") + String::valueOf(bundle->getBundleId()) + String(L") class loader. \n") + e.getMessage());
	}

	bundle->resolve();

	//bundle->start();

	P<Bundle> theBundle = bundle.raw();
	this->bundles->put(theBundle->getSymbolicName(),theBundle);

	return theBundle;
}

P<Bundle> FrameworkLauncher::installSystemBundle()
{
	this->bundles->put(this->getSymbolicName(),this);
	return this;
}

P<List<P<Bundle>>> FrameworkLauncher::installBundles(String location) 
		throw(BundleException)
{
	P<List<P<Bundle>>> bundles = new ArrayList<P<Bundle>>();

	P<Bundle> sysBundle = installSystemBundle();

	if (sysBundle == (P<Bundle>)null)
	{
		throw BundleException(L"install system bundle failed!");
	}

	bundles->add(sysBundle);


	P<BundleLoader> bundleLoader = BLM::GetInstance();

	P<File> dir = new File(location);

	if(dir->isDirectory())
	{
		P<Array<P<File>>> files = dir->listFiles();
		for(int i = 0; i < files->size(); ++i)
		{
			P<File> file = files->get(i);
			if(bundleLoader->isAvailable(file->getAbsolutePath()))
			{
				P<Bundle> bundle = null;

				try
				{
					bundle = this->installBundle(file->getAbsolutePath());

					if (bundle != null)
					{
						bundles->add(bundle);
					}
				}
				catch(BundleException& be)
				{
					logger->warn(be.getMessage());
				}	
			}
		}
	}

	this->state = STATE::RESOLVED;

	return bundles;
}


void FrameworkLauncher::startBundle(long bundleId)
{
	P<Bundle> bundle = getBundle(bundleId);
	bundle->start();
}

void FrameworkLauncher::startBundle(String symbolicName)
{
	P<Bundle> bundle = getBundle(symbolicName);
	bundle->start();
}

void FrameworkLauncher::stopBundle(long bundleId)
{
	P<Bundle> bundle = getBundle(bundleId);
	bundle->stop();
}

void FrameworkLauncher::stopBundle(String symbolicName)
{
	P<Bundle> bundle = getBundle(symbolicName);
	bundle->stop();
}

P<Bundle> FrameworkLauncher::getBundle(String symbolicName) 
		throw(BundleException)
{
	if (this->bundles->containsKey(symbolicName))
	{
		return this->bundles->get(symbolicName);
	}

	return null;
}

P<FrameworkClassLoader> FrameworkLauncher::getClassLoader()
{
	return this->classLoader;
}

P<FrameworkLog> FrameworkLauncher::getLog()
{
	return this->logger;
}

P<Bundle> FrameworkLauncher::getBundle(long id)
{
	P<Iterator<P<Map<String,P<Bundle>>::Entry>>> it=bundles->iterator();

	while(it->hasNext())
	{
		P<Map<String,P<Bundle>>::Entry> entry=it->next();
		P<Bundle> bundle=entry->getValue();

		if (bundle->getBundleId() == id)
		{
			return bundle;
		}
	}

	return null;
}

P<Array<P<Bundle>>> FrameworkLauncher::getBundles() 
	throw(BundleException)
{
	P<Array<P<Bundle>>> theBundles = new Array<P<Bundle>>(bundles->size());
	int index = 0;

	P<Iterator<P<Map<String,P<Bundle>>::Entry>>> it=bundles->iterator();

	while(it->hasNext())
	{
		P<Map<String,P<Bundle>>::Entry> entry=it->next();
		P<Bundle> bundle=entry->getValue();

		theBundles->set(index++, bundle);
	}

	return theBundles;
}

P<ServiceRegistry> FrameworkLauncher::getServiceRegistry()
{
	return this->serviceRegistry;
}

void FrameworkLauncher::fireFrameworkEvent(FrameworkEvent::TYPE eventType)
{
	this->fireFrameworkEvent(eventType, null);
}

void FrameworkLauncher::fireFrameworkEvent(FrameworkEvent::TYPE eventType, String message)
{ 
   P<FrameworkEvent> theEvent = new FrameworkEventImpl(eventType, null, message, null);
   
   for (P<Iterator<P<FrameworkListener>>> it = frameworkListeners->iterator(); it->hasNext();)
   {
	   P<FrameworkListener> listener = it->next();
       listener->frameworkEvent(theEvent);
   }
}