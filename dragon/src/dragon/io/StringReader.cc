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
 * Created:     2014/04/27
 **********************************************************************/


#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/io/StringReader.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import dragon::io;

const Type* StringReader::TYPE = TypeOf<StringReader>();
static Logger* logger = Logger::getLogger(StringReader::TYPE, ERROR);

StringReader::StringReader(String* source) :cursor(0) {
    this->source = (String*)source->retain();
}

StringReader::~StringReader() {
    SafeRelease(this->source);
}

int StringReader::read(wchar_u* cbuf, int num, int off, int len) const
                    throw(IOException*, IndexOutOfBoundsException*) {
    if(off<0 || len<0 || off+len>num) {
        throw new IndexOutOfBoundsException("the read buffer argments");
    }

    StringReader* reader = const_cast<StringReader*>(this);

    int size = this->source->length();
    int last = size - this->cursor;
    int read = last > len ? len : last;

    this->source->getChars(this->cursor, this->cursor + read, cbuf, off);
    reader->cursor += read;

    return read;
}

void StringReader::close() throw(IOException*) {

}
