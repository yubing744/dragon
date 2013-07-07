#include "FrameworkClassLoaderImpl.h"

Import OSGIInternal;

FrameworkClassLoaderImpl::FrameworkClassLoaderImpl(){};

FrameworkClassLoaderImpl::FrameworkClassLoaderImpl(P<Framework> framework)
{
	this->framework = framework;
	this->bundleClassLoaders = new HashMap<String,P<BundleClassLoader>>();
}

P<Class<Object>> FrameworkClassLoaderImpl::loadClass(String className)
{
	return LM::GetInstance()->getClassForName(className);
}

P<BundleClassLoader> FrameworkClassLoaderImpl::getBundleClassLoader(String symbolicName)
{
	return this->bundleClassLoaders->get(symbolicName);
}

void FrameworkClassLoaderImpl::createBundleClassLoader(P<BundleData> bundleData)
{
	P<BundleClassLoader> bundleClassLoader =new BundleClassLoaderImpl(this,bundleData);
	this->bundleClassLoaders->put(bundleData->getSymbolicName(),bundleClassLoader);
}

bool FrameworkClassLoaderImpl::isPackageExposed(String packageName)
{
	return true;
}