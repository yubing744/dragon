#include "BundleClassLoaderImpl.h"

Import OSGIInternal;

BundleClassLoaderImpl::BundleClassLoaderImpl(){};

BundleClassLoaderImpl::BundleClassLoaderImpl(P<ClassLoader> parent, P<BundleData> bundleData)
{
	this->parent = parent;
	this->bundleData = bundleData;
	
	try
	{
		this->init();
	}
	catch(...)
	{
		throw BundleException(String(L"Init BundleClassLoaderImpl failed!"));
	}
}

void BundleClassLoaderImpl::init()
{
	//load classPaths
	this->libs = new ArrayList<P<Library>>();
	P<Array<String>> classPaths = bundleData->getClassPaths();
	int size = classPaths->size();

	for (int i = 0; i < size; ++i)
	{
		String theClassPath = classPaths->get(i);
		File file(theClassPath);
		
		if (file.isDirectory())
		{
			P<Array<P<File>>> dllFiles=file.listFiles(L"*.dll");
			int fileCount=dllFiles->size();

			for(int i=0;i<fileCount;i++)
			{
				P<File> tempFile=dllFiles->get(i);

				if (checkFile(tempFile->getAbsolutePath())) continue;

				P<Library> lib=new DllLibrary(tempFile->getCanonicalPath());
				this->libs->add(lib);
			}
		}
		else
		{
			if (!checkFile(file.getAbsolutePath()))
			{
				P<Library> lib=new DllLibrary(file.getCanonicalPath());
				this->libs->add(lib);
			}
		}
	}

	//load nativeLib
	nativeLib = new DllLibrary();
	nativeLib->load(bundleData->getNativeLib());

}

bool BundleClassLoaderImpl::checkFile(String dllName)
{
	if (bundleData->getNativeLib().endsWith(dllName))
	{
		return true;
	}

	return false;
}

P<Class<Object>> BundleClassLoaderImpl::loadClass(String className)
{
	//load class by parent class loader
	P<Class<Object>> clazz = parent->loadClass(className);
	if(clazz!=null)
	{
		return clazz;
	}

	//load class from native lib
	clazz = Class<Object>::ForName(nativeLib,className);
	if(clazz!=null)
	{
		return clazz;
	}

	//load class from classpath lib
	int size = this->libs->size();

	for (int i = 0; i < size; ++i)
	{
		clazz = Class<Object>::ForName(libs->get(i),className);

		if(clazz!=null)
		{
			return clazz;
		}
	}

	throw ClassNotFoundException();
}

bool BundleClassLoaderImpl::isPackageExposed(String packageName)
{
	return packages->contains(packageName);
}