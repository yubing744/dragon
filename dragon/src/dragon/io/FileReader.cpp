#include "FileReader.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

Import IO;

FileReader::FileReader(String& fileName) throw(FileNotFoundException)
{
	mBaseFile=new File(fileName);

	if(_wsopen_s(&mhFile,mBaseFile->getCanonicalPath(),_O_RDONLY|_O_WTEXT,_SH_DENYNO,0)!=0)
	{
		throw FileNotFoundException();
	}
}

FileReader::FileReader(File* file) throw(FileNotFoundException)
{
	mBaseFile=file;

	if(_wsopen_s(&mhFile,mBaseFile->getCanonicalPath(),_O_RDONLY|_O_WTEXT,_SH_DENYNO,0)!=0)
	{
		throw FileNotFoundException();
	}
}

int FileReader::read(Char* cbuf,int num,int off,int len) 
					throw(IOException,NullPointerException,IndexOutOfBoundsException)
{
	if(len==0) return 0;

	if(_eof(mhFile)==1) return -1;

	if(cbuf==null)
	{
		throw NullPointerException();
	}

	if(off<0 || len<0 || off+len>num)
	{
		throw IndexOutOfBoundsException();
	}

	int byteRead=-1;

	if((byteRead =_read(mhFile,cbuf,num*2))<= 0)
	{
		throw IOException();
	}

	return byteRead/2;
}

Long FileReader::skip(Long n) throw(IOException)
{
	if(n<0) return 0L;

	Long newPos=-1L;

	newPos=_lseeki64(mhFile,n*2,SEEK_CUR);
	if(newPos==-1L)
	{
		throw IOException(L"Problem reading file!");
	}

	return newPos;
}

bool FileReader::ready() throw(IOException)
{
	return (_filelength(mhFile)-_tell(mhFile))/2>1;
}

void FileReader::close() throw(IOException)
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