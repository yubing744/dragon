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

#ifndef FileInputStream_IO_Lang_H 
#define FileInputStream_IO_Lang_H

#include <dragon/lang/String.h>

#include <dragon/io/File.h>
#include <dragon/io/InputStream.h>
#include <dragon/io/IOException.h>
#include <dragon/io/FileNotFoundException.h>

BeginPackage2(dragon, io)

Import dragon::lang;

class _DragonExport FileInputStream extends(InputStream)
{
public:
	FileInputStream(const String& name) throw(FileNotFoundException*);
	FileInputStream(File* file) throw(FileNotFoundException*);
	virtual ~FileInputStream();

protected:
	virtual void open() throw(IOException*);

public:
	virtual wlong_u skip(wlong_u n) throw(IOException*);
    virtual int read(byte* b, int num, int off, int len) throw(IOException*);
    virtual void close() throw(IOException*);

public:
    virtual bool markSupported() const;
    virtual void mark(int readlimit);
    virtual void reset() throw(IOException*);
    virtual int available() const;

protected:
	File* file;
	void* nativeFileHandle;

    int markpos;
    int marklimit;
};

EndPackage2//(dragon, io)

#endif//FileInputStream_IO_Lang_H