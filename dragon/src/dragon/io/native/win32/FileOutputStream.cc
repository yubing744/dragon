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

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

#include <dragon/io/FileOutputStream.h>
#include <dragon/lang/NullPointerException.h>
#include <dragon/lang/IndexOutOfBoundsException.h>

Import dragon::io;
Import dragon::lang;

void FileOutputStream::open(bool append) throw(IOException*) {
    int fh, numread;
    char buffer[40];

    String* path = this->file->getCanonicalPath();
    wchar_t* wcharPath = path->toWCHARString();

    FILE* f = NULL;

    if (append) {
        errno_t err = _wsopen_s(&fh, wcharPath, _O_BINARY | _O_WRONL | _O_APPEND , _SH_DENYNO, 
                          _S_IWRITE );
    } else {
        errno_t err = _wsopen_s(&fh, wcharPath, _O_BINARY | _O_WRONL, _SH_DENYNO, 
                          _S_IWRITE );
    }

    if(err == 0) {
        SafeFree(wcharPath);
        SafeDelete(path);
        this->nativeFileHandle = (void*)fh;
    } else {
        FileNotFoundException* e = new FileNotFoundException("the file not found");
        SafeFree(wcharPath);
        SafeDelete(path);

        throw e;
    }
}

void FileOutputStream::write(const byte* b, int num, int off, int len) throw(IOException*) {
    if(b == null) {
        throw new NullPointerException("the input buffer is null!");
    }

    if(off<0 || len<0 || off+len>num) {
        throw new IndexOutOfBoundsException("the write buffer argments");
    }

    int fh = (int)this->nativeFileHandle;

    if (f != NULL) {
        _write(fh, b + off, len);
    }
}

void FileOutputStream::flush() throw(IOException*) {
     
}

void FileOutputStream::close() throw(IOException*) {
    int fh = (int)this->nativeFileHandle;

    if (fh != NULL) {
        _close(fh);
    }
}