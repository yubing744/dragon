#include "FileInputStream.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

Import IO;

FileInputStream::FileInputStream(String& name) throw(FileNotFoundException)
{
    mBaseFile=new File(name);

    if(_wsopen_s(&mhFile,mBaseFile->getCanonicalPath(),_O_RDONLY,_SH_DENYNO,0)!=0)
    {
        throw FileNotFoundException();
    }
}

FileInputStream::FileInputStream(File* file) throw(FileNotFoundException)
{
    mBaseFile=file;

    if(_wsopen_s(&mhFile,mBaseFile->getCanonicalPath(),_O_RDONLY,_SH_DENYNO,0)!=0)
    {
        throw FileNotFoundException(L"File not found!");
    }
}

FileInputStream::~FileInputStream() 
{
    this->close();
}

int FileInputStream::read() throw(IOException)
{
    byte b;

    if(_eof(mhFile)==1) return -1;

    int byteRead=-1;
    if((byteRead =_read(mhFile,&b,1))<= 0)
    {
        throw IOException(L"Problem reading file!");
    }

    return (int)b;
}

int FileInputStream::read(byte* b,int num) 
    throw(IOException,NullPointerException)
{
    int byteRead=-1;
    if(b==null)
    {
        throw NullPointerException();
    }

    if((byteRead =_read(mhFile,b,num))<= 0)
    {
        throw IOException();
    }

    return byteRead;
}

int FileInputStream::read(byte* b,int num,int off,int len)
    throw(IOException,NullPointerException,IndexOutOfBoundsException)
{
    if(len==0) return 0;

    if(_eof(mhFile)==1) return -1;

    if(b==null)
    {
        throw NullPointerException();
    }

    if(off<0 || len<0 || off+len>num)
    {
        throw IndexOutOfBoundsException();
    }

    return this->read(b+off,len);
}

Long FileInputStream::skip(Long n) throw(IOException)
{
    if(n<0) return 0L;

    Long newPos=-1L;

    newPos=_lseeki64(mhFile,n,SEEK_CUR);
    if(newPos==-1L)
    {
        throw IOException(L"Problem reading file!");
    }

    return newPos;
}

int FileInputStream::available()
{
    return _filelength(mhFile)-_tell(mhFile);
}

void FileInputStream::close() throw(IOException)
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