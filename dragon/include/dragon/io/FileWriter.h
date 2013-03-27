#include "io.h"

#ifndef IO_FileWriter_H 
#define IO_FileWriter_H
#pragma once

#include "OutputStreamWriter.h"

BeginPackageIO

class _DragonExport FileWriter :public OutputStreamWriter
{
public:
	FileWriter(const Char* fileName) throw(IOException);
	FileWriter(const Char* fileName,bool append) throw(IOException);
	FileWriter(File* file) throw(IOException);
	FileWriter(File* file,bool append) throw(IOException);
	~FileWriter(){close();}

public:
	virtual void close() throw(IOException);
	virtual void flush() throw(IOException);
	virtual void write(const Char* cbuf,int off,int len) 
					throw(IOException,NullPointerException,IndexOutOfBoundsException);
private:
	int mhFile;
};

EndPackageIO

#endif