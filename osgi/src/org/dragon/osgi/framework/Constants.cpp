#include "Constants.h"

Import OSGIFramework;

const String Constants::SYSTEM_BUNDLE_LOCATION = L"System Bundle";
const String Constants::BUNDLE_LOCATION = L"bundle.location";
const String Constants::OSGI_FRAMEWORK_IMPL = L"osgi.framework.impl";

const String Constants::BUNDLE_SYMBOLICNAME = L"Bundle-SymbolicName";
const String Constants::BUNDLE_ACTIVATOR = L"Bundle-Activator";
const String Constants::BUNDLE_NAME = L"Bundle-Name";
const String Constants::BUNDLE_NATIVE_LIB = L"Bundle-Native-Lib";
const String Constants::BUNDLE_DESCRIPTION = L"Bundle-Description";
const String Constants::BUNDLE_CLASSPATH = L"Bundle-ClassPath";
const String Constants::IMPORT_PACKAGE = L"Import-Package";
const String Constants::EXPORT_PACKAGE = L"Export-Package";
const String Constants::REQUIRE_BUNDLE = L"Require-Bundle";
const String Constants::BUNDLE_LINKS = L"bundle.links";

P<Map<int,String>> Constants::BundleStates = null;

P<Map<int,String>> Constants::GetBundleStates()
{
	if (BundleStates == (P<Map<int,String>>)null)
	{
		P<Map<int,String>> bundleStateMap =  new HashMap<int,String>();

		//bundleStateMap->put(Bundle::STATE::ACTIVE, L"Active");
		//bundleStateMap->put(Bundle::STATE::INSTALLED, L"Installed");
		//bundleStateMap->put(Bundle::STATE::RESOLVED, L"Resolved");
		//bundleStateMap->put(Bundle::STATE::STARTING, L"Starting");
		//bundleStateMap->put(Bundle::STATE::STOPPING, L"Stopping");
		//bundleStateMap->put(Bundle::STATE::UNINSTALLED, L"Uninstalled");

		bundleStateMap->put(Bundle::STATE::ACTIVE, L"ACTIVE");
		bundleStateMap->put(Bundle::STATE::INSTALLED, L"INSTALLED");
		bundleStateMap->put(Bundle::STATE::RESOLVED, L"RESOLVED");
		bundleStateMap->put(Bundle::STATE::STARTING, L"STARTING");
		bundleStateMap->put(Bundle::STATE::STOPPING, L"STOPPING");
		bundleStateMap->put(Bundle::STATE::UNINSTALLED, L"UNINSTALLED");

		BundleStates = bundleStateMap;
	}

	return BundleStates;
}
