#include "DirBundleLoader.h"

Import OSGIInternal;

DirBundleLoader::DirBundleLoader()
{

}

DirBundleLoader::DirBundleLoader(P<Framework> framework)
{
	this->framework = framework;
}


bool DirBundleLoader::isAvailable(String location)
{
	P<File> file = new File(location);
	if (!file->exists())
	{
		return false;
	}

	if(!file->isDirectory())
	{
		return false;
	}

	P<File> metaInfMFFile = new File(file->getAbsolutePath()
		.append(L"\\META-INF\\MANIFEST.MF"));

	if(!metaInfMFFile->exists())
	{
		return false;
	}

	return true;
}

P<BundleData> DirBundleLoader::loadBundle(String location)
{
	P<BundleData> bundleData = new BundleData();

	bundleData->setLocation(location);

	String path = location;
	path.append(L"\\META-INF\\MANIFEST.MF");
	P<File> file = new File(path);

	P<Manifest> mf = new Manifest(file);
	P<Map<String,String>> entries = mf->getEntries();

	String symbolicName = entries->get(Constants::BUNDLE_SYMBOLICNAME);
	if (symbolicName == (String)null || symbolicName.equals(L"") ) 
	{
        throw BundleException(String(L"Bundle symbolic name not found: ") + file->getAbsolutePath());
    }

	//if (framework->getBundle(symbolicName) != null) 
	//{
 //       throw BundleException(String(L"Bundle(SymbolicName: ") + symbolicName + String(L") already exists: ") + file->getAbsolutePath());
 //   }

	bundleData->setSymbolicName(symbolicName);

	//get Bundle-Name
	String name = entries->get(Constants::BUNDLE_NAME);
    if (name == (String)null || name.equals(L"")) 
	{
		name = File(location).getName();
    }

	bundleData->setName(name);

    // Validate the bundle activator.

	String activator = entries->get(Constants::BUNDLE_ACTIVATOR);
    if (activator == (String)null || symbolicName.equals(L"") )
	{
        throw BundleException(String(L"Bundle activator definition not found: ") + file->getAbsolutePath());
    }

	bundleData->setActivator(activator);

	String nativeLib = entries->get(Constants::BUNDLE_NATIVE_LIB);
	if (nativeLib == (String)null || nativeLib.equals(L"") )
	{
		nativeLib = name + String(L".dll");
	}

	nativeLib = String(location) + String(L"\\") + nativeLib;

	bundleData->setNativeLib(nativeLib);

	//P<Library> lib= new DllLibrary();
	//lib->load(this->nativeLib);

	//if (!lib->containsClass(activator)) 
	//{
 //       throw BundleException(String(L"Bundle activator class(\"") + activator + String(L"\") not found: ") + file->getAbsolutePath());
 //   }

	//lib->free();

	String description = entries->get(Constants::BUNDLE_DESCRIPTION);
    if (description == (String)null || description.equals(L"")) 
	{
        description = L"";
    }

	bundleData->setDescription(description);


	// Parse classpaths
    String classpath = entries->get(Constants::BUNDLE_CLASSPATH);

	P<Array<String>> classPaths = null;

    if (classpath != null) 
	{
        Array<String> theClassPaths =classpath.split(L",");

		int size = theClassPaths.size();
		classPaths = new Array<String>(size);

        for (int i = 0; i < size; i++) 
		{
			String theClassPath =theClassPaths.get(i);

			// Check the classpath entry
			bool entryExists = false;
			
			String theRealPath = generateURL(location, theClassPath);
			File theFile(theRealPath);

			entryExists = theFile.exists();

			if (entryExists) 
			{
				classPaths->set(i, theFile.getCanonicalPath());
			}
			else 
			{
				throw BundleException(String(L"Classpath(\"") + theClassPath + String(L"\") not found: ") + file->getAbsolutePath());
			}
		}
    }
	else 
	{
		classPaths = new Array<String>();
	}

	bundleData->setClassPaths(classPaths);

	// Parse export packages
	String exportPackages = entries->get(Constants::EXPORT_PACKAGE);
	Array<String> exportedPackages;

    if (exportPackages != null) 
	{
         
        exportedPackages =exportPackages.split(L",");
    }
	else 
	{
		exportedPackages = Array<String>();
	}

	bundleData->setExportedPackages(new Array<String>(exportedPackages));

	// Parse import packages, nee
	String importpackages = entries->get(Constants::IMPORT_PACKAGE);
	Array<String> importedPackages;

    if (importpackages != null)
	{
		importedPackages =importpackages.split(L",");
    }
	else 
	{
        importedPackages = Array<String>();
    }

	bundleData->setImportedPackages(new Array<String>(importedPackages));

	// Parse reuqired extensions
	String requiredbundles = entries->get(Constants::REQUIRE_BUNDLE);
	Array<String> requiredBundles;

    if (requiredbundles != null) 
	{
		requiredBundles =requiredbundles.split(L",");
    }
	else 
	{
        requiredBundles =  Array<String>();
    }

	bundleData->setRequiredBundles(new Array<String>(requiredBundles));

	return bundleData;
}

String DirBundleLoader::generateURL(String location, String path) 
{
    return  String(location).append(L"\\").append(path);
}
