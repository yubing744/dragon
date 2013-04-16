#include "io.h"

#ifndef IO_File_H 
#define IO_File_H
#pragma once

#include "IOException.h"

BeginPackage2(ProjectName,io)

//Import ProjectName::lang::gc;

class _DragonExport File :public Object//,public Comparable<File> 
{
public:
	File(P<String> pathname);
	File(const Char* pathname);

public:
	virtual bool canExecute();
	virtual bool canRead();
	virtual bool canWrite();
	virtual bool isHidden();
	virtual bool mkdir() throw(SecurityException);
	virtual bool mkdirs() throw(SecurityException);
	virtual bool exists() throw(SecurityException);
	virtual bool isDirectory() throw(SecurityException);
	virtual bool isFile() throw(SecurityException);
	virtual bool del();
	virtual bool remove();
	virtual Long length();
	virtual void deleteOnExit();
	virtual bool createNewFile() throw(IOException);
	virtual bool renameTo(File& dest);

	virtual P<Array<String>> list();
	virtual P<Array<String>> list(String filter);
	virtual P<Array<P<File>>> listFiles();
	virtual P<Array<P<File>>> listFiles(String filter);

	virtual String getName();
	virtual String getPath();

	virtual String getParent();
	virtual P<File> getParentFile();
	virtual bool isAbsolute();
	virtual String getAbsolutePath();
	virtual P<File> getAbsoluteFile();
	virtual String getCanonicalPath() throw(IOException);

private:
	P<String> mpPathName;
};


EndPackage2

#endif