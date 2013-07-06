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
 * Created:     2013/03/31
 **********************************************************************/

#include <dragon/util/regex/Pattern.h>
#include <dragon/util/regex/Matcher.h>

Import dragon::lang;
Import dragon::util::regex;

// static methods
Pattern* Pattern::compile(String* regex) {
    return new Pattern(regex, 0);
}

Pattern* Pattern::compile(String* regex, dg_int flags) {
    return new Pattern(regex, flags);
}

void Pattern::release(Pattern* p) {
    SafeDelete(p);
}

dg_boolean Pattern::matches(String* regex, String* input) {
    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(input);
    dg_boolean result = m->matches();
    SafeDelete(m);
    Pattern::release(p);

    return result;
}

// member methods
Pattern::Pattern(String* regex, dg_int flags) {
    this->pattern = new String(regex);
    this->flags = flags;
    this->compiled = dg_false;
}

Pattern::~Pattern() {
    SafeDelete(this->pattern);

    if (this->re != NULL) {
        pcre32_free(this->re);
        this->re = NULL;
    }
}


void Pattern::compile() {
    const char *error;
    int erroffset;

    dg_char* pattern = (dg_char*)this->pattern->toChars();

    pcre32* re = pcre32_compile(
        pattern,              /* the pattern */
        0,                    /* default options */
        &error,               /* for error message */
        &erroffset,           /* for error offset */
        NULL);                /* use default character tables */

    if (re != NULL) {
        this->re = re;
        this->compiled = dg_true;
    } 
}


Matcher* Pattern::matcher(String* input) {
    if (!this->compiled) {
        this->compile();
    }

    Matcher* m = new Matcher(this, input);
    return m;
}
