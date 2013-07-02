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

#include <dragon/lang/String.h>

#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <cwchar>

#include <unicode.h>
#include <convert.h>

#include <dragon/lang/Arrays.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/Long.h>

//#include <dragon/lang/NullPointerException.h>
//#include <dragon/lang/IndexOutOfBoundsException.h>

//#include "internal/platform.h"

#include <dragon/util/regex/regex.h>

//#define vstprintf_s vswprintf_s
//#define _ltot_s _ltow_s

Import dragon::lang;
Import dragon::util::regex;


// static const variables
const char* String::LOCAL_UCS4_CHARSET = "UCS4-native";
const Array<dg_char> String::EMPTY_CHAR_ARRAY = Array<dg_char>();
const Array<dg_byte> String::EMPTY_BYTE_ARRAY = Array<dg_byte>();


// Static variable and method
char* String::DEFAULT_CHARSET_NAME = String::init();

char* String::init() {
	atexit(String::destroy);

	unicode_init();

	char* charset;
	unicode_get_charset(&charset);

	if (charset) {
		return charset;
	}	

	return null;
}

Array<dg_char> String::decode(Array<dg_byte> bytes, dg_int offset, dg_int length, const char* charset) {
	if (length<0 || offset<0 || offset + length > bytes.size()) {
		return EMPTY_CHAR_ARRAY;
	}

	const char* fromcode = charset;
	if (fromcode == NULL) {
		fromcode = DEFAULT_CHARSET_NAME;
	}

	const char* tocode = LOCAL_UCS4_CHARSET;

	unicode_iconv_t ic;

    if ((ic = unicode_iconv_open(tocode, fromcode)) == (unicode_iconv_t) -1){
     	return EMPTY_CHAR_ARRAY;
    }

	const dg_byte* from = bytes.raw() + offset;
	size_t from_size = (size_t)length;

	size_t to_size = 4 * bytes.size();
	dg_char* buf = new dg_char[bytes.size() + 1];
	char* to = (char*)buf;

	int rt = unicode_iconv(ic, (const char **) &from, &from_size, &to, &to_size);
	if (rt == -1){
		return EMPTY_CHAR_ARRAY;
	}

	unicode_iconv_close(ic);

	buf[rt] = NULL_CHAR;
	return Array<dg_char>(buf, rt);
}

Array<dg_byte> String::encode(Array<dg_char> chars, dg_int offset, dg_int length, const char* charset) {
	if (length<0 || offset<0 || offset + length > chars.size()) {
		return EMPTY_BYTE_ARRAY;
	}

	const char* tocode = charset;
	if (tocode == NULL) {
		tocode = DEFAULT_CHARSET_NAME;
	}

	const char* fromcode = LOCAL_UCS4_CHARSET;

	unicode_iconv_t ic;

    if ((ic = unicode_iconv_open(tocode, fromcode)) == (unicode_iconv_t) -1){
     	return EMPTY_BYTE_ARRAY;
    }

	const dg_char* fromBuf = chars.raw() + offset;
	const char* from = (const char*)fromBuf;
	size_t from_size = (size_t)(length * 4);

	size_t to_size = from_size;
	dg_byte* buf = new dg_byte[to_size + 1];
	char* to = (char*)buf;

	int rt = unicode_iconv(ic, (const char **) &from, &from_size, &to, &to_size);
	if (rt == -1){
		return EMPTY_BYTE_ARRAY;
	}

	unicode_iconv_close(ic);

	return Array<dg_byte>(buf, rt);
}

void String::destroy() {

}

// -------------------------- Member method --------------------------------------

String::String(){
   this->offset = 0;
   this->count = 0;
   this->value = NULL;
}

String::~String(){
	SafeDeleteArray(this->value);
	this->offset = 0;
	this->count = 0;
}


String::String(Array<dg_byte> bytes, dg_int offset) {
	Array<dg_char> v = String::decode(bytes, offset, bytes.size(), null);

	this->offset = 0;
	this->count = v.size();
	this->value = const_cast<dg_char*>(v.raw());
}

