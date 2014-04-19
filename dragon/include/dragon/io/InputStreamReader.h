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


#ifndef InputStreamReader_IO_Dragon_H 
#define InputStreamReader_IO_Dragon_H

#include <dragon/io/Reader.h>
#include <dragon/io/InputStream.h>
#include <dragon/lang/StringBuffer.h>
#include <dragon/io/UnsupportedEncodingException.h>

BeginPackage2(dragon, io)

Import dragon::lang;

class _DragonExport InputStreamReader 
	extends(Reader)
{
public:
	InputStreamReader(){};
	InputStreamReader(const InputStream* in);
	InputStreamReader(const InputStream* in, const String& charset) 
        throw(UnsupportedEncodingException*);

    virtual ~InputStreamReader();
    
public: // extends from Reader
	virtual int read(wchar_u* cbuf, int num, int off, int len) const 
        throw(IOException*, IndexOutOfBoundsException*);
	virtual void close() throw(IOException*);

public:
	virtual const String* getEncoding() const;

protected:
    virtual void readLine();
    virtual void checkCharset(char* buf, size_t n);
    
protected:
	InputStream* innerStream;
	String* charsetName;

    String* line;
    int current;
    bool firstLine;
};

EndPackage2//(dragon, io)

#endif//InputStreamReader_IO_Dragon_H
