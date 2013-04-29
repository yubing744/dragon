#include "OutputStreamWriter.h"

Import IO;

OutputStreamWriter::OutputStreamWriter(OutputStream* out)
{
	mOut=out;
	mCharsetName=new String(L"Unicode");
}

OutputStreamWriter::OutputStreamWriter(OutputStream* out, String& charsetName)
{
	mOut=out;
	mCharsetName=&charsetName;
}

void OutputStreamWriter::close() throw(IOException)
{
	mOut->close();
}

void OutputStreamWriter::flush() throw(IOException)
{
	mOut->flush();
}

void OutputStreamWriter::write(const Char* cbuf,int off,int len) 
		throw(IOException,NullPointerException,IndexOutOfBoundsException)
{
	byte* b=(byte*)cbuf;
	mOut->write(b,wcslen(cbuf)*2,off*2,len*2);
}

String& OutputStreamWriter::getEncoding()
{
	return *mCharsetName;
}