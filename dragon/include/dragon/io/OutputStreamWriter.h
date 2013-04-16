#include "io.h"

#ifndef IO_OutputStreamWriter_H 
#define IO_OutputStreamWriter_H
#pragma once

#include "Writer.h"
#include "OutputStream.h"

BeginPackageIO

class _DragonExport OutputStreamWriter :public Writer
{
public:
	OutputStreamWriter(OutputStream* out);
	OutputStreamWriter(OutputStream* out, String& charsetName);
	~OutputStreamWriter(){close();}
protected:
	OutputStreamWriter(){};

public:
	virtual void close() throw(IOException);
	virtual void flush() throw(IOException);
	virtual void write(const Char* cbuf,int off,int len) 
					throw(IOException,NullPointerException,IndexOutOfBoundsException);
	virtual String& getEncoding();

protected:
	P<OutputStream> mOut;
	P<String> mCharsetName;
};

EndPackageIO

#endif