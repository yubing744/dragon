#include "io.h"

#ifndef IO_FileReader_H 
#define IO_FileReader_H
#pragma once

#include "InputStreamReader.h"

BeginPackageIO

class _DragonExport FileReader :public InputStreamReader
{
public:
	FileReader(String& fileName) throw(FileNotFoundException);
	FileReader(File* file) throw(FileNotFoundException);
	~FileReader(){close();};

public:
	virtual void close() throw(IOException);
	virtual int read(Char* cbuf,int num,int off,int len) 
					throw(IOException,NullPointerException,IndexOutOfBoundsException);

	virtual Long skip(Long n) throw(IOException);
	virtual bool ready() throw(IOException);
private:
	int mhFile;

};

EndPackageIO

#endif