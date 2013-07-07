#ifndef OSGI_Framework_H
#define OSGI_Framework_H

#include "config/config.h"

#define BeginPackageOSGIFramework BeginPackage4(org,dragon,osgi,framework)
#define EndPackageOSGIFramework EndPackage4
#define OSGIFramework org::dragon::osgi::framework

BeginPackageOSGIFramework

	class BundleException;
	class Constants;
	interface EventListener;
	interface ClassLoader;
	interface BundleClassLoader;
	interface FrameworkClassLoader;
	interface FrameworkLog;
	interface BundleData;
	interface ServiceReference;
	interface ServiceRegistration;
	interface BundleContext;
	interface BundleLoader;
	interface Bundle;
	interface Framework;
	interface FrameworkEvent;
	interface FrameworkListener;
	interface FrameworkFactory;
	interface BundleActivator;
	interface SystemBundleActivator;
	interface ServiceRegistry;
	interface ServiceRegistration;
	interface ServiceReference;


EndPackageOSGIFramework

#include "dragon.h"


#include "BundleException.h"
#include "EventListener.h"
#include "FrameworkLog.h"
#include "ServiceReference.h"
#include "ServiceRegistration.h"
#include "Constants.h"
#include "ClassLoader.h"
#include "BundleClassLoader.h"
#include "FrameworkClassLoader.h"
#include "BundleData.h"
#include "BundleContext.h"
#include "BundleLoader.h"
#include "Bundle.h"
#include "Framework.h"
#include "FrameworkEvent.h"
#include "FrameworkListener.h"
#include "FrameworkFactory.h"
#include "BundleActivator.h"
#include "SystemBundleActivator.h"
#include "ServiceRegistry.h"
#include "ServiceRegistration.h"
#include "ServiceReference.h"

#endif