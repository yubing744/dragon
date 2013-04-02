#include "FileWriter.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

Import IO;

FileWriter::FileWriter(const Char* fileName) throw(IOException)
{
	mBaseFile=new File(fileName);

	if(_wsopen_s(&mhFile,mBaseFile->getCanonicalPath(),_O_BINARY|_O_WRONLY|_O_WTEXT,_SH_DENYNO,0)!=0)
	{
		throw FileNotFoundException();
	}
}

FileWriter::FileWriter(const Char* fileName,bool append) throw(IOException)
{
	mBaseFile=new File(fileName);

	int oflag=_O_BINARY|_O_WRONLY|_O_WTEXT;
	if(append) oflag=_O_BINARY|_O_WRONLY|_O_APPEND|_O_WTEXT;

	if(_wsopen_s(&mhFile,mBaseFile->getCanonicalPath(),oflag,_SH_DENYNO,0)!=0)
	{
		throw FileNotFoundException();
	}
}

FileWriter::FileWriter(File* file) throw(IOException)
{
	mBaseFile=file;

	if(_wsopen_s(&mhFile,mBaseFile->getCanonicalPath(),_O_BINARY|_O_WRONLY|_O_WTEXT,_SH_DENYNO,0)!=0)
	{
		throw FileNotFoundException();
	}
}

FileWriter::FileWriter(File* file,bool append) throw(IOException)
{
	mBaseFile=file;

	int oflag=_O_BINARY|_O_WRONLY|_O_WTEXT;
	if(append) oflag=_O_BINARY|_O_WRONLY|_O_APPEND|_O_WTEXT;

	if(_wsopen_s(&mhFile,mBaseFile->getCanonicalPath(),oflag,_SH_DENYNO,0)!=0)
	{
		throw FileNotFoundException();
	}
}

void FileWriter::write(const Char* cbuf,int off,int len) 
					throw(IOException,NullPointerException,IndexOutOfBoundsException)
{
	if(cbuf==null)
	{
		throw NullPointerException();
	}

	if(off<0 || len<0 || size_t(off+len)>wcslen(cbuf))
	{
		throw IndexOutOfBoundsException();
	}

	if(_write(mhFile,cbuf+off*2,len*2)==-1)
	{
		throw IOException();
	}	
}

void FileWriter::close() throw(IOException)
{
	if(mhFile!=0)
	{
		if(_close(mhFile)==-1)
		{
			throw IOException();
		}

		mhFile=0;
	}
}

void FileWriter::flush() throw(IOException)
{
	if(_commit(mhFile))
	{
		throw IOException();
	}
}