String::String(Array<dg_byte> bytes, dg_int offset, dg_int length) {
	Array<dg_char> v = String::decode(bytes, offset, length, null);

	this->offset = 0;
	this->count = v.size();
	this->value = const_cast<dg_char*>(v.raw());
}

String::String(Array<dg_byte> bytes, dg_int offset, dg_int length, const char* charset) {
	Array<dg_char> v = String::decode(bytes, offset, length, charset);

	this->offset = 0;
	this->count = v.size();
	this->value = const_cast<dg_char*>(v.raw());
}


String::String(const dg_char* value){
	this->offset = 0;
	
	dg_int size = 0;
	dg_char* cur = const_cast<dg_char*>(value);
	while(*(cur++) != null) {
		size++;
	}
	
	this->count = size;
	this->value = Arrays<dg_char>::copyOf(value, size);
}

String::String(const char* value){
	dg_int count = strlen(value);
	dg_int len = count;

	char* p = const_cast<char*>(value);

    dg_char* buf = new dg_char[count + 1];	
	dg_char* pp = buf;

	if (len > 0) {
		while(len-- >0) *pp++ = *p++;
	}

	buf[count] = NULL_CHAR;

	this->offset = 0;
	this->count = count;
	this->value = buf;
}


String::String(const wchar_t* value){
	dg_int count = wcslen(value);
	dg_int len = count;
	
	wchar_t* p = const_cast<wchar_t*>(value);

    dg_char* buf = new dg_char[count + 1];	
	dg_char* pp = buf;

	if (len > 0) {
		while(len-- >0) *pp++ = *p++;
	}

	buf[count] = NULL_CHAR;

	this->offset = 0;
	this->count = count;
	this->value = buf;	
}

String::String(const String& value){
	this->offset = 0;
	this->count = value.count;
	this->value = Arrays<dg_char>::copyOf(value.value, value.count);
}

String::String(const String* value) {
	this->offset = 0;
	this->count = value->count;
	this->value = Arrays<dg_char>::copyOf(value->value, value->count);
}

String::String(const dg_char* value, dg_int offset, dg_int count){
	this->offset = 0;
	this->count = count;
	this->value = Arrays<dg_char>::copyOf(value, offset, count);
}

String::String(dg_int offset, dg_int count, dg_char* value) {
	this->value = value;
	this->offset = offset;
	this->count = count;
}

// ----------------------------------------------------------------------


String* String::operator = (const char* str) {
	return new String(str);
}

String* String::operator = (const wchar_t* str) {
	return new String(str);
}

/*
String& String::operator+(const String& str)
{
	mstr.append(str.mstr);
	return *this;
}

String& String::operator+=(const String& str)
{
	mstr.append(str.mstr);
	return *this;
}

dg_boolean String::operator==(const dg_char* str)
{
	if(this->mstr==str)
	{
		return true;
	}

	return false;
}

dg_boolean String::operator==(const String& str)
{
	if(this->mstr==str.mstr)
	{
		return true;
	}

	return false;

}

String::operator wstring()
{
	return mstr;
}

String::operator const dg_char*()
{
	return mstr.c_str();
}


String::operator size_t()
{
	return this->hashCode();
}

size_t String::operator()(const String& str)
{
	dg_int n=str.mstr.size();
	dg_int hc=0;

	for(dg_int i=0;i<n;i++)
	{
		hc+=(str.mstr[i]*(dg_int)Math::pow(31.0,n-i+1));
	}

	return hc;

}

*/

dg_boolean String::equals(const String* str) const {
	if (str == null) {
		return dg_false;
	}

	if (this == str) {
		return dg_true;
	}

	if (this->count != str->count) {
		return dg_false;
	}

	dg_int size = str->count;
	
	for (dg_int i=0; i<size; i++) {
		if (this->value[i] != str->value[i]) {
			return dg_false;
		}
	}

	return dg_true;
}


dg_boolean String::startsWith(const String* prefix, dg_int toffset) {
	dg_char* ta = this->value;
	dg_int to = offset + toffset;

	dg_char* pa = prefix->value;
	dg_int po = prefix->offset;
	dg_int pc = prefix->count;

	// Note: toffset might be near -1>>>1.
	if ((toffset < 0) || (toffset + pc > this->count)) {
	    return dg_false;
	}

	while (--pc >= 0) {
	    if (ta[to++] != pa[po++]) {
	        return dg_false;
	    }
	}
	
	return dg_true;
}

