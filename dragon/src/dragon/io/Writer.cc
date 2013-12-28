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

#include <dragon/io/Writer.h>

Import dragon::io;

Writer* Writer::append(wchar_u c) throw(IOException*) {
	this->write(c);
	return this;
}

Writer* Writer::append(const CharSequence* csq) throw(IOException*) {
	this->write(csq);
	return this;
}

Writer* Writer::append(const CharSequence* csq, int start, int end) throw(IOException*) {
	this->write(csq, start, end);
	return this;
}

Writer* Writer::append(const String& str) throw(IOException*) {
	this->write(str);
	return this;
}

Writer* Writer::append(const String& str, int off, int len) throw(IOException*, IndexOutOfBoundsException*) {
	this->write(str, off, len);
	return this;
}

void Writer::write(int c) throw(IOException*) {
	wchar_u ch[2];
	ch[0] = (wchar_u)c;
	ch[1] = 0;

	this->write(ch);
}

void Writer::write(const wchar_u* cbuf) throw(IOException*) {
	size_t size = 0;
	wchar_u* p = const_cast<wchar_u*>(cbuf);

	while( *p != 0) {
		size++;
	}

	this->write(cbuf, 0, size);
}

void Writer::write(const CharSequence* csq) throw(IOException*) {
	String* str = csq->toString();
	this->write(str->toChars(), 0, str->length());
	SafeDelete(str);
}

void Writer::write(const CharSequence* csq, int start, int end) throw(IOException*) {
	String* str = csq->toString();
	String* newStr = str->substring(start, end);

	this->write(newStr->toCharArray(), 0, newStr->length());

	SafeDelete(newStr);
	SafeDelete(str);	
}

void Writer::write(const String& str) throw(IOException*) {
	this->write(str.toChars(), 0, str.length());
}

void Writer::write(const String& str, int off, int len) throw(IOException*, IndexOutOfBoundsException*) {
	this->write(str.toChars(), off, len);
}
