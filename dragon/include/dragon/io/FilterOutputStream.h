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
 * Created:     2014/01/12
 **********************************************************************/


#ifndef FilterOutputStream_Io_Dragon_H
#define FilterOutputStream_Io_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/OutputStream.h>

BeginPackage2(dragon, io)

Import dragon::io;
Import dragon::lang;

class_ FilterOutputStream extends(OutputStream) {
public:
    static const Type* TYPE;
    
public:
    FilterOutputStream(OutputStream* out);
    virtual ~FilterOutputStream();

public:
    virtual void write(const byte* b, int num, int off, int len) throw(IOException*);
    virtual void flush() throw(IOException*);
    virtual void close() throw(IOException*);

protected:
    OutputStream* out;

};//FilterOutputStream

EndPackage2 //(dragon, io)

#endif //FilterOutputStream_Io_Dragon_H
