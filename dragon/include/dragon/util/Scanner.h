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
 * Created:     2014/03/16
 **********************************************************************/


#ifndef Scanner_Util_Dragon_H
#define Scanner_Util_Dragon_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/lang/StringBuffer.h>

#include <dragon/io/Reader.h>
#include <dragon/io/File.h>
 
#include <dragon/util/regex/Pattern.h>

BeginPackage2(dragon, util)

Import dragon::io;
Import dragon::lang;
Import dragon::util::regex;

class_ Scanner extends(Object) {
public:
    static const Type* TYPE;
    
public:
    Scanner(Reader* reader);
    Scanner(File* file);
    Scanner(File* file, const String& charsetName);

    virtual ~Scanner();

public:
    virtual bool hasNext(Pattern* pattern);
    virtual bool hasNext(const String& pattern);
    virtual bool hasNext();

    virtual String* next(Pattern* pattern);
    virtual String* next(const String& pattern);
    virtual String* next();

    virtual bool hasNextInt();
    virtual int nextInt();

    virtual bool hasNextFloat();
    virtual float nextFloat();

    virtual bool hasNextDouble();
    virtual double nextDouble();

    virtual bool hasNextChar();
    virtual wchar_u nextChar();
   
public:
    virtual void skip(Pattern* pattern);
    virtual void skip(const String& pattern);

    virtual Scanner* useDelimiter(Pattern* pattern);
    virtual Scanner* useDelimiter(const String& pattern);

protected:
    virtual void readToken();

protected:
    Reader* reader;
    Pattern* delimiter;
    String* token;
    wchar_u lastChar;
};//Scanner

EndPackage2 //(dragon, util)

#endif //Scanner_Util_Dragon_H
