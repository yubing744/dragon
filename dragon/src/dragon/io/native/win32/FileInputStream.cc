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

#include <dragon/io/FileInputStream.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

Import dragon::io;

void FileInputStream::open() throw(IOException*) {
    int fh, numread;
    char buffer[40];

    String* path = this->file->getCanonicalPath();
    wchar_t* wcharPath = path->toWCHARString();

    errno_t err = _wsopen_s(&fh, wcharPath, _O_RDONLY, _SH_DENYNO, 
                          _S_IREAD | _S_IWRITE );

    if (err == 0) {
        this->nativeFileHandle = (void*)fh;
        SafeFree(wcharPath);
        SafeDelete(path);
    } else {
        FileNotFoundException* e = new FileNotFoundException("the file not found");
        SafeFree(wcharPath);
        SafeDelete(path);

        throw e;
    }
}

wlong_u FileInputStream::skip(wlong_u n) throw(IOException*) {
    int fh = (int)this->nativeFileHandle;

    if (fh > 0 && _lseek(fh, n, SEEK_SET) == n) {
        return n;
    }

    return -1;
}

int FileInputStream::read(byte* b, int num, int off, int len) throw(IOException*) {
    int result = 0;

    int fh = (int)this->nativeFileHandle;

    if (fh >= 0) {
        result = _read(fh, b + off, len);

        if (result < 0) {
            result = 0;
        }
    }

    return (int) result;
}

void FileInputStream::close() throw(IOException*) {
    int fh = (int)this->nativeFileHandle;

    if (fh != NULL) {
        _close(fh);
        this->nativeFileHandle = NULL;
    }
}

int FileInputStream::available() const throw(IOException*) {
    int fh = (int)this->nativeFileHandle;

    if (fh != NULL) {
        long old = _tell(fh);

        _lseek(fh, 0L, SEEK_END); 
        long flen = _tell(fh); 

        _lseek(fh, old, SEEK_SET);

        return flen - old;
    }   

    return 0;
}
