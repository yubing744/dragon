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

#include <dragon/lang/System.h>
#include <dragon/lang/IllegalArgumentException.h>
#include <dragon/io/BufferedOutputStream.h>
#include <dragon/util/logging/Logger.h>
 
Import dragon::io;
Import dragon::lang;
Import dragon::util::logging;

const Type* BufferedOutputStream::TYPE = TypeOf<BufferedOutputStream>();
static Logger* logger = Logger::getLogger(BufferedOutputStream::TYPE, ERROR);

BufferedOutputStream::BufferedOutputStream(OutputStream* out) 
    :FilterOutputStream(out) {
    byte* buf = new byte[8192];
    this->buf = Array<byte>(buf, 8192);
}

BufferedOutputStream::BufferedOutputStream(OutputStream* out, int size) 
    :FilterOutputStream(out) {
    if (size <= 0) {
        throw new IllegalArgumentException("Buffer size <= 0");
    }

    byte* buf = new byte[size];
    this->buf = Array<byte>(buf, size);
}

BufferedOutputStream::~BufferedOutputStream() {

}

void BufferedOutputStream::flushBuffer() throw(IOException*) {
    if (count > 0) {
        out->write(buf, 0, count);
        count = 0;
    }
}

void BufferedOutputStream::write(const byte* b, int num, int off, int len) throw(IOException*) {
    if (len >= buf.length()) {
        /* If the request length exceeds the size of the output buffer,
           flush the output buffer and then write the data directly.
           In this way buffered streams will cascade harmlessly. */
        flushBuffer();
        out->write(b, num, off, len);
        return;
    }

    if (len > num - count) {
        flushBuffer();
    }

    System::arraycopy(b, off, buf.raw(), count, len);
    count += len;
}

void BufferedOutputStream::flush() throw(IOException*) {
    flushBuffer();
    out->flush();
}