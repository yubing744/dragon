#include "osgi_launch.h"

#ifndef OSGI_Launch_DragonOSGI_H 
#define OSGI_Launch_DragonOSGI_H 
#pragma once

BeginPackageOSGILaunch 

Import org::dragon::osgi::framework;

class _DragonExport DragonOSGI :public Framework, Object
{

public:
	DragonOSGI(P<Map<String,String>> configuration);

	virtual void init() throw(BundleException);

	virtual long getBundleId();
	virtual P<BundleData> getBundleData();
	virtual P<Map<String,String>> getHeaders();
	virtual String getLocation();
	virtual String getSymbolicName();
	virtual P<Class<Object>> loadClass(const String& name) 
		throw(ClassNotFoundException);

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

	virtual P<Bundle> getBundle(String symbolicName) 
		throw(BundleException);

	virtual P<Bundle> getBundle(long id);
	virtual P<Array<P<Bundle>>> getBundles() 
		throw(BundleException);

	virtual P<FrameworkClassLoader> getClassLoader();

	virtual P<FrameworkLog> getLog();

	virtual P<ServiceRegistry> getServiceRegistry();

private:
	P<Framework> createImpl();
	P<Framework> getImpl();

private:
	P<Map<String,String>> configuration;
	P<Framework> frameworkImpl;
	static String DEFAULT_FRAMEWORK_IMPL;
};

EndPackageOSGILaunch

#endif