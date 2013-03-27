#include "osgi_framework.h"

#ifndef OSGI_Framework_BundleData_H 
#define OSGI_Framework_BundleData_H 
#pragma once

BeginPackageOSGIFramework

class _DragonExport BundleData: public Object
{

public:

	P<Array<String>> getClassPaths()
	{
		return classPaths;
	}
	void setClassPaths(P<Array<String>> classPaths)
	{
		this->classPaths = classPaths;
	}

	P<Array<String>> getExportedPackages()
	{
		return exportedPackages;
	}
	void setExportedPackages(P<Array<String>> exportedPackages)
	{
		this->exportedPackages = exportedPackages;
	}

	P<Array<String>> getImportedPackages()
	{
		return importedPackages;
	}
	void setImportedPackages(P<Array<String>> importedPackages)
	{
		this->importedPackages = importedPackages;
	}

	P<Array<String>> getRequiredBundles()
	{
		return requiredBundles;
	}
	void setRequiredBundles(P<Array<String>> requiredBundles)
	{
		this->requiredBundles = requiredBundles;
	}


	String getDescription()
	{
		return description;
	}
	void setDescription(String description)
	{
		this->description = description;
	}

	String getSymbolicName()
	{
		return symbolicName;
	}
	void setSymbolicName(String symbolicName)
	{
		this->symbolicName = symbolicName;
	}

	String getActivator()
	{
		return activator;
	}
	void setActivator(String activator)
	{
		this->activator = activator;
	}

	String getName()
	{
		return name;
	}
	void setName(String name)
	{
		this->name = name;
	}


	String getNativeLib()
	{
		return nativeLib;
	}
    void setNativeLib(String nativeLib)
	{
		this->nativeLib = nativeLib;
	}

	String getLocation()
	{
		return location;
	}
    void setLocation(String location)
	{
		this->location = location;
	}

private:
	String name;
	String nativeLib;
	String location;
	String description;
	String symbolicName;
	String activator;

	P<Array<String>> classPaths;
	P<Array<String>> exportedPackages;
	P<Array<String>> importedPackages;
	P<Array<String>> requiredBundles;
};

EndPackageOSGIFramework

#endif