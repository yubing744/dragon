#include "io.h"

#ifndef IO_OutputStream_H 
#define IO_OutputStream_H
#pragma once

#include "Closeable.h"
#include "Flushable.h"
#include "IOException.h"

BeginPackage2(ProjectName,io)

class _DragonExport OutputStream 
	:public Object, public Closeable, public Flushable
{
protected:
	OutputStream(){};

public:
	virtual void write(int b) throw(IOException) =0;
	virtual void close() throw(IOException) =0;
	virtual void flush() throw(IOException) =0;

public:
	virtual void write(byte* b,int num) 
		throw(IOException,NullPointerException);

	virtual void write(byte* b,int num,int off,int len) 
		throw(IOException,NullPointerException,IndexOutOfBoundsException);

protected:
	P<File> baseFile;
};

EndPackage2

#endif