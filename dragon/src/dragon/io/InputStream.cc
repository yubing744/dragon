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

#include <dragon/io/InputStream.h>
#include <dragon/lang/UnsupportedOperationException.h>

Import dragon::lang;
Import dragon::io;


int InputStream::read(byte* b, int num) throw(IOException*) {
	return read(b, num, 0, num);
}

int InputStream::read() throw(IOException*) {
	byte buf[1];

	if (read(buf, 1)) {
		return buf[0];
	} 
	
    return -1;
}

bool InputStream::markSupported() const {
    return false;
}

void InputStream::mark(int readlimit) {
    throw new UnsupportedOperationException("this input stream not support mark!");
}

void InputStream::reset() throw(IOException*) {
    throw new UnsupportedOperationException("this input stream not support reset!");
}

int InputStream::available() const {
    throw new UnsupportedOperationException("this input stream not support available!");
}