dg_boolean String::startsWith(const String* prefix) {
	return this->startsWith(prefix, 0);
}

dg_boolean String::endsWith(const String* suffix){
	return this->startsWith(suffix, this->count - suffix->count);
}

dg_int String::hashCode() {
	dg_int h = 0;

    dg_int off = offset;
    dg_char* val = value;
    dg_int len = count;

    for (dg_int i = 0; i < len; i++) {
        h = 31*h + val[off++];
    }

    return h;
}

dg_int String::indexOf(dg_char ch) {
	return this->indexOf(ch, 0);
}

dg_int String::indexOf(dg_char ch, dg_int fromIndex) {
	dg_int max = this->offset + this->count;
	dg_char* v = this->value;

	if (fromIndex < 0) {
		fromIndex = 0;
	} else if (fromIndex >= this->count) {
		return -1;
	}

	dg_int i = this->offset + fromIndex;

	for (; i<max; i++) {
		if (v[i] == ch) {
			return i - offset;
		}
	}

	return -1;
}

dg_int String::indexOf(String* str) {
	return this->indexOf(str);
}

dg_int String::indexOf(String* str, dg_int fromIndex) {
	dg_char* source = this->value;
	dg_int sourceOffset = this->offset;
	dg_int sourceCount = this->count;

	dg_char* target = str->value;
	dg_int targetOffset = str->offset;
	dg_int targetCount = str->count;

	if (fromIndex >= sourceCount) {
		return (targetCount == 0 ? sourceCount : -1);
	}

	if (fromIndex < 0) {
		fromIndex = 0;
	}

	if (targetCount == 0) {
		return fromIndex;
	}

	dg_char first = target[targetOffset];
	dg_int max = sourceOffset + (sourceCount - targetCount);

	for (dg_int i = sourceOffset + fromIndex; i <= max; i++) {
		/* Look for first character. */
		if (source[i] != first) {
			while(++i <= max && source[i] != first) ;
		}

		/* Found fisrt character, now look at the rest of v2 */
		if (i <= max) {
			dg_int j= i + 1;
			dg_int end = j + targetCount - 1;

			for (dg_int k = targetOffset + 1; j < end && source[j] == target[k]; j++, k++) ;

			if (j == end) {
				return i - sourceOffset;
			}
		}
	}

	return -1;
}

dg_int String::lastIndexOf(dg_char ch) {
	return this->lastIndexOf(ch, this->count - 1);
}

dg_int String::lastIndexOf(dg_char ch, dg_int fromIndex) {
	dg_int min = this->offset;
	dg_char* v = this->value;

	dg_int i = this->offset + ((fromIndex >= this->count) ? count - 1 : fromIndex);

	for (; i>=min; i--) {
		if (v[i] == ch) {
			return i - offset;
		}
	}

	return -1;	
}

dg_int String::lastIndexOf(String* str) {
	return this->lastIndexOf(str, this->count - 1);
}

dg_int String::lastIndexOf(String* str, dg_int fromIndex) {
	dg_char* source = this->value;
	dg_int sourceOffset = this->offset;
	dg_int sourceCount = this->count;

	dg_char* target = str->value;
	dg_int targetOffset = str->offset;
	dg_int targetCount = str->count;


	if (fromIndex >= sourceCount) {
        return (targetCount == 0 ? sourceCount : -1);
	}
    
    if (fromIndex < 0) {
    	fromIndex = 0;
    }

	if (targetCount == 0) {
	    return fromIndex;
	}

    dg_char first  = target[targetOffset];
    dg_int max = sourceOffset + (sourceCount - targetCount);

    for (dg_int i = sourceOffset + fromIndex; i <= max; i++) {
        /* Look for first character. */
        if (source[i] != first) {
            while (++i <= max && source[i] != first) ;
        }

        /* Found first character, now look at the rest of v2 */
        if (i <= max) {
            dg_int j = i + 1;
            dg_int end = j + targetCount - 1;
            for (dg_int k = targetOffset + 1; j < end && source[j] == 
                     target[k]; j++, k++) ;

            if (j == end) {
                /* Found whole string. */
                return i - sourceOffset;
            }
        }
    }

    return -1;
}


