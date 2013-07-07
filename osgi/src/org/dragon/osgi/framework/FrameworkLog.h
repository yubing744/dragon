#include "osgi_framework.h"

#ifndef OSGI_Framework_FrameworkLog_H 
#define OSGI_Framework_FrameworkLog_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport FrameworkLog
{
public:
	enum LOGLEVEL
	{
		INFO    = 0x00000001,
		DEBUG   = 0x00000002,
		WARN    = 0x00000004,
		ERR   = 0x00000008
	};


public:
	virtual ~FrameworkLog(){};

public:

	virtual void setLevel(int level)=0;

	virtual void info(String message)=0;
	virtual void debug(String message)=0;
	virtual void warn(String message)=0;
	virtual void error(String message)=0;


	virtual void setWriter(P<Writer> newWriter, bool append)=0;

};

EndPackageOSGIFramework

#endif