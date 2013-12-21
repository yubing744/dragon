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


#ifndef FileWriter_IO_Dragon_H 
#define FileWriter_IO_Dragon_H

#include <dragon/io/OutputStreamWriter.h>
#include <dragon/io/IOException.h>
#include <dragon/io/File.h>

BeginPackage2(dragon, io)

class _DragonExport FileWriter 
	extends(OutputStreamWriter)
{
public:
	FileWriter(const wchar_u* fileName) throw(IOException*);
	FileWriter(const wchar_u* fileName, bool append) throw(IOException*);
	FileWriter(File* file) throw(IOException*);
	FileWriter(File* file, bool append) throw(IOException*);

	virtual ~FileWriter();
};

EndPackage2//(dragon, io)


#endif//FileWriter_IO_Dragon_H