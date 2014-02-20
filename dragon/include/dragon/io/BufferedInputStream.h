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


#ifndef BufferedInputStream_Io_Dragon_H
#define BufferedInputStream_Io_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/FilterInputStream.h>

BeginPackage2(dragon, io)

Import dragon::lang;

class_ BufferedInputStream extends(FilterInputStream) {
public:
    static const Type* TYPE;
    
public:
    BufferedInputStream(InputStream* in);
    BufferedInputStream(InputStream* in, int size);
    virtual ~BufferedInputStream();

public:
    virtual wlong_u skip(wlong_u n) throw(IOException*);
    virtual int read(byte* b, int num, int off, int len) throw(IOException*);
    virtual void close() throw(IOException*);

public:
    virtual bool markSupported() const;
    virtual void mark(int readlimit);
    virtual void reset() throw(IOException*);
    virtual int available() const;

private:
    virtual InputStream* getInIfOpen() const throw(IOException*);
    virtual Array<byte> getBufIfOpen() const throw(IOException*);
    virtual void fill() throw(IOException*);
    virtual int read1(Array<byte> b, int off, int len) throw(IOException*);

protected:
    Array<byte> buf;
    int count;
    int pos;
    int markpos;
    int marklimit;
};//BufferedInputStream

EndPackage2 //(dragon, io)

#endif //BufferedInputStream_Io_Dragon_H
