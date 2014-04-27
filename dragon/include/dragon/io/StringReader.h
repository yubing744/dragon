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
 * Created:     2014/04/27
 **********************************************************************/


#ifndef StringReader_Io_Dragon_H
#define StringReader_Io_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/Reader.h>

BeginPackage2(dragon, io)

Import dragon::lang;

class_ StringReader extends(Reader) {
public:
    static const Type* TYPE;
    
public:
    StringReader(String* source);
    virtual ~StringReader();

public:
    virtual int read(wchar_u* cbuf, int num, int off, int len) const
                    throw(IOException*, IndexOutOfBoundsException*);
    virtual void close() throw(IOException*);
   
protected:
    String* source;
    size_t cursor;
};//StringReader

EndPackage2 //(dragon, io)

#endif //StringReader_Io_Dragon_H
