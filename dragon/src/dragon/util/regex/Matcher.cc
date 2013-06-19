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

#include <dragon/util/regex/Matcher.h>
#include <dragon/lang/Arrays.h>

Import dragon::lang;
Import dragon::util::regex;

#define OVECCOUNT 30    /* should be a multiple of 3 */

Matcher::Matcher(Pattern* parent, String* text) {
    this->parentPattern = parent;
    this->text = new String(text);

    this->groups = NULL;
    this->groupSize = 0;

    this->first = -1;
    this->last = 0;
}

Matcher::~Matcher() {
    SafeDelete(this->text);
    this->reset();
}

void Matcher::reset() {
    if (this->groups != NULL) {
        delete[] this->groups;
        this->groups = NULL;
    }
    
    this->groupSize = 0;
}


dg_boolean Matcher::matches() {
    return this->find(0);
}

dg_boolean Matcher::find() {
    dg_int nextSearchIndex = this->last;
    if (nextSearchIndex == this->first) {
        nextSearchIndex++;
    }

    dg_boolean result = this->find(nextSearchIndex);
    if (result) {
        this->first = this->start();
        this->last = this->end();
    } else {
        this->first = -1;
        this->last = 0;
    }

    return result;
}

dg_boolean Matcher::find(dg_int start) {
    const dg_char* subject = this->text->toChars();
    dg_int subject_length = this->text->length();
 
    int count = OVECCOUNT;

    int* ovector = NULL;
    int rc = 0;

    this->reset();
    
    if (start < 0 || start >= subject_length) {
        return dg_false;
    }

    while(rc == 0) {
      if (ovector != NULL) {
          delete[] ovector;
          count*=2;
      }

      ovector = new int[count];

      rc = pcre32_exec(
        this->parentPattern->re,  /* the compiled pattern */
        NULL,                     /* no extra data - we didn't study the pattern */
        subject,                  /* the subject string */
        subject_length,           /* the length of the subject */
        start,                    /* start at offset 0 in the subject */
        0,                        /* default options */
        ovector,                  /* output vector for substring information */
        count);                   /* number of elements in the output vector */
    }

    SafeDeleteArray(subject);

    if (rc > 0) {
        this->groups = ovector;
        this->groupSize = rc;

        return dg_true;
    }

    return dg_false;
}


dg_int Matcher::start(dg_int group) {
    if (group < 0 || group >= this->groupSize) {
        return 0;
    }

    return this->groups[group * 2];
}

dg_int Matcher::end(dg_int group){
    if (group < 0 || group >= this->groupSize) {
        return 0;
    }

    return this->groups[group * 2 + 1];
}

String* Matcher::group(dg_int group) {
    if (group < 0 || group >= this->groupSize) {
        return null;
    }

    dg_int startIndex = this->start(group);
    dg_int endIndex = this->end(group);
    return this->text->substring(startIndex, endIndex);
}


dg_int Matcher::groupCount() {
    return this->groupSize;
}

dg_int Matcher::start(){
    return this->start(0);
}

dg_int Matcher::end() {
    return this->end(0);
}

String* Matcher::group(){
    return this->group(0);
}
