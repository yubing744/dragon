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
	this->value = Array<dg_char>();
	this->count = 0;
}

AbstractStringBuilder::AbstractStringBuilder(dg_int capcity) {
	this->value = Array<dg_char>(new dg_char[capcity], capcity);
	this->count = 0;
}

AbstractStringBuilder::~AbstractStringBuilder() {
	this->value.release();
	this->count = 0;
}

dg_int AbstractStringBuilder::length(){
	return this->count;
}

dg_int AbstractStringBuilder::capcity() {
	return this->value.length();
}


void AbstractStringBuilder::ensureCapacity(dg_int minimumCapacity) {
	if (minimumCapacity > this->value.length()) {
	    this->expandCapacity(minimumCapacity);
	}
}


void AbstractStringBuilder::expandCapacity(dg_int minimumCapacity) {
	dg_int newCapacity = (this->value.length() + 1) * 2;

    if (newCapacity < 0) {
        newCapacity = 0;
    } else if (minimumCapacity > newCapacity) {
    	newCapacity = minimumCapacity;
	}	

	dg_char* newValue = new dg_char[newCapacity];
	Arrays<dg_char>::copyOf(value, 0, newValue, 0, count);
	this->value.release();

	this->value = Array<dg_char>(newValue, newCapacity);
}


void AbstractStringBuilder::trimToSize() {
    if (this->count < this->value.length()) {
        dg_char* newValue = new dg_char[count];
        Arrays<dg_char>::copyOf(value, 0, newValue, 0, count); 
		this->value = Array<dg_char>(newValue, count);
    }
}


void AbstractStringBuilder::setLength(dg_int newLength) {
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

dg_char AbstractStringBuilder::charAt(dg_int index) {
	return this->value[index];
}

void AbstractStringBuilder::getChars(dg_int srcBegin, dg_int srcEnd, dg_char* dst, dg_int dstBegin){
	Arrays<dg_char>::copyOf(value, srcBegin, dst, dstBegin, srcEnd - srcBegin);
}

void AbstractStringBuilder::setCharAt(dg_int index, dg_char ch) {
	value[index] = ch;
}

AbstractStringBuilder* AbstractStringBuilder::append(String* str) {
	if (str == null) 
		return append("null");
    
    dg_int len = str->length();

	if (len == 0) 
		return this;

	dg_int newCount = count + len;

	if (newCount > value.length())
	    expandCapacity(newCount);

	dg_char* dest = const_cast<dg_char*>(this->value.raw());
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

AbstractStringBuilder* AbstractStringBuilder::append(CharSequence* s, dg_int start, dg_int end) {
    if (s == null)
        return append("null");

    //if ((start < 0) || (end < 0) || (start > end) || (end > s->length()))
    //    throw new IndexOutOfBoundsException(
    //            "start " + start + ", end " + end + ", s.length() " 
    //            + s->length());

    dg_int len = end - start;
    if (len == 0)
        return this;

    dg_int newCount = count + len;
    if (newCount > value.length())
        expandCapacity(newCount);

    for (dg_int i=start; i<end; i++)
        value[count++] = s->charAt(i);

    count = newCount;
    return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(AbstractStringBuilder* sb) {
    if (sb == null)
        return append("null");

    dg_int len = sb->length();
    dg_int newCount = count + len;

    if (newCount > value.length())
        expandCapacity(newCount);

    sb->getChars(0, len, const_cast<dg_char*>(value.raw()), count);

    count = newCount;
    return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(const char* str) {
	String* s = new String(str);
	this->append(s);
	SafeDelete(s);

	return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(const wchar_t* str) {
	String* s = new String(str);
	this->append(s);
	SafeDelete(s);

	return this;
}

AbstractStringBuilder* AbstractStringBuilder::append(dg_boolean b) {
    if (b) {
        dg_int newCount = count + 4;
        if (newCount > value.length())
            expandCapacity(newCount);
        value[count++] = 't';
        value[count++] = 'r';
        value[count++] = 'u';
        value[count++] = 'e';
    } else {
        dg_int newCount = count + 5;
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

AbstractStringBuilder* AbstractStringBuilder::append(dg_char c) {
    dg_int newCount = count + 1;

	if (newCount > value.length())
	    expandCapacity(newCount);

	value[count++] = c;
	return this;
}

static dg_int sizeTable[] = { 9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999, Integer::MAX_VALUE };

// Requires positive x
static dg_int stringSizeOfInt(dg_int x) {
    for (dg_int i=0; ; i++)
        if (x <= sizeTable[i])
            return i+1;
}

AbstractStringBuilder* AbstractStringBuilder::append(dg_int i) {
    if (i == Integer::MIN_VALUE) {
        append("-2147483648");
        return this;
    }

    dg_int appendedLength = (i < 0) ? stringSizeOfInt(-i) + 1 
                                 : stringSizeOfInt(i);

    dg_int spaceNeeded = count + appendedLength;
    if (spaceNeeded > value.length())
        expandCapacity(spaceNeeded);

	Integer::getChars(i, spaceNeeded, const_cast<dg_char*>(value.raw()));

    count = spaceNeeded;
    
    return this;
}

// Requires positive x
static dg_int stringSizeOfLong(dg_long x) {
    dg_long p = 10;
    for (dg_int i=1; i<19; i++) {
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

    dg_int appendedLength = (l < 0) ? stringSizeOfLong(-l) + 1 
                                 : stringSizeOfLong(l);

    dg_int spaceNeeded = count + appendedLength;
    if (spaceNeeded > value.length())
        expandCapacity(spaceNeeded);

	Long::getChars(l, spaceNeeded, const_cast<dg_char*>(value.raw()));
    count = spaceNeeded;

    return this;
}


