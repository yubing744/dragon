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


#ifndef Reader_IO_DRAGON_H 
#define Reader_IO_DRAGON_H

#include <dragon/lang/Object.h>
#include <dragon/io/Closeable.h>

#include <dragon/io/IOException.h>
#include <dragon/lang/IndexOutOfBoundsException.h>

BeginPackage2(dragon, io)

Import dragon::lang;

class _DragonExport Reader extends(Object) 
	implements1(Closeable)
{
public:
	Reader(){};
	virtual ~Reader(){};

public:
	virtual int read(wchar_u* cbuf, int num, int off, int len) const
					throw(IOException*, IndexOutOfBoundsException*) = 0;
	virtual void close() throw(IOException*) = 0;
	
public:
	virtual int read() const 
		throw(IOException*);
		
	virtual int read(wchar_u* cbuf, int num) const 
		throw(IOException*);

	virtual wlong_u skip(wlong_u n) 
		throw(IOException*);
};

EndPackage2//(dragon, io)

#endif//Reader_IO_DRAGON_H
