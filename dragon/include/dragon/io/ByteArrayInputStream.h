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
 * Created:     2014/01/08
 **********************************************************************/


#ifndef ByteArrayInputStream_Io_Dragon_H
#define ByteArrayInputStream_Io_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/InputStream.h>

BeginPackage2(dragon, io)

Import dragon::lang;

class_ ByteArrayInputStream extends(InputStream) {
public:
    static const Type* TYPE;
    
public:
    ByteArrayInputStream(const Array<byte> buf);
    ByteArrayInputStream(const Array<byte> buf, int offset, int length);
    virtual ~ByteArrayInputStream();

public:
    virtual wlong_u skip(wlong_u n) throw(IOException*);
    virtual int read(byte* b, int num, int off, int len) throw(IOException*);
    virtual void close() throw(IOException*);

public:
    virtual void mark(int readlimit);
    virtual void reset() throw(IOException*);
    virtual bool markSupported();
    virtual int available();
    
protected:
    Array<byte> buf;
    int pos;
    int _mark;
    int count;

};//ByteArrayInputStream

EndPackage2 //(dragon, io)

#endif //ByteArrayInputStream_Io_Dragon_H
