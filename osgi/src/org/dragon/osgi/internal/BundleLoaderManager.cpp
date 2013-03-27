#include "BundleLoaderManager.h"

Import OSGIInternal;

P<BundleLoaderManager> BundleLoaderManager::plm = null;

BundleLoaderManager::BundleLoaderManager()
{
	this->bundleLoaders = new ArrayList<P<BundleLoader>>;
}

BundleLoaderManager::BundleLoaderManager(P<Framework> framework)
{
	this->bundleLoaders = new ArrayList<P<BundleLoader>>;
	this->framework = framework;
}

void BundleLoaderManager::init()
{
	registerBundleLoader(new DirBundleLoader());
	registerBundleLoader(new ZipBundleLoader());
	registerBundleLoader(new LinksBundleLoader());
}

void BundleLoaderManager::registerBundleLoader(P<BundleLoader> bundleLoader)
{
	this->bundleLoaders->add(bundleLoader);
}

bool BundleLoaderManager::isAvailable(String location)
{
	int size = this->bundleLoaders->size();
	P<BundleLoader> bundleLoader = null;
	for ( int i = 0; i < size; ++i )
	{
		bundleLoader = this->bundleLoaders->get(i);
		if (bundleLoader->isAvailable(location))
		{
			return true;
		}
	}

	return false;
}

P<BundleLoader> BundleLoaderManager::findAvailableLoader(String location)
{
	int size = this->bundleLoaders->size();
	P<BundleLoader> bundleLoader = null;
	for ( int i = 0; i < size; ++i )
	{
		bundleLoader = this->bundleLoaders->get(i);
		if (bundleLoader->isAvailable(location) != null)
		{
			return bundleLoader;
		}
	}

	return null;
}

P<BundleData> BundleLoaderManager::loadBundle(String location)
{
	P<BundleLoader> bundleLoader = this->findAvailableLoader(location);
	return bundleLoader->loadBundle(location);
}

P<BundleLoaderManager> BundleLoaderManager::GetInstance()
{
	if (plm == (P<BundleLoaderManager>)null)
	{
		plm = new BundleLoaderManager();
		plm->init();
	}

	return plm;
}