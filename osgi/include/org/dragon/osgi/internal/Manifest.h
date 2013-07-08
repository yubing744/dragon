#include "osgi_internal.h"

#ifndef OSGI_Internal_Manifest_H 
#define OSGI_Internal_Manifest_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageOSGIInternal

Import org::dragon::osgi::framework;

class _DragonExport Manifest 
	:public Object
{
public:
	Manifest();
	Manifest(P<File> file);

    virtual P<Map<String, String>> getEntries();
	virtual void setFile(P<File> file);
protected:
	virtual void parseFile();

private:
	void addEnity(String entity);

private:
	P<Map<String, String>> entries;
	P<File> file;
};

EndPackageOSGIInternal

#endif