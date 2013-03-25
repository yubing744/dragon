#include "io.h"

#ifndef IO_Reader_H 
#define IO_Reader_H
#pragma once

#include "Closeable.h"

BeginPackageIO

class _DragonExport Reader :public Object,public Closeable
{
protected:
	Reader(){};
	Reader(Object* lock){mLock=lock;};

public:
	virtual void close() throw(IOException) =0;
	virtual int read(Char* cbuf,int num,int off,int len) 
					throw(IOException,NullPointerException,IndexOutOfBoundsException) =0;
	virtual bool ready() throw(IOException) =0;

public:
	virtual int read() throw(IOException);
	virtual int read(Char* cbuf,int num) 
					throw(IOException,NullPointerException);

	virtual Long skip(Long n) throw(IOException);

public:

protected:
	P<Object> mLock;
	P<File> mBaseFile;
};

EndPackageIO

#endif