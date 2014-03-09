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

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/06/26
 **********************************************************************/

#include <dragon/io/OutputStreamWriter.h>

Import dragon::io;

OutputStreamWriter::OutputStreamWriter(const OutputStream* out) {
	this->innerStream = const_cast<OutputStream*>(out);
	this->innerStream->retain();

	this->charsetName = new String(L"UTF-8");
}

OutputStreamWriter::OutputStreamWriter(const OutputStream* out, const String& charsetName) {
	this->innerStream = const_cast<OutputStream*>(out);
	this->innerStream->retain();

	this->charsetName = new String(charsetName);
}

OutputStreamWriter::~OutputStreamWriter(){
	SafeDelete(this->charsetName);
	SafeRelease(this->innerStream);
}

void OutputStreamWriter::close() throw(IOException*) {
	if (this->innerStream != NULL) {
		this->innerStream->close();
	}
}

void OutputStreamWriter::flush() throw(IOException*) {
	if (this->innerStream != NULL) {
		this->innerStream->flush();
	}
}

void OutputStreamWriter::write(const wchar_u* cbuf, int off, int len) 
	throw(IOException*, IndexOutOfBoundsException*)
{
	String* text = new String(cbuf, off, len);

	char* charset = this->charsetName->toCString();
	const Array<byte> data = text->getBytes(charset);
	this->innerStream->write(data.raw(), data.size(), 0, data.size());
	free(charset);

	SafeDelete(text);
}

const String* OutputStreamWriter::getEncoding() const {
	return this->charsetName;
}
