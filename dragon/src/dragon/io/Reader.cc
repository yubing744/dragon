#include "Reader.h"

Import IO;

int Reader::read() throw(IOException)
{
	Char ch;
	this->read(&ch,1,0,1);
	return (int)ch;
}

int Reader::read(Char* cbuf,int num) throw(IOException,NullPointerException)
{
	return this->read(cbuf,num,0,num);
}

Long Reader::skip(Long n) throw(IOException)
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