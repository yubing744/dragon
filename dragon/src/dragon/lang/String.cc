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

#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <cwchar>

#include <unicode.h>
#include <convert.h>

#include <dragon/lang/String.h>
#include <dragon/lang/Arrays.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/Long.h>
#include <dragon/lang/NullPointerException.h>
#include <dragon/lang/IndexOutOfBoundsException.h>
#include <dragon/lang/UnsupportedEncodingException.h>

#include <dragon/util/regex/regex.h>


Import dragon::lang;
Import dragon::util::regex;


// static const variables
const char* String::LOCAL_UCS4_CHARSET = "UCS4-native";
const Array<wchar_u> String::EMPTY_CHAR_ARRAY = Array<wchar_u>();
const Array<byte> String::EMPTY_BYTE_ARRAY = Array<byte>();


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

Array<wchar_u> String::decode(Array<byte> bytes, int offset, int length, const char* charset) {
	if (length<0 || offset<0 || offset + length > bytes.size()) {
		throw new IndexOutOfBoundsException();
	}

	const char* fromcode = charset;
	if (fromcode == NULL) {
		fromcode = DEFAULT_CHARSET_NAME;
	}

	const char* tocode = LOCAL_UCS4_CHARSET;

	unicode_iconv_t ic;

    if ((ic = unicode_iconv_open(tocode, fromcode)) == (unicode_iconv_t) -1){
     	throw new UnsupportedEncodingException();
    }

	const byte* from = bytes.raw() + offset;
	size_t from_size = (size_t)length;

	size_t to_size = sizeof(wchar_u) * bytes.size();
	wchar_u* buf = new wchar_u[bytes.size() + 1];
	char* to = (char*)buf;

	int rt = unicode_iconv(ic, (const char **) &from, &from_size, &to, &to_size);
	if (rt == -1){
		throw new UnsupportedEncodingException();
	}

	unicode_iconv_close(ic);

	buf[rt] = NULL_CHAR;
	return Array<wchar_u>(buf, rt);
}

Array<byte> String::encode(Array<wchar_u> chars, int offset, int length, const char* charset) {
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

	const wchar_u* fromBuf = chars.raw() + offset;
	const char* from = (const char*)fromBuf;
	size_t from_size = (size_t)(length * sizeof(wchar_u));

	size_t to_size = from_size;
	byte* buf = new byte[to_size + 1];
	memset(buf, 0, to_size + 1);

	char* to = (char*)buf;

	int rt = unicode_iconv(ic, (const char **) &from, &from_size, &to, &to_size);
	if (rt == -1){
		return EMPTY_BYTE_ARRAY;
	}

	unicode_iconv_close(ic);

	int result_size = to - buf;
	return Array<byte>(buf, result_size, true);
}

void String::destroy() {

}

// -------------------------- Member method --------------------------------------

const Type* String::TYPE = TypeOf<String>();

String::String(){
   this->offset = 0;
   this->count = 0;
   this->value = NULL;
}

String::String(Array<byte> bytes, int offset) {
	Array<wchar_u> v = String::decode(bytes, offset, bytes.size(), null);
	size_t size = v.size();
	const wchar_u* value = v.raw();

	this->offset = 0;
	this->count = size;

	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value, offset, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->value = buf;
}

String::String(Array<byte> bytes, int offset, int length) {
	Array<wchar_u> v = String::decode(bytes, offset, length, null);
	size_t size = v.size();
	const wchar_u* value = v.raw();

	this->offset = 0;
	this->count = size;

	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value, offset, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->value = buf;
}

String::String(Array<byte> bytes, int offset, int length, const char* charset) {
	Array<wchar_u> v = String::decode(bytes, offset, length, charset);
	size_t size = v.size();
	const wchar_u* value = v.raw();

	this->offset = 0;
	this->count = size;

	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value, offset, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->value = buf;
}

