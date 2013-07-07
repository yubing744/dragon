#include "osgi_internal.h"

#ifndef OSGI_Internal_BundleImpl_H 
#define OSGI_Internal_BundleImpl_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageOSGIInternal

Import org::dragon::osgi::framework;

class _DragonExport BundleImpl :public Bundle, public Object
{
public:
	BundleImpl();
	BundleImpl(P<Framework> framework,long id, String location);
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
	
public:
	virtual void install() throw(BundleException);
	virtual void resolve() throw(BundleException);

private:
	P<BundleData> bundleData;
	P<Framework> framework;
	P<BundleContext> bundleContext;
	P<BundleActivator> activator;

	long id;
	String location;
	int state;
};

EndPackageOSGIInternal

#endif