#include "ZipBundleLoader.h"

Import OSGIInternal;

ZipBundleLoader::ZipBundleLoader()
{

}

ZipBundleLoader::ZipBundleLoader(P<Framework> framework)
{
	this->framework = framework;
}


bool ZipBundleLoader::isAvailable(String location)
{
	P<File> file = new File(location);
	if (!file->exists())
	{
		return false;
	}

	if (!file->getName().endsWith(String(L".zip")))
	{
		return false;
	}

	P<ZipFile> zf = ZipFile::Open(file->getAbsolutePath());
	 
	P<ZipEntry> zipEntry = zf->getEntry(L"META-INF/MANIFEST.MF");

	if (zipEntry == (P<ZipEntry>)null)
	{
		zf->close();
		return false;
	}

	return true;
}

P<BundleData> ZipBundleLoader::loadBundle(String location)
{
	P<File> file = new File(location);

	P<ZipFile> zf = ZipFile::Open(location);

	String bundleName = file->getName();
	String newLocation = String(L"./configuration/temp/") +bundleName.substring(0,bundleName.length()-4);
	
	zf->unZipTo(newLocation);
	zf->close();

	return BLM::GetInstance()->loadBundle(newLocation);;
}