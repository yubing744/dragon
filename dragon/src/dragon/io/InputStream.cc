#include "InputStream.h"


Import ProjectName::lang;
Import ProjectName::io;


int InputStream::read(byte* b,int num)
{
	int byteRead=-1;
	if(b==null)
	{
		throw NullPointerException(L"InputStream::read(byte* b,int len) b==null !");
	}
	
	int i;

	for(i=0;i<num;i++)
	{
		if((*(b++)=this->read())==-1)
		{
			break;
		}
	}

	return i;
}

int InputStream::read(byte* b,int num,int off,int len)
{
	if(len==0) return 0;

	int tb=this->read();
	if(tb==-1)
	{
		return -1;
	}
	else
	{
		*(b+off)=(byte)tb;
	}

	if(off<0 || len<0 || off+len>num)
	{
		throw IndexOutOfBoundsException(L"FileInputStream::read(byte* b,int off,int len)");
	}

	return this->read(b+off+1,len-1);
}



Long InputStream::skip(Long n)
{
	Long i;

	for(i=0;i<n;i++)
	{
		if(this->read()==-1)
		{
			break;
		}
	}

	return i;
}