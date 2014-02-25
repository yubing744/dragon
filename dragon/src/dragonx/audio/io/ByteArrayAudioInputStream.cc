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
 * Created:     2014/02/25
 **********************************************************************/

#include <dragon/lang/Math.h>
#include <dragon/lang/System.h>
#include <dragon/lang/NullPointerException.h>
#include <dragon/lang/IndexOutOfBoundsException.h>
#include <dragon/util/logging/Logger.h>
#include <dragonx/audio/io/ByteArrayAudioInputStream.h>

Import dragon::lang;
Import dragon::util::logging;
Import dragonx::audio::io;

const Type* ByteArrayAudioInputStream::TYPE = TypeOf<ByteArrayAudioInputStream>();
static Logger* logger = Logger::getLogger(ByteArrayAudioInputStream::TYPE, ERROR);


ByteArrayAudioInputStream::ByteArrayAudioInputStream(const AudioFormat* format, const Array<byte> buf) {
    this->format = new AudioFormat(format);

    this->buf = buf;
    this->pos = 0;
    this->count = buf.length();
}

ByteArrayAudioInputStream::ByteArrayAudioInputStream(const AudioFormat* format, const Array<byte> buf, int offset, int length) {
    this->format = new AudioFormat(format);

    this->buf = buf;
    this->pos = offset;
    this->count = Math::min(offset + length, buf.length());
    this->markPos = offset;
}

ByteArrayAudioInputStream::~ByteArrayAudioInputStream() {
    this->buf.release();
    SafeDelete(this->format);
}

const AudioFormat* ByteArrayAudioInputStream::getFormat() const {
    return this->format;
}

void ByteArrayAudioInputStream::checkReadSize(int size) throw(IOException*) {
    const AudioFormat* fmt = this->getFormat();
    int frameSize = fmt->getFrameSize();

    if (size % frameSize != 0) {
        throw new IOException("the skip size must be multiple of frame size.");
    }
}

void ByteArrayAudioInputStream::open() {

}

wlong_u ByteArrayAudioInputStream::skip(wlong_u n) throw(IOException*) {
    this->checkReadSize(n);

    if (pos + n > count) {
        n = count - pos;
    }

    if (n < 0) {
        return 0;
    }

    pos += n;
    return n;
}

int ByteArrayAudioInputStream::read(byte* b, int num, int off, int len) throw(IOException*) {
    this->checkReadSize(len);

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

void ByteArrayAudioInputStream::close() throw(IOException*) {

}

void ByteArrayAudioInputStream::mark(int readlimit) {
    this->markPos = pos;
}

void ByteArrayAudioInputStream::reset() throw(IOException*) {
    pos = this->markPos;
}

bool ByteArrayAudioInputStream::markSupported() const {
    return true;
}

int ByteArrayAudioInputStream::available() const {
    return count - pos;
}