String* String::substring(dg_int beginIndex) {
	return this->substring(beginIndex, beginIndex + this->count);
}

String* String::substring(dg_int beginIndex, dg_int endIndex) {
	if (beginIndex < 0 || endIndex > this->count) {
		return null;
	}

	if (endIndex < beginIndex) {
		return null;
	}

	return new String(this->value + this->offset, beginIndex, endIndex - beginIndex);
}

String* String::concat(String* str) {
	dg_int otherLen = str->length();
	if (otherLen == 0) {
	    return this;
	}

	dg_char* buf = new dg_char[count + otherLen];
	getChars(0, count, buf, 0);
	str->getChars(0, otherLen, buf, count);
	return new String(0, count + otherLen, buf);
}


dg_int String::compareTo(String* o) {
	dg_char* p1 = this->value;
	dg_char* p2 = o->value;

	dg_int pc1 = this->count;
	dg_int pc2 = o->count;

	while(pc1>0 && pc2>0) {
		dg_char ch1 = *p1++;
		dg_char ch2 = *p2++;

		dg_int result = ch1 - ch2;

		if (result != 0) {
			return result;
		}

		pc1--;
		pc2--;
	}

	return pc1 - pc2;
}

dg_int String::compareToIgnoreCase(String* str){
	dg_char* p1 = this->value;
	dg_char* p2 = str->value;

	dg_int pc1 = this->count;
	dg_int pc2 = str->count;

	while(pc1>0 || pc2>0) {
		dg_char ch1 = *p1++;
		dg_char ch2 = *p2++;

		dg_int result = unicode_tolower(ch1) - unicode_tolower(ch2);

		if (result != 0) {
			return result;
		}

		pc1--;
		pc2--;
	}

	return pc1 - pc2;
}

dg_char String::charAt(dg_int index) {
	if (index < 0) index = 0;

	if (index >= this->count) 
		index = this->count -1;

	return this->value[index];
}

dg_int String::length() const {
	return this->count;
}

CharSequence* String::subSequence(dg_int start, dg_int end) {
	return this->substring(start, end);
}

String* String::toString()
{
	return new String(this);
}

const dg_char* String::toChars() {
	return Arrays<dg_char>::copyOf(this->value, this->count);
}

Array<dg_char> String::toCharArray() {
	return Array<dg_char>(this->toChars(), this->count);
}

void String::getChars(dg_int srcBegin, dg_int srcEnd, dg_char* dst, dg_int dstBegin) {
    Arrays<dg_char>::copyOf(value, offset + srcBegin, dst, dstBegin, srcEnd - srcBegin);
}

Array<dg_byte> String::getBytes() {
	return this->getBytes(null);
}

Array<dg_byte> String::getBytes(const char* charset) {
	return String::encode(Array<dg_char>(this->value + this->offset, this->count), 0, this->count, charset);
}

dg_boolean String::matches(String* regex) {
	return Pattern::matches(regex, this);
}


dg_boolean String::contains(CharSequence* s) {
	dg_boolean result = dg_false;
	String* str = s->toString();
	result = this->indexOf(str) > -1;
	SafeDelete(str);
	return result;
}

String* String::replace(dg_char oldChar, dg_char newChar) {
	if (oldChar != newChar) {
	    dg_int len = this->count;
	    dg_int i = -1;
	    dg_char* val = this->value; /* avoid getfield opcode */
	    dg_int off = offset;   /* avoid getfield opcode */

	    while (++i < len) {
			if (val[off + i] == oldChar) {
			    break;
			}
	    }

	    if (i < len) {
			dg_char* buf = new dg_char[len];

			for (dg_int j = 0 ; j < i ; j++) {
			    buf[j] = val[off+j];
			}

			while (i < len) {
			    dg_char c = val[off + i];
			    buf[i] = (c == oldChar) ? newChar : c;
			    i++;
			}

			return new String(buf, 0, len);
		}
	}

	return this;
}

