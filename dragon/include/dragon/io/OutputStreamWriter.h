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

#ifndef OutputStreamWriter_IO_Dragon_H 
#define OutputStreamWriter_IO_Dragon_H

#include <dragon/io/Writer.h>
#include <dragon/io/OutputStream.h>

#include <dragon/io/IOException.h>

BeginPackage2(dragon, io)

class _DragonExport OutputStreamWriter 
	extends(Writer)
{
public:
	OutputStreamWriter(const OutputStream* out);
	OutputStreamWriter(const OutputStream* out, const String& charsetName);
	virtual ~OutputStreamWriter();

public:
	virtual void flush() throw(IOException*);
	virtual void write(const wchar_u* cbuf, int off, int len) 
					throw(IOException*, IndexOutOfBoundsException*);
	virtual void close() throw(IOException*);

public:
	virtual const String* getEncoding() const;

protected:
	OutputStream* innerStream;
	String* charsetName;
};

EndPackage2//(dragon, io)

#endif//OutputStreamWriter_IO_Dragon_H
