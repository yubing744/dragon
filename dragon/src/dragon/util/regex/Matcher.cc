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

Matcher::Matcher(Pattern* parent, const String* text) {
    this->parentPattern = parent;
    this->text = new String(text);

    this->groups = NULL;
    this->groupSize = 0;

    this->first = -1;
    this->last = 0;

    this->lastAppendPosition = 0;
}

Matcher::Matcher(Pattern* parent, const CharSequence* text) {
    this->parentPattern = parent;
    this->text = text->toString();

    this->groups = NULL;
    this->groupSize = 0;

    this->first = -1;
    this->last = 0;

    this->lastAppendPosition = 0;
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
    
    this->first = -1;
    this->last = 0;
    this->groupSize = 0;
    this->lastAppendPosition = 0;
}


bool Matcher::matches() {
    return this->find(0);
}

bool Matcher::find() {
    int nextSearchIndex = last;
    if (nextSearchIndex == first)
        nextSearchIndex++;

    // If next search starts before region, start it at region
    //if (nextSearchIndex < from)
    //    nextSearchIndex = from;

    // If next search starts beyond region then it fails
    //if (nextSearchIndex > to) {
    //    SafeDeleteArray(this->groups);
    //    return false;
    //}

    return this->search(nextSearchIndex);
}

bool Matcher::find(int start) {
    //int limit = getTextLength();
    //if ((start < 0) || (start > limit))
    //    throw new IndexOutOfBoundsException("Illegal start index");

    this->reset();
    return this->search(start);
}

bool Matcher::search(int from) {
    int subject_length = this->text->length();
 
    int count = OVECCOUNT;

    int* ovector = NULL;
    int rc = 0;
    
    if (from < 0 || from >= subject_length) {
        return dg_false;
    }

    const wchar_u* subject = this->text->toString()->toChars();

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
        from,                     /* start at offset 0 in the subject */
        0,                        /* default options */
        ovector,                  /* output vector for substring information */
        count);                   /* number of elements in the output vector */
    }

    if (rc > 0) {
        SafeDeleteArray(this->groups);
        this->groups = ovector;
        this->groupSize = rc;

        this->first = this->start();
        this->last = this->end();

        return true;
    }

    return false;
}


int Matcher::start(int group) {
    if (group < 0 || group >= this->groupSize) {
        return 0;
    }

    return this->groups[group * 2];
}

int Matcher::end(int group){
    if (group < 0 || group >= this->groupSize) {
        return 0;
    }

    return this->groups[group * 2 + 1];
}

String* Matcher::group(int group) {
    if (group < 0 || group >= this->groupSize) {
        return null;
    }

    int startIndex = this->start(group);
    int endIndex = this->end(group);

    return this->text->toString()->substring(startIndex, endIndex);
}


int Matcher::groupCount() {
    return this->groupSize;
}

int Matcher::start(){
    return this->start(0);
}

int Matcher::end() {
    return this->end(0);
}

String* Matcher::group(){
    return this->group(0);
}

Matcher* Matcher::appendReplacement(StringBuffer* sb, String* replacement) {
    // If no match, return error
    //if (first < 0)
    //    throw new IllegalStateException("No match available");

    // Process substitution string to replace group references with groups
    int cursor = 0;
    String* s = replacement;
    StringBuffer* result = new StringBuffer();

    while (cursor < replacement->length()) {
        dg_char nextChar = replacement->charAt(cursor);
        if (nextChar == '\\') {
            cursor++;
            nextChar = replacement->charAt(cursor);
            result->append(nextChar);
            cursor++;
        } else if (nextChar == '$') {
            // Skip past $
            cursor++;

            // The first number is always a group
            int refNum = (int)replacement->charAt(cursor) - '0';
            //if ((refNum < 0)||(refNum > 9))
            //    throw new IllegalArgumentException(
            //        "Illegal group reference");
            cursor++;

            // Capture the largest legal group string
            bool done = dg_false;
            while (!done) {
                if (cursor >= replacement->length()) {
                    break;
                }
                int nextDigit = replacement->charAt(cursor) - '0';
                if ((nextDigit < 0)||(nextDigit > 9)) { // not a number
                    break;
                }
                int newRefNum = (refNum * 10) + nextDigit;
                if (groupCount() < newRefNum) {
                    done = dg_true;
                } else {
                    refNum = newRefNum;
                    cursor++;
                }
            }

            // Append group
            if (group(refNum) != null)
                result->append(group(refNum));
        } else {
            result->append(nextChar);
            cursor++;
        }
    }

    // Append the intervening text
    CharSequence* head = getSubSequence(lastAppendPosition, first);
    sb->append(head);
    SafeDelete(head);

    // Append the match substitution
    String* mid = result->toString();
    sb->append(mid);
    SafeDelete(mid);

    SafeDelete(result);

    lastAppendPosition = last;
    return this;
}

StringBuffer* Matcher::appendTail(StringBuffer* sb) {
    CharSequence* seq = getSubSequence(lastAppendPosition, getTextLength());
    sb->append(seq);
    SafeDelete(seq);

    return sb;
}


String* Matcher::replaceAll(String* replacement) {
    reset();

    bool result = find();

    if (result) {
        String* ret = null;

        StringBuffer* sb = new StringBuffer();

        do {
            appendReplacement(sb, replacement);
            result = find();
        } while (result);

        appendTail(sb);

        ret = sb->toString();
        SafeDelete(sb);

        return ret;
    } else {
        return text->toString();
    }
}

int Matcher::getTextLength() {
    return text->length();
}

CharSequence* Matcher::getSubSequence(int beginIndex, int endIndex) {
    return text->subSequence(beginIndex, endIndex);
}

wchar_u Matcher::charAt(int i) {
    return text->charAt(i);
}