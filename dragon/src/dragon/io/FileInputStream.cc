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

//include <dragon/io/native/${platform}/FileInputStream.cc>

#include <stdio.h>
#include <dragon/io/FileInputStream.h>

Import dragon::io;

FileInputStream::FileInputStream(const String& name) throw(FileNotFoundException*)
    :markpos(-1), marklimit(0) {
    this->file = new File(name);
    this->nativeFileHandle = NULL;

    this->open();
}

FileInputStream::FileInputStream(File* file) throw(FileNotFoundException*)
    :markpos(-1), marklimit(0) {
    this->file = new File(file);
    this->nativeFileHandle = NULL;

    this->open();
}

FileInputStream::~FileInputStream() {
    SafeDelete(this->file);

    this->close();
}