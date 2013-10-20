#include "InputStreamReader.h"

Import IO;

InputStreamReader::InputStreamReader(InputStream* in) {
	mIn=in;
	mCharsetName=new String(L"Unicode");
}

InputStreamReader::InputStreamReader(InputStream* in,String& charsetName)throw(UnsupportedEncodingException) {
	mIn=in;
	mCharsetName=&charsetName;
}

void InputStreamReader::close() throw(IOException) {
	mIn->close();
}

int InputStreamReader::read(Char* cbuf,int num,int off,int len) 
					throw(IOException, NullPointerException, IndexOutOfBoundsException) {
	return mIn->read((byte*)cbuf,num*2,off*2,len*2)/2;
}

bool InputStreamReader::ready() throw(IOException) {
	return mIn->available()/2>1;
}

String& InputStreamReader::getEncoding() {
	return *mCharsetName;
}