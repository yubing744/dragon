#include "zip.h"

#ifndef Util_Zip_ZipEntry_H
#define Util_Zip_ZipEntry_H
#pragma once


#include "zip_utils/zip.h"
#include "zip_utils/unzip.h"

BeginPackageZip

Import ZipUtils;

class _DragonExport ZipEntry:public Object
{
friend class ZipFile;

private:
	ZipEntry(ZIPENTRY _zipEntry);

public:
	ZipEntry();

public:
	virtual String getName();
	virtual long getSize();
	virtual bool isDirectory();
	virtual int getIndex();

private:
	ZIPENTRY m_zipEntry;
};

EndPackageZip

#endif