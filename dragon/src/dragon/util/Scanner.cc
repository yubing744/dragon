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

#include <dragon/lang/Integer.h>
#include <dragon/lang/Float.h>
#include <dragon/lang/Double.h>
#include <dragon/lang/StringBuffer.h>

#include <dragon/util/Scanner.h>
#include <dragon/util/logging/Logger.h>

#include <dragon/io/FileInputStream.h>
#include <dragon/io/InputStreamReader.h>

#include <dragon/util/regex/Matcher.h>
#include <dragon/util/regex/Pattern.h>

Import dragon::io;
Import dragon::lang;
Import dragon::util;
Import dragon::util::logging;
Import dragon::util::regex;

const Type* Scanner::TYPE = TypeOf<Scanner>();
static Logger* logger = Logger::getLogger(Scanner::TYPE, ERROR);

Scanner::Scanner(Reader* reader) 
    :token(null) {
    SafeRetain(reader);
    this->reader = reader;

    this->delimiter = Pattern::compile("\\s");
}

Scanner::Scanner(File* file) 
    :token(null){
    FileInputStream* fis = new FileInputStream(file);
    InputStreamReader* reader = new InputStreamReader(fis, "UTF-8");

    SafeRetain(reader);
    this->reader = reader;

    SafeRelease(reader);
    SafeRelease(fis);

    this->delimiter = Pattern::compile("\\s");
}

Scanner::Scanner(File* file, const String& charsetName) 
    :token(null) {
    FileInputStream* fis = new FileInputStream(file);
    InputStreamReader* reader = new InputStreamReader(fis, charsetName);

    SafeRetain(reader);
    this->reader = reader;

    SafeRelease(reader);
    SafeRelease(fis); 

    this->delimiter = Pattern::compile("\\s"); 
}

Scanner::~Scanner() {
    SafeRelease(this->reader);
    SafeRelease(this->token);
    SafeRelease(this->delimiter);
}

void Scanner::readToken() {
    if (this->token==null) {
        StringBuffer* sb = new StringBuffer();

        wchar_u ch;
        int read = this->reader->read(&ch, 1);

        while(read > -1) {
            sb->append(ch);

            String* tmp = sb->toString();

            Matcher* m = this->delimiter->matcher(tmp);

            if (m->find()) {
                this->token = tmp->substring(0, m->start());
                SafeRelease(m);
                SafeRelease(tmp);
                break;
            } else if (ch == '\n') {
                this->token = tmp;
                SafeRelease(m);
                break;
            }

            SafeRelease(m);
            SafeRelease(tmp);

            read = this->reader->read(&ch, 1);
        }

        SafeRelease(sb);
    }
}

bool Scanner::hasNext() {
    this->readToken();
    return this->token!=null;
}

String* Scanner::next() {
    this->readToken();

    String* token = this->token;

    if (token != null) {
        this->token = null;
        return token;
    }

    return null;
}

bool Scanner::hasNextInt() {
    this->readToken();

    if (this->token != null) {
        try {
            Integer* val = Integer::parseInt(this->token);
            SafeRelease(val);
            return true;
        } catch(NumberFormatException* e) {
            SafeRelease(e);
            return false;
        }
    }

    return false;
}

int Scanner::nextInt() {
    this->readToken();

    if (this->token != null) {
        Integer* val = Integer::parseInt(this->token);
        int ret = val->intValue();
        SafeRelease(val);
        
        SafeRelease(this->token);
        return ret;
    }

    return 0;
}   

bool Scanner::hasNextFloat() {
    this->readToken();

    if (this->token != null) {
        try {
            Float* val = Float::parseFloat(this->token);
            SafeRelease(val);
            return true;
        } catch(NumberFormatException* e) {
            SafeRelease(e);
            return false;
        }
    }

    return false;
}

float Scanner::nextFloat() {
    this->readToken();

    if (this->token != null) {
        Float* val = Float::parseFloat(this->token);
        float ret = val->floatValue();
        SafeRelease(val);
        
        SafeRelease(this->token);
        return ret;
    }

    return 0.0f;
}

bool Scanner::hasNextDouble() {
    this->readToken();

    if (this->token != null) {
        try {
            Double* val = Double::parseDouble(this->token);
            SafeRelease(val);
            return true;
        } catch(NumberFormatException* e) {
            SafeRelease(e);
            return false;
        }
    }

    return false;
}

double Scanner::nextDouble() {
    this->readToken();

    if (this->token != null) {
        Double* val = Double::parseDouble(this->token);
        double ret = val->doubleValue();
        SafeRelease(val);
        
        SafeRelease(this->token);
        return ret;
    }

    return 0.0;
}

bool Scanner::hasNextChar() {
    this->readToken();

    if (this->token != null && this->token->length() == 1) {
        return true;
    }

    return false;
}

wchar_u Scanner::nextChar() {
    this->readToken();

    if (this->token != null && this->token->length() == 1) {
        wchar_u ret = this->token->charAt(0);
        SafeRelease(this->token);
        return ret;
    }

    return ' ';
}

void Scanner::skip(const String& pattern) {
    Pattern* p = Pattern::compile("\\s");
    this->skip(p);
    SafeRelease(p);
}

void Scanner::skip(Pattern* pattern) {
    if (this->token==null) {
        StringBuffer* sb = new StringBuffer();

        wchar_u ch;
        int read = this->reader->read(&ch, 1);

        while(read > -1) {
            sb->append(ch);

            String* tmp = sb->toString();

            Matcher* m = pattern->matcher(tmp);

            if (m->find()) {
                SafeRelease(m);
                SafeRelease(tmp);
                break;
            } else if (ch == '\n') {
                SafeRelease(m);
                break;
            }

            SafeRelease(m);
            SafeRelease(tmp);

            read = this->reader->read(&ch, 1);
        }

        SafeRelease(sb);
    }
}