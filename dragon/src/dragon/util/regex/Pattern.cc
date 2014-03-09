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
#include <dragon/util/ArrayList.h>


Import dragon::lang;
Import dragon::util;
Import dragon::util::regex;

// static methods
Pattern* Pattern::compile(const String* regex) {
    return new Pattern(regex, 0);
}

Pattern* Pattern::compile(const String* regex, int flags) {
    return new Pattern(regex, flags);
}

void Pattern::release(Pattern* p) {
    SafeDelete(p);
}

bool Pattern::matches(String* regex, String* input) {
    Pattern* p = Pattern::compile(regex);

    Matcher* m = p->matcher(input);
    bool result = m->matches();
    SafeDelete(m);

    Pattern::release(p);

    return result;
}

// member methods
Pattern::Pattern(const String* regex, int flags) {
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


Matcher* Pattern::matcher(const CharSequence* input) {
    if (!this->compiled) {
        this->compile();
    }

    return new Matcher(this, input);
}

Array<String*> Pattern::split(const CharSequence* input) {
    return split(input, 0);
}

Array<String*> Pattern::split(const CharSequence* input, int limit) {
    int index = 0;
    bool matchLimited = limit > 0;
    ArrayList<String>* matchList = new ArrayList<String>();

    Matcher* m = matcher(input);

    // Add segments before each match found
    while(m->find()) {
        if (!matchLimited || matchList->size() < limit - 1) {
            CharSequence* subSeq = input->subSequence(index, m->start());
            String* match = subSeq->toString();
            SafeRelease(subSeq);

            matchList->add(match);
            index = m->end();

            //SafeRelease(match);
        } else if (matchList->size() == limit - 1) { // last one
            CharSequence* subSeq = input->subSequence(index, input->length());
            String* match = subSeq->toString();
            SafeRelease(subSeq);

            matchList->add(match);
            index = m->end();

            //SafeRelease(match);
        }
    }

    SafeDelete(m);

    // If no match was found, return this
    if (index == 0) {
        String** data = new String*[1];
        data[0] = input->toString();
        return Array<String*>(data, 1);
    }

    // Add remaining segment
    if (!matchLimited || matchList->size() < limit) {
        CharSequence* subSeq = input->subSequence(index, input->length());
        matchList->add(subSeq->toString());
        SafeRelease(subSeq);
    }

    // Construct result
    int resultSize = matchList->size();
    if (limit == 0)
        while (resultSize > 0 && matchList->get(resultSize-1)->equals(""))
            resultSize--;

    List<String>* subList = matchList->subList(0, resultSize);
    Array<String*> array = subList->toArray();
    SafeRelease(subList);

    SafeRelease(matchList);
    
    return array;
}