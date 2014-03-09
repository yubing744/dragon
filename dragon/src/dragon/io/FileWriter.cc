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

#include <dragon/io/FileWriter.h>
#include <dragon/io/FileOutputStream.h>

Import dragon::io;

FileWriter::FileWriter(const wchar_u* fileName) throw(IOException*) 
    :OutputStreamWriter(new FileOutputStream(fileName), "UTF-8") {
}

FileWriter::FileWriter(const wchar_u* fileName, bool append) throw(IOException*) 
    :OutputStreamWriter(new FileOutputStream(fileName, append), "UTF-8") {
}

FileWriter::FileWriter(File* file) throw(IOException*) 
    :OutputStreamWriter(new FileOutputStream(file, true), "UTF-8") {
}

FileWriter::FileWriter(File* file, bool append) throw(IOException*) 
    :OutputStreamWriter(new FileOutputStream(file, append), "UTF-8") {
}

FileWriter::~FileWriter(){
	SafeRelease(this->innerStream);
}