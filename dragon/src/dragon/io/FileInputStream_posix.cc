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

#include <stdio.h>
#include <dragon/io/FileInputStream.h>
#include <dragon/io/FileNotFoundException.h>

Import dragon::io;

void FileInputStream::open() throw(IOException*) {
    String* path = this->file->getCanonicalPath();
    const Array<char> utf8Name = path->getBytes("UTF-8");

    FILE* f = fopen(utf8Name, "r");

    if (f != NULL) {
        this->nativeFileHandle = (void*)f;
        SafeDelete(path);
    } else {
        String* msg = String::format("the file not found, path: %s!", utf8Name.raw());
        FileNotFoundException* e = new FileNotFoundException(msg);
        SafeDelete(msg);
        SafeDelete(path);

        throw e;
    }
}

wlong_u FileInputStream::skip(wlong_u n) throw(IOException*) {
    FILE* f = (FILE*)this->nativeFileHandle;

    if (f != NULL && fseek(f, n, SEEK_SET) == n) {
        return n;
    }

    return -1;
}

int FileInputStream::read(byte* b, int num, int off, int len) throw(IOException*) {
    int result = 0;

    FILE* f = (FILE*)this->nativeFileHandle;

    if (f != NULL) {
        result = fread(b + off, 1, len, f);

        if (result < 0) {
            result = 0;
        }
    }

    return (int) result;
}

void FileInputStream::close() throw(IOException*) {
    FILE* f = (FILE*)this->nativeFileHandle;

    if (f != NULL) {
        fclose(f);
        this->nativeFileHandle = NULL;
    }
}

int FileInputStream::available() throw(IOException*) {
    FILE* f = (FILE*)this->nativeFileHandle;

    if (f != NULL) {
        long old = ftell(f);

        fseek(f, 0L, SEEK_END); 
        long flen = ftell(f); 

        fseek(f, old, SEEK_SET);

        return flen - old;
    }   

    return 0;
}