String* String::replace(CharSequence* target, CharSequence* replacement) {
    String* targetStr = target->toString();
    String* replacementStr = replacement->toString();

    this->replaceAll(targetStr, replacementStr);

    SafeDelete(targetStr);
    SafeDelete(replacementStr);
}

String* String::replaceAll(String* regex, String* replacement) {
    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(this);

    String* ret = m->replaceAll(replacement);
    
    SafeDelete(m);
    SafeDelete(p);

    return ret;
} 

String* String::replaceFirst(String* regex, String* replacement) {

	return null;
}


Array<String*> String::split(dg_char ch) {
	return Array<String*>();
}

Array<String*> String::split(String* regex){
	return Array<String*>();
}

String* String::toLowerCase() {
	dg_char* buf = new dg_char[this->count];
	this->getChars(0, this->count, buf, 0);

	for (dg_int i=0; i<this->count; i++) {
		buf[i] = unicode_tolower(buf[i]);
	}

	return new String(0, this->count, buf);
}

String* String::toUpperCase(){
	dg_char* buf = new dg_char[this->count];
	this->getChars(0, this->count, buf, 0);

	for (dg_int i=0; i<this->count; i++) {
		buf[i] = unicode_toupper(buf[i]);
	}

	return new String(0, this->count, buf);
}

String* String::trim() {
	dg_int len = count;
	dg_int st = 0;
	dg_int off = offset;      /* avoid getfield opcode */
	dg_char* val = value;    /* avoid getfield opcode */

	while ((st < len) && (val[off + st] <= ' ')) {
	    st++;
	}
	while ((st < len) && (val[off + len - 1] <= ' ')) {
	    len--;
	}

	return ((st > 0) || (len < count)) ? substring(st, len) : new String(this);
}


//----------------------------------------------------------

String* String::copyValueOf(const dg_char* data) {
	return new String(data);
}

String* String::copyValueOf(const dg_char* data, dg_int offset, dg_int count) {
	// All public String constructors now copy the data.
	return new String(data, offset, count);
}

String* String::format(String* format, va_list args) {
	Array<dg_byte> data = format->getBytes("ISO-8859-1");
	int bufSize = data.size();

	int ret = 0;
	dg_byte* buf = null;

	do {
		bufSize*=2;
		SafeDeleteArray(buf);
		buf = new dg_byte[bufSize];
		memset(buf, '\0', bufSize);
		ret = vsnprintf(buf, bufSize - 1, data.raw(), args);
	} while(ret < 0 || ret>bufSize);

	data.release();

	String* result = new String(buf);
	SafeDeleteArray(buf);

	return result;
}


String* String::format(String* format, ...) {
	String* result = null;

	va_list args;
	va_start(args, format);
		result = String::format(format, args);
	va_end(args);

	return result;
}

String* String::format(const char* format, ...) {
	String* result = null;

	String* fmt = new String(format);

	va_list ap;
	va_start(ap, format);
		result = String::format(fmt, ap);
	va_end(ap);
	
	SafeDelete(fmt);

	return result;
}

String* String::format(const wchar_t* format, ...){
	String* result = null;

	String* fmt = new String(format);

	va_list ap;
	va_start(ap, format);
		result = String::format(fmt, ap);
	va_end(ap);
	
	SafeDelete(fmt);

	return result;
}


String* String::valueOf(const dg_char* data, dg_int offset, dg_int count){
	return new String(data, offset, count);
}

String* String::valueOf(const dg_char* data){
	return new String(data);
}

String* String::valueOf(const char* value){
	return new String(value);
}

String* String::valueOf(const wchar_t* value){
	return new String(value);
}

String* String::valueOf(dg_boolean b){
	return b ? new String("true") : new String("false");
}

String* String::valueOf(dg_char c){
	dg_char* data = new dg_char[1];
	data[0] = c;
	return new String(0, 1, data);
}


String* String::valueOf(dg_int i){
	return Integer::toString(i);
}

String* String::valueOf(dg_long l){
	return Long::toString(l);
}

String* String::valueOf(dg_float f){
	return null;
}

String* String::valueOf(dg_double d){
	return null;
}

