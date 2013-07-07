#include "LinksBundleLoader.h"

Import OSGIInternal;

LinksBundleLoader::LinksBundleLoader()
{

}

LinksBundleLoader::LinksBundleLoader(P<Framework> framework)
{
	this->framework = framework;
}


bool LinksBundleLoader::isAvailable(String location)
{
	P<File> file = new File(location);
	if (!file->exists())
	{
		return false;
	}

	if (!file->getName().endsWith(String(L".link")))
	{
		return false;
	}

	return true;
}

P<BundleData> LinksBundleLoader::loadBundle(String location)
{
	P<File> file = new File(location);
	P<Reader> reader = new FileReader(file);
	P<Properties> prop = new Properties();
	prop->load(reader);

	String newLocation = prop->getProperty(L"path");

	if (BLM::GetInstance()->isAvailable(newLocation))
	{
		return BLM::GetInstance()->loadBundle(newLocation);
	}

	return null;
}