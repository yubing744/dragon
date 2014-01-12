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


#include <dragon/io/FilterOutputStream.h>
#include <dragon/util/logging/Logger.h>

Import dragon::io;
Import dragon::util::logging;

const Type* FilterOutputStream::TYPE = TypeOf<FilterOutputStream>();
static Logger* logger = Logger::getLogger(FilterOutputStream::TYPE, ERROR);

FilterOutputStream::FilterOutputStream(OutputStream* out) 
    :out(out) {

}

FilterOutputStream::~FilterOutputStream() {

}

void FilterOutputStream::write(const byte* b, int num, int off, int len) throw(IOException*) {
    out->write(b, num, off, len);
}

void FilterOutputStream::flush() throw(IOException*) {
    out->flush();
}

void FilterOutputStream::close() throw(IOException*) {
    out->close();
}