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

//include <dragon/io/native/${platform}/FileOutputStream.cc>

#include <dragon/io/FileOutputStream.h>
#include <stdio.h>

Import dragon::io;

FileOutputStream::FileOutputStream(const wchar_u* name) throw(FileNotFoundException*) {
    this->file = new File(name);
    this->open(false);
}

FileOutputStream::FileOutputStream(const wchar_u* name, bool append) throw(FileNotFoundException*) {
    this->file = new File(name);
    this->open(append);
}

FileOutputStream::FileOutputStream(File* file) throw(FileNotFoundException*) {
    this->file = new File(file);
    this->open(false);
}

FileOutputStream::FileOutputStream(File* file, bool append) throw(FileNotFoundException*) {
    this->file = new File(file);
    this->open(append);
}

FileOutputStream::~FileOutputStream(){
    this->close();
    SafeDelete(this->file);
}