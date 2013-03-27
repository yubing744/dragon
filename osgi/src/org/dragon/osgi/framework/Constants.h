#include "osgi_framework.h"

#ifndef OSGI_Framework_Constants_H 
#define OSGI_Framework_Constants_H 
#pragma once

BeginPackageOSGIFramework

class _DragonExport Constants
{
public:
	static const String SYSTEM_BUNDLE_LOCATION;
	static const String BUNDLE_LOCATION;
	static const String OSGI_FRAMEWORK_IMPL;

	static const String BUNDLE_NAME;
	static const String BUNDLE_SYMBOLICNAME;
	static const String BUNDLE_NATIVE_LIB;
	static const String BUNDLE_ACTIVATOR;
	static const String BUNDLE_DESCRIPTION;

	static const String BUNDLE_CLASSPATH;
	static const String IMPORT_PACKAGE;
	static const String EXPORT_PACKAGE;
	static const String REQUIRE_BUNDLE;
	static const String BUNDLE_LINKS;
	
	static P<Map<int,String>> GetBundleStates();

private:
	static P<Map<int,String>> BundleStates;
};

EndPackageOSGIFramework

#endif