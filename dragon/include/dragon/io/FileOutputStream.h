#include "io.h"

#ifndef IO_FileOutputStream_H 
#define IO_FileOutputStream_H
#pragma once

#include "OutputStream.h"

BeginPackageIO

class _DragonExport FileOutputStream :public OutputStream
{
public:
	FileOutputStream(const Char* name)  throw(FileNotFoundException);
	FileOutputStream(const Char* name,bool append)  throw(FileNotFoundException);
	FileOutputStream(File* file) throw(FileNotFoundException);
	FileOutputStream(File* file, bool append) throw(FileNotFoundException);
	~FileOutputStream(){this->close();};

public:
	virtual void write(int b) throw(IOException);
	virtual void close() throw(IOException);
	virtual void flush() throw(IOException);

	virtual void write(byte* b,int num) 
		throw(IOException,NullPointerException);

	virtual void write(byte* b,int num,int off,int len) 
		throw(IOException,NullPointerException,IndexOutOfBoundsException);

private:
	int mhFile;
};

EndPackageIO

#endif