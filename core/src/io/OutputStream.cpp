#include "OutputStream.h"


Import ProjectName::lang;
Import ProjectName::io;

void OutputStream::write(byte* b,int num) 
	throw(IOException,NullPointerException)
{
	if(b==null)
	{
		throw NullPointerException();
	}

	for(int i=0;i<num;i++)
	{
		this->write(*(b++));
	}
}

void OutputStream::write(byte* b,int num,int off,int len) 
	throw(IOException,NullPointerException,IndexOutOfBoundsException)
{
	if(b==null)
	{
		throw NullPointerException();
	}

	if(off<0 || len<0 || off+len>num)
	{
		throw IndexOutOfBoundsException();
	}

	this->write(b+off,len);
}