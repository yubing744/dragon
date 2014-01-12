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

#include <unistd.h>
#include <stdio.h>

#include <dragon/io/FileOutputStream.h>
#include <dragon/lang/NullPointerException.h>
#include <dragon/lang/IndexOutOfBoundsException.h>

Import dragon::io;
Import dragon::lang;

void FileOutputStream::open(bool append) throw(IOException*) {
    String* path = this->file->getCanonicalPath();
    const Array<char> utf8Name = path->getBytes("UTF-8");

    FILE* f = NULL;

    if (append) {
        f = fopen(utf8Name, "ab+");
    } else {
        f = fopen(utf8Name, "wb");
    }

    if(f != NULL) {
        SafeDelete(path);
        this->nativeFileHandle = (void*)f;
    } else {
        String* msg = String::format("the file not found, path: %s!", utf8Name.raw());
        FileNotFoundException* e = new FileNotFoundException(msg);
        SafeDelete(msg);
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

    FILE* f = (FILE*)this->nativeFileHandle;

    if (f != NULL) {
        fwrite(b + off, 1, len, f);
    }
}

void FileOutputStream::flush() throw(IOException*) {
    FILE* f = (FILE*)this->nativeFileHandle;

    if (f != 0) {
        //if (fsync(f) == -1)
        //    throw new IOException("error in flush!");

        #if JUCE_ANDROID
            // This stuff tells the OS to asynchronously update the metadata
            // that the OS has cached aboud the file - this metadata is used
            // when the device is acting as a USB drive, and unless it's explicitly
            // refreshed, it'll get out of step with the real file.
            const LocalRef<jstring> t (javaString (file.getFullPathName()));
            android.activity.callVoidMethod (JuceAppActivity.scanFile, t.get());
        #endif
    }
}

void FileOutputStream::close() throw(IOException*) {
    FILE* f = (FILE*)this->nativeFileHandle;

    if (f != NULL) {
        fclose(f);
    }
}

