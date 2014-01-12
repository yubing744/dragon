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
#include <dragon/io/BufferedInputStream.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/lang/IndexOutOfBoundsException.h>

Import dragon::io;
Import dragon::lang;
Import dragon::util::logging;

const Type* BufferedInputStream::TYPE = TypeOf<BufferedInputStream>();
static Logger* logger = Logger::getLogger(BufferedInputStream::TYPE, ERROR);

#define DEFAULT_BUFFER_SIZE 8192

BufferedInputStream::BufferedInputStream(InputStream* in) 
    :FilterInputStream(in), count(0), pos(0), markpos(-1), marklimit(0) {
    byte* buf = new byte[DEFAULT_BUFFER_SIZE];
    this->buf = Array<byte>(buf, DEFAULT_BUFFER_SIZE);
}

BufferedInputStream::BufferedInputStream(InputStream* in, int size) 
    :FilterInputStream(in), count(0), pos(0), markpos(-1), marklimit(0)  {
    byte* buf = new byte[size];
    this->buf = Array<byte>(buf, size);
}

BufferedInputStream::~BufferedInputStream() {
    this->buf.release();
}

InputStream* BufferedInputStream::getInIfOpen() const throw(IOException*) {
    InputStream* input = this->in;

    if (input == null) {
        throw new IOException("Stream closed");
    }

    return input;
}

Array<byte> BufferedInputStream::getBufIfOpen() const throw(IOException*) {
    Array<byte> buffer = this->buf;

    if (buffer.size() == 0) {
        throw new IOException("Stream closed");
    }

    return buffer;
}

void BufferedInputStream::fill() throw(IOException*) {
    Array<byte> buffer = getBufIfOpen();

    if (markpos < 0) {
        pos = 0;        /* no mark: throw away the buffer */
    } else if (pos >= buffer.length()) {  /* no room left in buffer */
        if (markpos > 0) {  /* can throw away early part of the buffer */
            int sz = pos - markpos;
            System::arraycopy(buffer, markpos, buffer, 0, sz);
            pos = sz;
            markpos = 0;
        } else if (buffer.length() >= marklimit) {
            markpos = -1;   /* buffer got too big, invalidate mark */
            pos = 0;    /* drop buffer contents */
        } else {        /* grow buffer */
            int nsz = pos * 2;

            if (nsz > marklimit) {
                nsz = marklimit;
            }

            byte* nbuf = new byte[nsz];
            System::arraycopy(buffer.raw(), 0, nbuf, 0, pos);
            buffer = Array<byte>(nbuf, nsz);
        }
    }

    count = pos;
    int n = getInIfOpen()->read(const_cast<byte*>(buffer.raw()), buffer.size(), pos, buffer.length() - pos);

    if (n > 0) {
        count = n + pos;
    }
}

wlong_u BufferedInputStream::skip(wlong_u n) throw(IOException*) {
    getBufIfOpen(); // Check for closed stream

    if (n <= 0) {
        return 0;
    }
    
    long avail = count - pos;
     
    if (avail <= 0) {
        // If no mark position set then don't keep in buffer
        if (markpos <0) 
            return getInIfOpen()->skip(n);
        
        // Fill in buffer to save bytes for reset
        fill();
        avail = count - pos;
        if (avail <= 0)
            return 0;
    }
    
    long skipped = (avail < n) ? avail : n;
    pos += skipped;
    return skipped;
}

int BufferedInputStream::read1(Array<byte> b, int off, int len) throw(IOException*) {
    int avail = count - pos;

    if (avail <= 0) {
        /* If the requested length is at least as large as the buffer, and
           if there is no mark/reset activity, do not bother to copy the
           bytes into the local buffer.  In this way buffered streams will
           cascade harmlessly. */
        if (len >= getBufIfOpen().length() && markpos < 0) {
            return getInIfOpen()->read(const_cast<byte*>(b.raw()), b.size(), off, len);
        }

        fill();
        avail = count - pos;
        if (avail <= 0) return -1;
    }

    int cnt = (avail < len) ? avail : len;
    System::arraycopy(getBufIfOpen(), pos, b, off, cnt);
    pos += cnt;
    return cnt;
}

int BufferedInputStream::read(byte* b, int num, int off, int len) throw(IOException*) {
    getBufIfOpen(); // Check for closed stream

    if ((off | len | (off + len) | (num - (off + len))) < 0) {
        throw new IndexOutOfBoundsException();
    } else if (len == 0) {
        return 0;
    }

    int n = 0;
    Array<byte> bb(b, num);

    for (;;) {
        int nread = read1(bb, off + n, len - n);
        if (nread <= 0) 
            return (n == 0) ? nread : n;

        n += nread;
        if (n >= len)
            return n;

        // if not closed but no bytes available, return
        InputStream* input = this->in;
        if (input != null && input->available() <= 0)
            return n;
    }
}

void BufferedInputStream::close() throw(IOException*) {
    byte* buffer;

    while ((buffer = const_cast<byte*>(buf.raw())) != null) {
        InputStream* input = in;
        in = null;

        if (input != null)
            input->close();

        return;
        // Else retry in case a new buf was CASed in fill()
    }
}

void BufferedInputStream::mark(int readlimit) {
    marklimit = readlimit;
    markpos = pos;
}

void BufferedInputStream::reset() throw(IOException*) {
    getBufIfOpen(); // Cause exception if closed

    if (markpos < 0)
        throw new IOException("Resetting to invalid mark");

    pos = markpos;
}

bool BufferedInputStream::markSupported() {
    return true;
}

int BufferedInputStream::available() const {
    return getInIfOpen()->available() + (count - pos);
}