String::String(const char* value){
	int count = strlen(value);
	int len = count;

	char* p = const_cast<char*>(value);

    wchar_u* buf = new wchar_u[count + 1];	
	wchar_u* pp = buf;

	if (len > 0) {
		while(len-- >0) *pp++ = *p++;
	}

	buf[count] = NULL_CHAR;

	this->offset = 0;
	this->count = count;
	this->value = buf;
}

String::String(const char* value, int length) {
	int count = strlen(value);
	count = (count>length) ? length : count;
	int len = count;

	char* p = const_cast<char*>(value);

    wchar_u* buf = new wchar_u[count + 1];	
	wchar_u* pp = buf;

	if (len > 0) {
		while(len-- >0) *pp++ = *p++;
	}

	buf[count] = NULL_CHAR;

	this->offset = 0;
	this->count = count;
	this->value = buf;	
}

String::String(const char* value, int offset, int length) {
	int count = strlen(value);
	count = (count > offset + length) ? length : count - offset;
	int len = count;

	char* p = const_cast<char*>(value) + offset;

    wchar_u* buf = new wchar_u[count + 1];	
	wchar_u* pp = buf;

	if (len > 0) {
		while(len-- >0) *pp++ = *p++;
	}

	buf[count] = NULL_CHAR;

	this->offset = 0;
	this->count = count;
	this->value = buf;	
}

String::String(const wchar_t* value){
	int count = wcslen(value);
	int len = count;
	
	wchar_t* p = const_cast<wchar_t*>(value);

    wchar_u* buf = new wchar_u[count + 1];	
	wchar_u* pp = buf;

	if (len > 0) {
		while(len-- >0) *pp++ = *p++;
	}

	buf[count] = NULL_CHAR;

	this->offset = 0;
	this->count = count;
	this->value = buf;	
}

String::String(const wchar_t* value, int length){
	int count = wcslen(value);
	count = (count>length) ? length : count;
	int len = count;

	wchar_t* p = const_cast<wchar_t*>(value);

    wchar_u* buf = new wchar_u[count + 1];	
	wchar_u* pp = buf;

	if (len > 0) {
		while(len-- >0) *pp++ = *p++;
	}

	buf[count] = NULL_CHAR;

	this->offset = 0;
	this->count = count;
	this->value = buf;	
}

String::String(const wchar_t* value, int offset, int length){
	int count = wcslen(value);
	count = (count > offset + length) ? length : count - offset;
	int len = count;

	wchar_t* p = const_cast<wchar_t*>(value) + offset;

    wchar_u* buf = new wchar_u[count + 1];	
	wchar_u* pp = buf;

	if (len > 0) {
		while(len-- >0) *pp++ = *p++;
	}

	buf[count] = NULL_CHAR;

	this->offset = 0;
	this->count = count;
	this->value = buf;	
}

String::String(const wchar_u* value){
	int size = 0;
	wchar_u* cur = const_cast<wchar_u*>(value);
	while(*(cur++) != null) {
		size++;
	}
	
	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value, 0, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->offset = 0;
	this->count = size;
	this->value = buf;
}

String::String(const wchar_u* value, int count){
	int size = count;

	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value, 0, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->offset = 0;
	this->count = size;
	this->value = buf;
}

String::String(const wchar_u* value, int offset, int count){
	int size = count;

	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value, offset, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->offset = 0;
	this->count = size;
	this->value = buf;
}

String::String(const String& value){
	int size = value.count;

	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value.value, 0, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->offset = 0;
	this->count = size;
	this->value = buf;
}

String::String(const String* value) {
	int size = value->count;
	
	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value->value, 0, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->offset = 0;
	this->count = size;
	this->value = buf;
}

String::String(int offset, int count, wchar_u* value) {
	this->value = value;
	this->offset = offset;
	this->count = count;
}

String::~String(){
	SafeDeleteArray(this->value);
	this->offset = 0;
	this->count = 0;
}

// ----------------------------------------------------------------------

String* String::operator = (const char* str) {
	return new String(str);
}

String* String::operator = (const wchar_t* str) {
	return new String(str);
}

