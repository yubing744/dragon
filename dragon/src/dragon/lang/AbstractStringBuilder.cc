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


#include <dragon/lang/AbstractStringBuilder.h>
#include <dragon/lang/Arrays.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/Long.h>

Import dragon::lang;

AbstractStringBuilder::AbstractStringBuilder() {
	this->value = Array<wchar_u>();
	this->count = 0;
}

AbstractStringBuilder::AbstractStringBuilder(int capcity) {
	this->value = Array<wchar_u>(new wchar_u[capcity], capcity);
	this->count = 0;
}

AbstractStringBuilder::~AbstractStringBuilder() {
	this->value.release();
	this->count = 0;
}

int AbstractStringBuilder::length(){
	return this->count;
}

int AbstractStringBuilder::capcity() {
	return this->value.length();
}


void AbstractStringBuilder::ensureCapacity(int minimumCapacity) {
	if (minimumCapacity > this->value.length()) {
	    this->expandCapacity(minimumCapacity);
	}
}


void AbstractStringBuilder::expandCapacity(int minimumCapacity) {
	int newCapacity = (this->value.length() + 1) * 2;

    if (newCapacity < 0) {
        newCapacity = 0;
    } else if (minimumCapacity > newCapacity) {
    	newCapacity = minimumCapacity;
	}	

	wchar_u* newValue = new wchar_u[newCapacity];
	Arrays<wchar_u>::copyOf(value, 0, newValue, 0, count);
	this->value.release();

	this->value = Array<wchar_u>(newValue, newCapacity);
}


void AbstractStringBuilder::trimToSize() {
    if (this->count < this->value.length()) {
        wchar_u* newValue = new wchar_u[count];
        Arrays<wchar_u>::copyOf(value, 0, newValue, 0, count); 
		this->value = Array<wchar_u>(newValue, count);
    }
}


void AbstractStringBuilder::setLength(int newLength) {
	if (newLength < 0)
    	newLength = 0;

	if (newLength > value.length())
    	expandCapacity(newLength);

	if (count < newLength) {
	    for (; count < newLength; count++)
			this->value[count] = NULL_CHAR;
	} else {
        count = newLength;
    }
}

wchar_u AbstractStringBuilder::charAt(int index) {
	return this->value[index];
}

void AbstractStringBuilder::getChars(int srcBegin, int srcEnd, wchar_u* dst, int dstBegin){
	Arrays<wchar_u>::copyOf(value, srcBegin, dst, dstBegin, srcEnd - srcBegin);
}

void AbstractStringBuilder::setCharAt(int index, wchar_u ch) {
	value[index] = ch;
}

AbstractStringBuilder* AbstractStringBuilder::append(String* str) {
	if (str == null) 
		return append("null");
    
    int len = str->length();

	if (len == 0) 
		return this;

	int newCount = count + len;

	if (newCount > value.length())
	    expandCapacity(newCount);

	wchar_u* dest = const_cast<wchar_u*>(this->value.raw());
	str->getChars(0, len, dest, count);

	count = newCount;
	return this;
}


AbstractStringBuilder* AbstractStringBuilder::append(const String& str) {
    const String* pstr = &str;
    append(const_cast<String*>(pstr));
}


AbstractStringBuilder* AbstractStringBuilder::append(CharSequence* s) {
    if (s == null)
        return append("null");

    return this->append(s, 0, s->length());
}

AbstractStringBuilder* AbstractStringBuilder::append(CharSequence* s, int start, int end) {
    if (s == null)
        return append("null");

    //if ((start < 0) || (end < 0) || (start > end) || (end > s->length()))
    //    throw new IndexOutOfBoundsException(
    //            "start " + start + ", end " + end + ", s.length() " 
    //            + s->length());

    int len = end - start;
    if (len == 0)
        return this;

    int newCount = count + len;
    if (newCount > value.length())
        expandCapacity(newCount);

    for (int i=start; i<end; i++)
        value[count++] = s->charAt(i);

    count = newCount;
    return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(AbstractStringBuilder* sb) {
    if (sb == null)
        return append("null");

    int len = sb->length();
    int newCount = count + len;

    if (newCount > value.length())
        expandCapacity(newCount);

    sb->getChars(0, len, const_cast<wchar_u*>(value.raw()), count);

    count = newCount;
    return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(const char* str, int offset, int length) {
	String* s = new String(str, offset, length);
	this->append(s);
	SafeDelete(s);

	return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(const char* str, int length) {
    return append(str, 0, length);
}

AbstractStringBuilder* AbstractStringBuilder::append(const char* str) {
    return append(str, 0, strlen(str));
}

AbstractStringBuilder* AbstractStringBuilder::append(const wchar_t* str) {
	String* s = new String(str);
	this->append(s);
	SafeDelete(s);

	return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(bool b) {
    if (b) {
        int newCount = count + 4;
        if (newCount > value.length())
            expandCapacity(newCount);
        value[count++] = 't';
        value[count++] = 'r';
        value[count++] = 'u';
        value[count++] = 'e';
    } else {
        int newCount = count + 5;
        if (newCount > value.length())
            expandCapacity(newCount);
        value[count++] = 'f';
        value[count++] = 'a';
        value[count++] = 'l';
        value[count++] = 's';
        value[count++] = 'e';
    }

	return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(wchar_u c) {
    int newCount = count + 1;

	if (newCount > value.length())
	    expandCapacity(newCount);

	value[count++] = c;
	return this;
}

static int sizeTable[] = { 9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999, Integer::MAX_VALUE };

// Requires positive x
static int stringSizeOfInt(int x) {
    for (int i=0; ; i++)
        if (x <= sizeTable[i])
            return i+1;
}

AbstractStringBuilder* AbstractStringBuilder::append(int i) {
    if (i == Integer::MIN_VALUE) {
        append("-2147483648");
        return this;
    }

    int appendedLength = (i < 0) ? stringSizeOfInt(-i) + 1 
                                 : stringSizeOfInt(i);

    int spaceNeeded = count + appendedLength;
    if (spaceNeeded > value.length())
        expandCapacity(spaceNeeded);

	Integer::getChars(i, spaceNeeded, const_cast<wchar_u*>(value.raw()));

    count = spaceNeeded;
    
    return this;
}

// Requires positive x
static int stringSizeOfLong(dg_long x) {
    dg_long p = 10;
    for (int i=1; i<19; i++) {
        if (x < p)
            return i;
        p = 10*p;
    }

    return 19;
}

AbstractStringBuilder* AbstractStringBuilder::append(dg_long l) {
    if (l == Long::MIN_VALUE) {
        append("-9223372036854775808");
        return this;
    }

    int appendedLength = (l < 0) ? stringSizeOfLong(-l) + 1 
                                 : stringSizeOfLong(l);

    int spaceNeeded = count + appendedLength;
    if (spaceNeeded > value.length())
        expandCapacity(spaceNeeded);

	Long::getChars(l, spaceNeeded, const_cast<wchar_u*>(value.raw()));
    count = spaceNeeded;

    return this;
}


