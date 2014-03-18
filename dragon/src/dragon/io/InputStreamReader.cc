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

#include <dragon/lang/Array.h>
#include <dragon/lang/Arrays.h>
#include <dragon/io/InputStreamReader.h>

Import dragon::lang;
Import dragon::io;

InputStreamReader::InputStreamReader(const InputStream* in) 
    :firstLine(true) {
	this->innerStream = const_cast<InputStream*>(in);
    this->innerStream->retain();
    
	this->charsetName = new String(L"UTF-8");
    this->line = null;
}

InputStreamReader::InputStreamReader(const InputStream* in, const String& charset) throw(UnsupportedEncodingException*) 
    :firstLine(true) {
    this->innerStream = const_cast<InputStream*>(in);
    this->innerStream->retain();

    this->charsetName = new String(charset);
    this->line = null;
}

InputStreamReader::~InputStreamReader() {
    this->close();
    SafeDelete(this->charsetName);
    SafeRelease(this->innerStream);
    SafeRelease(this->line);
}

void InputStreamReader::close() throw(IOException*) {
	this->innerStream->close();
}

void InputStreamReader::readLine() {
    int bufSize = 64;
    char* buf = (char*)malloc(bufSize);
    int n = 0;

    int read = 0;
    char ch;
    read = this->innerStream->read(&ch, 1);

    while(read > 0) {
        if (ch=='\r') {
            continue;
        }

        if (n >= bufSize) {
            int tmpSize = bufSize * 2;
            char* tmp = (char*)malloc(tmpSize);

            memcpy(tmp, buf, bufSize);
            bufSize = tmpSize;
            free(buf);

            buf = tmp;
        }

        buf[n++] = ch;

        if (ch=='\n') {
            break;
        }

        read = this->innerStream->read(&ch, 1);
    }


    SafeRelease(this->line);

    if (n > 0) {
        if (this->firstLine) {
            this->checkCharset(buf, n);
        }

        char* utf8Charset = this->charsetName->toUTF8String();
        this->line = new String(Array<byte>(buf, n, false), 0, n, utf8Charset);
        SafeFree(utf8Charset);
    } else {
        this->line = new String();
    }

    this->current = 0;

    SafeFree(buf);
}

void InputStreamReader::checkCharset(char* buf, size_t n) {
    if (this->firstLine) {
        if (n>=3 && buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF) {
            SafeRelease(this->charsetName);
            this->charsetName = new String("UTF-8");
            this->current += 3;
        } else if (n>=2 && buf[0] == 0xFE && buf[1] == 0xFF) {
            SafeRelease(this->charsetName);
            this->charsetName = new String("UCS2-little");
            this->current += 2;
        } else if (n>=2 && buf[0] == 0xFF && buf[1] == 0xFE) {
            if (n>=4 && buf[2] == 0x0 && buf[3] == 0x0) {
                SafeRelease(this->charsetName);
                this->charsetName = new String("UCS4-little");
                this->current += 4;
            } else {
                SafeRelease(this->charsetName);
                this->charsetName = new String("UCS2-big");
                this->current += 2;
            }
        } else if (n>=4 && buf[0] == 0x0 && buf[1] == 0x0
            && buf[2] == 0xFE && buf[3] == 0xFF) {
            SafeRelease(this->charsetName);
            this->charsetName = new String("UCS4-big");
            this->current += 4;
        }

        this->firstLine = false;
    }
}

int InputStreamReader::read(wchar_u* cbuf, int num, int off, int len) const
					throw(IOException*, IndexOutOfBoundsException*) {
    if(off<0 || len<0 || off+len>num) {
        throw new IndexOutOfBoundsException("the write buffer argments");
    }

    InputStreamReader* reader = const_cast<InputStreamReader*>(this);

    if (this->line == null) {
        reader->readLine();
    }

    wchar_u* target = cbuf + off;

    int readCount = 0;
    int size = this->line->length();

    while(this->current < size && readCount < len) {
        int c1 = size - this->current;
        int c2 = len - readCount;
        int count = (c1 > c2) ? c2 : c1;

        this->line->getChars(this->current, this->current + count, target, 0);
        readCount += count;
        reader->current += count;
        target += count;

        if (this->current >= size) {
            reader->readLine();
            size = this->line->length();
        }
    }

    return readCount;
}

const String* InputStreamReader::getEncoding() const {
	return this->charsetName;
}