String& String::operator = (const String& value) {
	SafeDeleteArray(this->value);

	int size = value.count;

	wchar_u* buf = new wchar_u[size + 1];	
	Arrays<wchar_u>::copyOf(value.value, 0, buf, 0, size);
	buf[size] = NULL_CHAR;

	this->offset = 0;
	this->count = size;
	this->value = buf;

	return *this;
}

/*
bool String::operator< (const String& str) const {
    String* theStr = const_cast<String*>(&this);
    String* otherStr = const_cast<String*>(&str);
	return theStr->compareTo(otherStr) > 0;
}
*/

bool String::equals(const String* str) const {
	if (str == null) {
		return false;
	}

	if (this == str) {
		return true;
	}

	if (this->count != str->count) {
		return false;
	}

	int size = str->count;
	
	for (int i=0; i<size; i++) {
		if (this->value[i] != str->value[i]) {
			return false;
		}
	}

	return true;
}

bool String::equals(const String& str) const {
	const String* pstr = &str;
	return this->equals(pstr);
}

bool String::startsWith(const String& prefix, int toffset) const {
	wchar_u* ta = this->value;
	int to = offset + toffset;

	wchar_u* pa = prefix.value;
	int po = prefix.offset;
	int pc = prefix.count;

	// Note: toffset might be near -1>>>1.
	if ((toffset < 0) || (toffset + pc > this->count)) {
	    return false;
	}

	while (--pc >= 0) {
	    if (ta[to++] != pa[po++]) {
	        return false;
	    }
	}
	
	return true;
}

bool String::startsWith(const String& prefix) const {
	return this->startsWith(prefix, 0);
}

bool String::endsWith(const String& suffix) const {
	return this->startsWith(suffix, this->count - suffix.count);
}

int String::hashCode() {
	int h = 0;

    int off = offset;
    wchar_u* val = value;
    int len = count;

    for (int i = 0; i < len; i++) {
        h = 31*h + val[off++];
    }

    return h;
}

int String::indexOf(wchar_u ch) const {
	return this->indexOf(ch, 0);
}

int String::indexOf(wchar_u ch, int fromIndex) const {
	int max = this->offset + this->count;
	wchar_u* v = this->value;

	if (fromIndex < 0) {
		fromIndex = 0;
	} else if (fromIndex >= this->count) {
		return -1;
	}

	int i = this->offset + fromIndex;

	for (; i<max; i++) {
		if (v[i] == ch) {
			return i - offset;
		}
	}

	return -1;
}

int String::indexOf(String* str) const {
	return this->indexOf(str, 0);
}

int String::indexOf(String* str, int fromIndex) const {
	wchar_u* source = this->value;
	int sourceOffset = this->offset;
	int sourceCount = this->count;

	wchar_u* target = str->value;
	int targetOffset = str->offset;
	int targetCount = str->count;

	if (fromIndex >= sourceCount) {
		return (targetCount == 0 ? sourceCount : -1);
	}

	if (fromIndex < 0) {
		fromIndex = 0;
	}

	if (targetCount == 0) {
		return fromIndex;
	}

	wchar_u first = target[targetOffset];
	int max = sourceOffset + (sourceCount - targetCount);

	for (int i = sourceOffset + fromIndex; i <= max; i++) {
		/* Look for first character. */
		if (source[i] != first) {
			while(++i <= max && source[i] != first) ;
		}

		/* Found fisrt character, now look at the rest of v2 */
		if (i <= max) {
			int j= i + 1;
			int end = j + targetCount - 1;

			for (int k = targetOffset + 1; j < end && source[j] == target[k]; j++, k++) ;

			if (j == end) {
				return i - sourceOffset;
			}
		}
	}

	return -1;
}

int String::lastIndexOf(wchar_u ch) {
	return this->lastIndexOf(ch, this->count - 1);
}

int String::lastIndexOf(wchar_u ch, int fromIndex) {
	int min = this->offset;
	wchar_u* v = this->value;

	int i = this->offset + ((fromIndex >= this->count) ? count - 1 : fromIndex);

	for (; i>=min; i--) {
		if (v[i] == ch) {
			return i - offset;
		}
	}

	return -1;	
}

