#include "zip.h"

#ifndef Util_Zip_ZipFile_H
#define Util_Zip_ZipFile_H
#pragma once

#include "zip_utils/zip.h"
#include "zip_utils/unzip.h"

BeginPackageZip

Import ZipUtils;

class _DragonExport ZipFile:public Object
{
private:
	ZipFile(String name, String password, int mode);

public:
	static P<ZipFile> Create(String name);
	static P<ZipFile> Open(String name);
	static P<ZipFile> Create(String name, String password);
	static P<ZipFile> Open(String name, String password);

	virtual P<ZipEntry> getEntry(String name);
	virtual P<InputStream> getInputStream(P<ZipEntry> entry) throw(IOException);
	virtual String getName();
	virtual P<List<P<ZipEntry>>> entries();

	virtual void addFile(String path, String file);

	virtual void unZip(P<ZipEntry> entry, String position);
	virtual void unZipTo(String position);
	virtual void setUnzipBaseDir(String dir);

	virtual int size();
	virtual void close() throw(IOException);

private:
	HZIP hZip;
	String pathName;
	String password;

};

EndPackageZip

#endif