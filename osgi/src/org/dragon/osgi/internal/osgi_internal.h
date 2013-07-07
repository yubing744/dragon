#ifndef OSGI_Internal_H
#define OSGI_Internal_H

#include "config/config.h"

#define BeginPackageOSGIInternal BeginPackage4(org,dragon,osgi,internal)
#define EndPackageOSGIInternal EndPackage4
#define OSGIInternal org::dragon::osgi::internal

BeginPackageOSGIInternal

	class Manifest;
	class FrameworkLogImpl;
	class BundleClassLoaderImpl;
	class FrameworkClassLoaderImpl;
	class BundleContextImpl;
	class DirBundleLoader;
	class ZipBundleLoader;
	class LinksBundleLoader;
	class BundleLoaderManager;
	class BundleImpl;
	class FrameworkEventImpl;
	class FrameworkLauncher;
	class ServiceReferenceImpl;
	class ServiceRegistrationImpl;
	class ServiceRegistryImpl;

EndPackageOSGIInternal

#include "dragon.h"
#include "../framework/osgi_framework.h"

#include "Manifest.h"
#include "BundleContextImpl.h"
#include "DirBundleLoader.h"
#include "ZipBundleLoader.h"
#include "LinksBundleLoader.h"
#include "BundleLoaderManager.h"
#include "BundleImpl.h"
#include "FrameworkEventImpl.h"
#include "BundleClassLoaderImpl.h"
#include "FrameworkClassLoaderImpl.h"
#include "FrameworkLauncher.h"
#include "FrameworkLogImpl.h"
#include "ServiceReferenceImpl.h"
#include "ServiceRegistrationImpl.h"
#include "ServiceRegistryImpl.h"

#endif