int String::lastIndexOf(const String& str) const {
	return this->lastIndexOf(str, this->count - 1);
}

int String::lastIndexOf(const String& other, int fromIndex) const {
	const String* str = &other;

	wchar_u* source = this->value;
	int sourceOffset = this->offset;
	int sourceCount = this->count;

	wchar_u* target = str->value;
	int targetOffset = str->offset;
	int targetCount = str->count;


	int rightIndex = sourceCount - targetCount;

	if (fromIndex < 0) {
	    return -1;
	}

	if (fromIndex > rightIndex) {
	    fromIndex = rightIndex;
	}
	
	if (targetCount == 0) {
	    return fromIndex;
	}

    int strLastIndex = targetOffset + targetCount - 1;
	wchar_u strLastChar = target[strLastIndex];
	int min = sourceOffset + targetCount - 1;
	int i = min + fromIndex;

    startSearchForLastChar:

	while (true) {
	    while (i >= min && source[i] != strLastChar) {
			i--;
	    }

	    if (i < min) {
			return -1;
	    }

	    int j = i - 1;
	    int start = j - (targetCount - 1);
	    int k = strLastIndex - 1;

	    while (j > start) {
	        if (source[j--] != target[k--]) {
			    i--;
			    goto startSearchForLastChar;
			}
	    }

	    return start - sourceOffset + 1;
	}

    return -1;
}


String* String::substring(int beginIndex) const {
	return this->substring(beginIndex, this->count);
}

String* String::substring(int beginIndex, int endIndex) const {
	if (beginIndex < 0 || endIndex > this->count) {
		return null;
	}

	if (endIndex < beginIndex) {
		return null;
	}

	return new String(this->value + this->offset, beginIndex, endIndex - beginIndex);
}

String* String::concat(const String& other) const {
	const String* str = &other;

	int otherLen = str->length();
	if (otherLen == 0) {
	    return new String(this);
	}

	wchar_u* buf = new wchar_u[count + otherLen];
	getChars(0, count, buf, 0);
	str->getChars(0, otherLen, buf, count);
	return new String(0, count + otherLen, buf);
}


int String::compareTo(String* o) {
	wchar_u* p1 = this->value;
	wchar_u* p2 = o->value;

	int pc1 = this->count;
	int pc2 = o->count;

	while(pc1>0 && pc2>0) {
		wchar_u ch1 = *p1++;
		wchar_u ch2 = *p2++;

		int result = ch1 - ch2;

		if (result != 0) {
			return result;
		}

		pc1--;
		pc2--;
	}

	return pc1 - pc2;
}

int String::compareToIgnoreCase(String* str){
	wchar_u* p1 = this->value;
	wchar_u* p2 = str->value;

	int pc1 = this->count;
	int pc2 = str->count;

	while(pc1>0 || pc2>0) {
		wchar_u ch1 = *p1++;
		wchar_u ch2 = *p2++;

		int result = unicode_tolower(ch1) - unicode_tolower(ch2);

		if (result != 0) {
			return result;
		}

		pc1--;
		pc2--;
	}

	return pc1 - pc2;
}

wchar_u String::charAt(int index) const {
	if (index < 0) index = 0;

	if (index >= this->count) 
		index = this->count -1;

	return this->value[index];
}

int String::length() const {
	return this->count;
}

CharSequence* String::subSequence(int start, int end) const {
	return this->substring(start, end);
}

String* String::toString() const {
	return new String(this);
}

const wchar_u* String::toChars() const {
	return this->value + offset;
}

const Array<wchar_u> String::toCharArray() const {
	return Array<wchar_u>(this->value + offset, this->count, false);
}

void String::getChars(int srcBegin, int srcEnd, wchar_u* dst, int dstBegin) const {
    Arrays<wchar_u>::copyOf(value, offset + srcBegin, dst, dstBegin, srcEnd - srcBegin);
}

