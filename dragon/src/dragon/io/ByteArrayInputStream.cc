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

#include <dragon/lang/Math.h>
#include <dragon/lang/System.h>
#include <dragon/lang/NullPointerException.h>
#include <dragon/lang/IndexOutOfBoundsException.h>
#include <dragon/io/ByteArrayInputStream.h>
#include <dragon/util/logging/Logger.h>

Import dragon::io;
Import dragon::lang;
Import dragon::util::logging;

const Type* ByteArrayInputStream::TYPE = TypeOf<ByteArrayInputStream>();
static Logger* logger = Logger::getLogger(ByteArrayInputStream::TYPE, ERROR);

ByteArrayInputStream::ByteArrayInputStream(const Array<byte> buf) {
    this->buf = buf;
    this->pos = 0;
    this->count = buf.length();
}

ByteArrayInputStream::ByteArrayInputStream(const Array<byte> buf, int offset, int length) {
    this->buf = buf;
    this->pos = offset;
    this->count = Math::min(offset + length, buf.length());
    this->_mark = offset;
}

ByteArrayInputStream::~ByteArrayInputStream() {
    this->buf.release();
}

wlong_u ByteArrayInputStream::skip(wlong_u n) throw(IOException*) {
    if (pos + n > count) {
        n = count - pos;
    }

    if (n < 0) {
        return 0;
    }

    pos += n;
    return n;
}

int ByteArrayInputStream::read(byte* b, int num, int off, int len) throw(IOException*) {
    if (b == null) {
        throw new NullPointerException();
    } else if ((off < 0) || (off > num) || (len < 0) ||
           ((off + len) > num) || ((off + len) < 0)) {
        throw new IndexOutOfBoundsException();
    }

    if (pos >= count) {
        return -1;
    }

    if (pos + len > count) {
        len = count - pos;
    }

    if (len <= 0) {
        return 0;
    }

    System::arraycopy(buf.raw(), pos, b, off, len);
    pos += len;

    return len;
}

void ByteArrayInputStream::close() throw(IOException*) {

}

void ByteArrayInputStream::mark(int readlimit) {
    _mark = pos;
}

void ByteArrayInputStream::reset() throw(IOException*) {
    pos = _mark;
}

bool ByteArrayInputStream::markSupported() {
    return true;
}

int ByteArrayInputStream::available() {
    return count - pos;
}
