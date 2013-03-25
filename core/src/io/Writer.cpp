#include "Writer.h"

Import IO;

Writer* Writer::append(Char c) throw(IOException)
{
	this->write(c);
	return this;
}

Writer* Writer::append(CharSequence* csq) throw(IOException)
{
	this->write(csq->toString());
	return this;
}

Writer* Writer::append(CharSequence* csq,int start,int end) throw(IOException)
{
	this->write(csq->toString().substring(start,end));
	return this;
}

void Writer::write(int c) throw(IOException)
{
	Char ch[2];
	ch[0]=(Char)c;
	ch[1]=0;

	this->write(ch);
}

void Writer::write(const Char* cbuf) throw(IOException)
{
	this->write(cbuf,0,wcslen(cbuf));
}

void Writer::write(String& str) throw(IOException)
{
	this->write(str.toCharArray(),0,str.length());
}

void Writer::write(String& str,int off,int len) throw(IOException,NullPointerException,IndexOutOfBoundsException)
{
	this->write(str.substring(off,off+len));
}
