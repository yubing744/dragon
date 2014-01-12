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

#include <dragon/io/OutputStream.h>

Import dragon::lang;
Import dragon::io;

void OutputStream::reset() {

}

void OutputStream::write(int b) throw(IOException*) {
	const byte buf[] = {b};
	this->write(buf, 1, 0, 1);
}

void OutputStream::write(const byte* b, int num) throw(IOException*) {
	this->write(b, num, 0, num);
}

void OutputStream::write(const Array<byte> b) throw(IOException*) {
    this->write(b.raw(), b.length(), 0, b.length());
}

void OutputStream::write(const Array<byte> b, int off, int len) throw(IOException*) {
    this->write(b.raw(), b.length(), off, len);
}