const Array<byte> String::getBytes() const {
	return this->getBytes(null);
}

const Array<byte> String::getBytes(const char* charset) const {
	return String::encode(Array<wchar_u>(this->value + this->offset, this->count, false), 0, this->count, charset);
}

const Array<byte> String::getBytes(const String& charset) const {
	char* charsetStr = charset.toCString();
	const Array<byte> result = String::encode(Array<wchar_u>(this->value + this->offset, this->count, false), 0, this->count, charsetStr);
	free(charsetStr);

	return result;
}

char* String::toUTF8String() const {
	const Array<byte> data = this->getBytes("UTF-8");
	
	char* utf8Data = (char*)malloc(data.size() + 1);
	memcpy(utf8Data, data.raw(), data.size());
	utf8Data[data.size()] = '\0';

	return utf8Data;
}

const Array<char> String::toUTF8CharArray() const {
	const Array<byte> data = this->getBytes("UTF-8");
	
	char* utf8Data = (char*)malloc(data.size() + 1);
	memcpy(utf8Data, data.raw(), data.size());
	utf8Data[data.size()] = '\0';

	return Array<char>(utf8Data, data.size() + 1);
}

char* String::toCString() const {
	const Array<byte> data = this->getBytes("ISO-8859-1");
	
	char* utf8Data = (char*)malloc(data.size() + 1);
	memcpy(utf8Data, data.raw(), data.size());
	utf8Data[data.size()] = '\0';

	return utf8Data;
}

wchar_t* String::toWCHARString() const {
	const Array<byte> data = this->getBytes("UCS-2");
	
	wchar_t* wcharData = (wchar_t*)malloc(data.size() / 2 + 2);
	memcpy(wcharData, data.raw(), data.size());
	wcharData[data.size() / 2] = '\0';

	return wcharData;
}

bool String::matches(const String& regex) const {
	String* str = const_cast<String*>(&regex);
	String* text = const_cast<String*>(this);
	return Pattern::matches(str, text);
}

bool String::matches(String* regex) const {
	String* text = const_cast<String*>(this);
	return Pattern::matches(regex, text);
}

bool String::contains(CharSequence* s) const {
	bool result = false;
	String* str = s->toString();
	result = this->indexOf(str) > -1;
	SafeDelete(str);

	return result;
}

bool String::contains(const String& s) const {
	return this->indexOf(const_cast<String*>(&s)) > -1;
}

