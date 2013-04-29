#include "io.h"

#ifndef IO_Writer_H 
#define IO_Writer_H
#pragma once

#include "Appendable.h" 
#include "Closeable.h"
#include "Flushable.h"

BeginPackageIO

class _DragonExport Writer :public Object
	,public Appendable,public Closeable,public Flushable
{
protected:
	Writer(){};
	Writer(Object* lock){mLock=lock;};

public:
	virtual void close() throw(IOException) =0;
	virtual void flush() throw(IOException) =0;
	virtual void write(const Char* cbuf,int off,int len) throw(IOException,NullPointerException,IndexOutOfBoundsException) =0;

public:
	virtual Writer* append(Char c) throw(IOException);
	virtual Writer* append(CharSequence* csq) throw(IOException);
	virtual Writer* append(CharSequence* csq,int start,int end) throw(IOException);

	virtual void write(int c) throw(IOException);
	virtual void write(const Char* cbuf) throw(IOException);
	virtual void write(String& str) throw(IOException);
	virtual void write(String& str,int off,int len) throw(IOException,NullPointerException,IndexOutOfBoundsException);

protected:
	P<Object> mLock;
	P<File> mBaseFile;
};

EndPackageIO

#endif