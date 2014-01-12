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
 * Created:     2014/01/12
 **********************************************************************/


#include <dragon/io/FilterInputStream.h>
#include <dragon/util/logging/Logger.h>

Import dragon::io;
Import dragon::util::logging;

const Type* FilterInputStream::TYPE = TypeOf<FilterInputStream>();
static Logger* logger = Logger::getLogger(FilterInputStream::TYPE, ERROR);

FilterInputStream::FilterInputStream(InputStream* in) 
    :in(in) {

}

FilterInputStream::~FilterInputStream() {

}

wlong_u FilterInputStream::skip(wlong_u n) throw(IOException*) {
    return in->skip(n);
}

int FilterInputStream::read(byte* b, int num, int off, int len) throw(IOException*) {
    return in->read(b, num, off, len);
}

void FilterInputStream::close() throw(IOException*) {
    in->close();
}

void FilterInputStream::mark(int readlimit) {
    in->mark(readlimit);
}

void FilterInputStream::reset() throw(IOException*) {
    in->reset();
}

bool FilterInputStream::markSupported() {
    return in->markSupported();
}

int FilterInputStream::available() {
    return in->available();
}