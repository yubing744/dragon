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
 * Created:     2013/06/26
 **********************************************************************/

#ifndef FileOutputStream_IO_Lang_H 
#define FileOutputStream_IO_Lang_H

#include <dragon/lang/String.h>

#include <dragon/io/File.h>
#include <dragon/io/OutputStream.h>
#include <dragon/io/IOException.h>
#include <dragon/io/FileNotFoundException.h>

BeginPackage2(dragon, io)

Import dragon::lang;

class _DragonExport FileOutputStream extends(OutputStream)
{
public:
	FileOutputStream(const wchar_u* name) throw(FileNotFoundException*);
	FileOutputStream(const wchar_u* name, bool append)  throw(FileNotFoundException*);
	FileOutputStream(File* file) throw(FileNotFoundException*);
	FileOutputStream(File* file, bool append) throw(FileNotFoundException*);

	virtual ~FileOutputStream(){this->close();};

public:
	virtual void open(bool append) throw(IOException*);
	
public:
	virtual void write(const byte* b, int num, int off, int len) throw(IOException*);
	virtual void flush() throw(IOException*);
	virtual void close() throw(IOException*);

protected:
	File* file;
	void* nativeFileHandle;
};

EndPackage2//(dragon, io)

#endif//FileOutputStream_IO_Lang_H