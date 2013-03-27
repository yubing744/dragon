#include "osgi_internal.h"

#ifndef OSGI_Internal_FrameworkLauncher_H 
#define OSGI_Internal_FrameworkLauncher_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageOSGIInternal

Import org::dragon::osgi::framework;

class _DragonExport FrameworkLauncher :public Framework,public Object
{
public:
	ImplGetClassSize(FrameworkLauncher);

public:
	FrameworkLauncher(){};
	FrameworkLauncher(P<Map<String,String>> configuration);

	virtual void init() throw(BundleException);

	virtual long getBundleId();
	virtual P<BundleData> getBundleData();
	virtual P<Map<String,String>> getHeaders();
	virtual String getLocation();
	virtual String getSymbolicName();
	virtual P<Class<Object>> loadClass(const String& name) throw(ClassNotFoundException);

	virtual int getState();
	virtual void start() throw(BundleException);
	virtual void stop() throw(BundleException);
	virtual void uninstall() throw(BundleException);
	virtual void update() throw(BundleException);
	virtual void update(P<InputStream> stream) throw(BundleException);
	virtual void setConfiguration(P<Map<String,String>> configuration);

	virtual P<Bundle> installBundle(String location) 
		throw(BundleException);

	virtual P<List<P<Bundle>>> installBundles(String location) 
		throw(BundleException);

	virtual void startBundle(long bundleId);
	virtual void startBundle(String symbolicName);

	virtual void stopBundle(long bundleId);
	virtual void stopBundle(String symbolicName);

	virtual P<Bundle> getBundle(long id);

	virtual P<Bundle> getBundle(String symbolicName) 
		throw(BundleException);

	virtual P<Array<P<Bundle>>> getBundles() 
		throw(BundleException);

	virtual P<FrameworkClassLoader> getClassLoader();

	virtual P<FrameworkLog> getLog();

	virtual P<ServiceRegistry> getServiceRegistry();

protected:
	virtual void registerSystemService();
	virtual P<Bundle> installSystemBundle();

	virtual void fireFrameworkEvent(FrameworkEvent::TYPE eventType);
	virtual void fireFrameworkEvent(FrameworkEvent::TYPE eventType, String msg);

private:
	P<Map<String,String>> configuration;
	P<Map<String,P<Bundle>>> bundles;
	long bundleSequence;
	P<FrameworkLog> logger;
	P<FrameworkClassLoader> classLoader;
	P<ServiceRegistry> serviceRegistry;
	P<BundleContext> bundleContext;
	bool isStoped;
	int state;
	P<Set<P<FrameworkListener>>> frameworkListeners;
};

EndPackageOSGIInternal

#endif