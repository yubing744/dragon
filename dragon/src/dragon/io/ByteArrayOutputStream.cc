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
 * Created:     2014/01/08
 **********************************************************************/


#include <dragon/io/ByteArrayOutputStream.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/lang/IndexOutOfBoundsException.h>
#include <dragon/lang/System.h>

Import dragon::io;
Import dragon::lang;
Import dragon::util::logging;

const Type* ByteArrayOutputStream::TYPE = TypeOf<ByteArrayOutputStream>();
static Logger* logger = Logger::getLogger(ByteArrayOutputStream::TYPE, ERROR);

#define DEFAULT_BYTE_ARRAY_INIT_SIZE 64

ByteArrayOutputStream::ByteArrayOutputStream() 
    :count(DEFAULT_BYTE_ARRAY_INIT_SIZE) {
    byte* newValue = new byte[DEFAULT_BYTE_ARRAY_INIT_SIZE];
    this->buf = Array<byte>(newValue, DEFAULT_BYTE_ARRAY_INIT_SIZE);
}

ByteArrayOutputStream::ByteArrayOutputStream(int size) 
    :count(size) {
    byte* newValue = new byte[size];
    this->buf = Array<byte>(newValue, size);
}

ByteArrayOutputStream::~ByteArrayOutputStream() {
    this->buf.release();
}

void ByteArrayOutputStream::write(const byte* b, int num, int off, int len) throw(IOException*) {
    if ((off < 0) || (off > num) || (len < 0) ||
            ((off + len) > num) || ((off + len) < 0)) {
        throw new IndexOutOfBoundsException();
    } else if (len == 0) {
        return;
    }

    int newcount = count + len;

    if (newcount > buf.length()) {
        int newSize = Math::max(buf.length() << 1, newcount);
        byte* newbuf = new byte[newSize];
        System::arraycopy(buf.raw(), 0, newbuf, 0, count);
        buf = Array<byte>(newbuf, newSize);
    }

    System::arraycopy(b, off, buf.raw(), count, len);
    count = newcount;
}

void ByteArrayOutputStream::flush() throw(IOException*) {

}

void ByteArrayOutputStream::close() throw(IOException*) {

}

Array<byte> ByteArrayOutputStream::toByteArray() const {
    byte* newbuf = new byte[count];
    System::arraycopy(buf.raw(), 0, newbuf, 0, count);
    return Array<byte>(newbuf, count);
}

void ByteArrayOutputStream::writeTo(OutputStream* out) {
    out->write(buf.raw(), buf.size(), 0, count);
}