String* String::replace(wchar_u oldChar, wchar_u newChar) {
	if (oldChar != newChar) {
	    int len = this->count;
	    int i = -1;
	    wchar_u* val = this->value; /* avoid getfield opcode */
	    int off = offset;   /* avoid getfield opcode */

	    while (++i < len) {
			if (val[off + i] == oldChar) {
			    break;
			}
	    }

	    if (i < len) {
			wchar_u* buf = new wchar_u[len];

			for (int j = 0 ; j < i ; j++) {
			    buf[j] = val[off+j];
			}

			while (i < len) {
			    wchar_u c = val[off + i];
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

    String* ret = this->replaceAll(targetStr, replacementStr);

    SafeDelete(targetStr);
    SafeDelete(replacementStr);

    return ret;
}

String* String::replaceAll(String* regex, String* replacement) {
    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(this);

    String* ret = m->replaceAll(replacement);
    
    SafeDelete(m);
    SafeDelete(p);

    return ret;
} 

String* String::replaceAll(const String& regex, const String& replacement) {
    Pattern* p = Pattern::compile(const_cast<String*>(&regex));
    Matcher* m = p->matcher(this);

    String* ret = m->replaceAll(const_cast<String*>(&replacement));
    
    SafeDelete(m);
    SafeDelete(p);

    return ret;
}

String* String::replaceFirst(String* regex, String* replacement) {

	return null;
}

Array<String*> String::split(const String& regex) const {
	const String* pstr = &regex;
	return split(pstr, 0);
}

Array<String*> String::split(const String* regex) const {
	return split(regex, 0);
}

Array<String*> String::split(const String* regex, int limit) const {
	Pattern* p = Pattern::compile(regex);
	Array<String*> result = p->split(this, limit);
	Pattern::release(p);

	return result;
}

String* String::toLowerCase() {
	wchar_u* buf = new wchar_u[this->count];
	this->getChars(0, this->count, buf, 0);

	for (int i=0; i<this->count; i++) {
		buf[i] = unicode_tolower(buf[i]);
	}

	return new String(0, this->count, buf);
}

String* String::toUpperCase(){
	wchar_u* buf = new wchar_u[this->count];
	this->getChars(0, this->count, buf, 0);

	for (int i=0; i<this->count; i++) {
		buf[i] = unicode_toupper(buf[i]);
	}

	return new String(0, this->count, buf);
}

String* String::trim() {
	int len = count;
	int st = 0;
	int off = offset;      /* avoid getfield opcode */
	wchar_u* val = value;    /* avoid getfield opcode */

	while ((st < len) && (val[off + st] <= ' ')) {
	    st++;
	}
	while ((st < len) && (val[off + len - 1] <= ' ')) {
	    len--;
	}

	return ((st > 0) || (len < count)) ? substring(st, len) : new String(this);
}


//----------------------------------------------------------

String* String::copyValueOf(const wchar_u* data) {
	return new String(data);
}

String* String::copyValueOf(const wchar_u* data, int offset, int count) {
	// All public String constructors now copy the data.
	return new String(data, offset, count);
}

String* String::vformat(String* format, va_list args) {
	char* data = format->toCString();
	int bufSize = strlen(data) * 4;

	int ret = bufSize;
	char* buf = null;
	
	do {
		bufSize = ret + 1;

		SafeDeleteArray(buf);
		buf = new char[bufSize];
		memset(buf, 0, bufSize);

		ret = vsnprintf(buf, bufSize - 1, data, args);
	} while(ret < 0 || ret > bufSize-1);

	String* result = new String(buf, 0, ret);
	SafeDeleteArray(buf);
	free(data);

	return result;
}

String* String::format(String* format, ...) {
	String* result = null;

	va_list args;
	va_start(args, format);
		result = String::vformat(format, args);
	va_end(args);

	return result;
}

String* String::vformat(const char* format, va_list arg) {
	String* result = null;

	String* fmt = new String(format);
	result = String::vformat(fmt, arg);
	SafeDelete(fmt);

	return result;
}

String* String::format(const char* format, ...) {
	String* result = null;

	String* fmt = new String(format);

	va_list ap;
	va_start(ap, format);
		result = String::vformat(fmt, ap);
	va_end(ap);
	
	SafeDelete(fmt);

	return result;
}

String* String::vformat(const wchar_t* format, va_list arg) {
	String* result = null;

	String* fmt = new String(format);
	result = String::vformat(fmt, arg);
	SafeDelete(fmt);

	return result;
}

String* String::format(const wchar_t* format, ...){
	String* result = null;

	String* fmt = new String(format);

	va_list ap;
	va_start(ap, format);
		result = String::vformat(fmt, ap);
	va_end(ap);
	
	SafeDelete(fmt);

	return result;
}


String* String::valueOf(const wchar_u* data, int offset, int count){
	return new String(data, offset, count);
}

String* String::valueOf(const wchar_u* data){
	return new String(data);
}

String* String::valueOf(const char* value){
	return new String(value);
}

String* String::valueOf(const wchar_t* value){
	return new String(value);
}

String* String::valueOf(bool b){
	return b ? new String("true") : new String("false");
}

String* String::valueOf(wchar_u c){
	wchar_u* data = new wchar_u[1];
	data[0] = c;
	return new String(0, 1, data);
}

String* String::valueOf(int i){
	return Integer::toString(i);
}

String* String::valueOf(dg_long l){
	return Long::toString(l);
}

String* String::valueOf(float f){
	return null;
}

String* String::valueOf(double d){
	return null;
}

