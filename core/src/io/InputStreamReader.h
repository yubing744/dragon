#include "io.h"

#ifndef IO_InputStreamReader_H 
#define IO_InputStreamReader_H
#pragma once

#include "Reader.h"

BeginPackageIO

class _DragonExport InputStreamReader :public Reader
{
public:
	InputStreamReader(){};
	InputStreamReader(InputStream* in);
	InputStreamReader(InputStream* in,String& charsetName)throw(UnsupportedEncodingException);

public:
	virtual void close() throw(IOException);
	virtual int read(Char* cbuf,int num,int off,int len) 
					throw(IOException,NullPointerException,IndexOutOfBoundsException);
	virtual String& getEncoding();

	virtual bool ready() throw(IOException);

protected:
	P<InputStream> mIn;
	P<String> mCharsetName;
};

EndPackageIO

#endif