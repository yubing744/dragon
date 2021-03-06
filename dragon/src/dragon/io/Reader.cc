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

#include <dragon/io/Reader.h>

Import dragon::io;

int Reader::read() const throw(IOException*) {
	wchar_u ch;
	int read = this->read(&ch, 1, 0, 1);
	
	if (read > 0) {
		return (int)ch;
	}

	return -1;
}

int Reader::read(wchar_u* cbuf, int num) const throw(IOException*) {
	return this->read(cbuf, num, 0, num);
}

wlong_u Reader::skip(wlong_u n) throw(IOException*) {
	wlong_u i;

	for(i=0; i<n; i++) {
		if(this->read() == -1) {
			break;
		}
	}

	return i;
}