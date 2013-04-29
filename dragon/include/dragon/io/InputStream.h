#include "io.h"

#ifndef IO_InputStream_H 
#define IO_InputStream_H
#pragma once

#include "Closeable.h"
#include "IOException.h"

BeginPackage2(ProjectName,io)

class _DragonExport InputStream :public Object,public Closeable
{
protected:
	InputStream(){};

public:
	virtual int read() throw(IOException) =0;
	virtual void close() throw(IOException) =0;
	virtual int available() throw(IOException)=0;

public:
	virtual int read(byte* b,int num) throw(IOException,NullPointerException);
	virtual int read(byte* b,int num,int off,int len) throw(IOException,NullPointerException,IndexOutOfBoundsException );

	virtual Long skip(Long n) throw(IOException);


protected:
	P<File> mBaseFile;
};

EndPackage2

#endif