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

#ifndef Writer_IO_Dragon_H 
#define Writer_IO_Dragon_H

#include <dragon/io/Appendable.h>
#include <dragon/io/Closeable.h>
#include <dragon/io/Flushable.h>

#include <dragon/lang/IndexOutOfBoundsException.h>

BeginPackage2(dragon, io)

Import dragon::lang;

class _DragonExport Writer extends(Object)
	implements3(Appendable, Closeable, Flushable)
{
public:
	Writer(){};
	virtual ~Writer(){};

public:
	virtual void flush() throw(IOException*) = 0;
	virtual void write(const wchar_u* cbuf, int off, int len) throw(IOException*, IndexOutOfBoundsException*) = 0;
	virtual void close() throw(IOException*) = 0;

public:
	virtual Writer* append(wchar_u c) throw(IOException*);

	virtual Writer* append(CharSequence* csq) throw(IOException*);
	virtual Writer* append(CharSequence* csq, int start, int end) throw(IOException*);

	virtual Writer* append(const String& str) throw(IOException*);
	virtual Writer* append(const String& str, int off, int len) throw(IOException*, IndexOutOfBoundsException*);
	
	virtual void write(int c) throw(IOException*);
	virtual void write(const wchar_u* cbuf) throw(IOException*);
	virtual void write(const String& str) throw(IOException*);
	virtual void write(const String& str, int off, int len) throw(IOException*, IndexOutOfBoundsException*);
};

EndPackage2//(dragon, io)

#endif//Writer_IO_Dragon_H
