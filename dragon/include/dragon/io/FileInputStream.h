#include "io.h"

#ifndef IO_FileInputStream_H 
#define IO_FileInputStream_H
#pragma once

#include "InputStream.h"
#include "IOException.h"
#include "FileNotFoundException.h"

BeginPackageIO

class _DragonExport FileInputStream :public InputStream
{
public:
	FileInputStream(String& name) throw(FileNotFoundException);
	FileInputStream(File* file) throw(FileNotFoundException);
	~FileInputStream();

public:
	virtual int read() throw(IOException);

	virtual int read(byte* b,int num) throw(IOException,NullPointerException);

	virtual int read(byte* b,int num,int off,int len) throw(IOException,NullPointerException,IndexOutOfBoundsException);

	virtual Long skip(Long n) throw(IOException);

	virtual int available() throw(IOException);

	virtual void close() throw(IOException);

private:
	int mhFile;
};

EndPackageIO

#endif