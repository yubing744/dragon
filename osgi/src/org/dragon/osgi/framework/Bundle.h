#include "osgi_framework.h"

#ifndef OSGI_Framework_Bundle_H 
#define OSGI_Framework_Bundle_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport Bundle
{
public:
	enum STATE
	{
		UNINSTALLED = 0x00000001,
		INSTALLED   = 0x00000002,
		RESOLVED    = 0x00000004,
		STARTING    = 0x00000008,
		STOPPING    = 0x00000010,
		ACTIVE      = 0x00000020
	};

public:
	virtual ~Bundle(){};

public:
	virtual long getBundleId()=0;
	virtual P<BundleData> getBundleData()=0;
	virtual P<Map<String,String>> getHeaders()=0;
	virtual String getLocation()=0;
	virtual String getSymbolicName()=0;
	virtual P<Class<Object>> loadClass(const String& name) 
		throw(ClassNotFoundException) =0;

	virtual int  getState()=0;
	virtual void start() throw(BundleException)=0;
	virtual void stop() throw(BundleException)=0;
	virtual void uninstall() throw(BundleException)=0;
	virtual void update() throw(BundleException)=0;
	virtual void update(P<InputStream> stream) throw(BundleException)=0;
};

EndPackageOSGIFramework

#endif