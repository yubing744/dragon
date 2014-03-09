/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <dragon/lang/Array.h>
#include <dragon/lang/Arrays.h>
#include <dragon/io/InputStreamReader.h>

Import dragon::lang;
Import dragon::io;

InputStreamReader::InputStreamReader(const InputStream* in) {
	this->innerStream = const_cast<InputStream*>(in);
    this->innerStream->retain();
    
	this->charsetName = new String(L"UTF-8");
}

InputStreamReader::InputStreamReader(const InputStream* in, const String& charset) throw(UnsupportedEncodingException*) {
    this->innerStream = const_cast<InputStream*>(in);
    this->innerStream->retain();

    this->charsetName = new String(charset);
}

InputStreamReader::~InputStreamReader() {
    this->close();
    SafeDelete(this->charsetName);
    SafeRelease(this->innerStream);
}

void InputStreamReader::close() throw(IOException*) {
	this->innerStream->close();
}

int InputStreamReader::read(wchar_u* cbuf, int num, int off, int len) const
					throw(IOException*, IndexOutOfBoundsException*) {
    if(off<0 || len<0 || off+len>num) {
        throw new IndexOutOfBoundsException("the write buffer argments");
    }

    int bufSize = len * 2;
    byte* buf = (byte*)malloc(bufSize);

	int readByteCount = 0;

    const Array<byte> charset = this->charsetName->getBytes("UTF-8");

    int totalCount = 0;
    int innerOffset = off;

    while((readByteCount = this->innerStream->read(buf, bufSize, 0, bufSize)) > 0) {
        String* text = new String(Array<byte>(buf, readByteCount, false), 0, readByteCount, charset.raw());
        
        const wchar_u* data = text->toChars();
        Arrays<wchar_u>::copyOf(data, 0, cbuf, innerOffset, text->length()); 
        innerOffset += text->length();
        totalCount += text->length();

        SafeDelete(text);
    }

    SafeFree(buf);

    return totalCount;
}

const String* InputStreamReader::getEncoding() const {
	return this->charsetName;
}

