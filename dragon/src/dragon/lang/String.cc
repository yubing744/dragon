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

//#include <dragon/util/regex/regex.h>
#include <dragon/lang/Arrays.h>
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

	size_t rt = unicode_iconv(ic, (const char **) &from, &from_size, &to, &to_size);
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

	size_t rt = unicode_iconv(ic, (const char **) &from, &from_size, &to, &to_size);
	if (rt == -1){
		return EMPTY_BYTE_ARRAY;
	}

	unicode_iconv_close(ic);

	return Array<dg_byte>(buf, rt);
}

void String::destroy() {

}

// Member method

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
	while(*(cur++) != NULL_CHAR) {
		size++;
	}
	
	this->count = size;
	this->value = Arrays<dg_char>::copyOf(value, size);
}

String::String(string value){
	dg_int count = (dg_int)value.size();
	dg_int len = count;

	const char* raw = value.c_str();
	char* p = const_cast<char*>(raw);

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


String::String(wstring value){
	dg_int count = (dg_int)value.size();
	dg_int len = count;
	
	const wchar_t* raw = value.c_str();
	wchar_t* p = const_cast<wchar_t*>(raw);

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
	
	dg_int size = 0;
	dg_char* cur = const_cast<dg_char*>(value);
	while(*(cur++) != NULL_CHAR) {
		size++;
	}
	
	this->count = count;
	this->value = Arrays<dg_char>::copyOf(value, size, offset, count);
}

/*
void String::operator = (const dg_char*  str)
{
	mstr=wstring(str);
}


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


/*
dg_int String::hashCode()
{
	dg_int n=mstr.length();
	dg_int hc=0;

	for(dg_int i=0;i<n;i++)
	{
		hc+=(mstr[i]*(dg_int)Math::pow(31.0,n-i+1));
	}

	return hc;
}

dg_int String::indexOf(dg_char ch)
{
	return mstr.find_first_of(ch,0);
}

dg_int String::indexOf(dg_char ch,dg_int fromIndex)
{
	return mstr.find_first_of(ch,fromIndex);
}

dg_int String::indexOf(const dg_char* str)
{
	return mstr.find_first_of(str,0);
}

dg_int String::indexOf(CharSequence* s,dg_int fromIndex)
{
	dg_int mlen=this->length();
	dg_int slen=s->length();

	for(dg_int i=fromIndex;i<mlen;i++)
	{
		if(this->charAt(i)==s->charAt(0))
		{
			dg_boolean isEque=true;
			for(dg_int j=0;j<slen;j++)
			{
				if(this->charAt(i+j)!=s->charAt(j))
				{
					isEque=false;
					break;
				}
			}

			if(isEque)
			{
				return i;
			}
		}
	}

	return -1;
}
dg_int String::indexOf(CharSequence* s)
{
	return this->indexOf(s,0);
}


dg_int String::indexOf(String& str,dg_int fromIndex)
{
	return mstr.find_first_of(str.mstr,fromIndex);
}

dg_int String::lastIndexOf(dg_char ch)
{
	return mstr.find_last_of(ch,0);
}

dg_int String::lastIndexOf(dg_char ch,dg_int fromIndex)
{
	return mstr.find_last_of(ch,fromIndex);
}

dg_int String::lastIndexOf(const dg_char* str)
{
	return mstr.find_last_of(str,mstr.size());
}

dg_int String::lastIndexOf(const dg_char* str,dg_int fromIndex)
{
	return mstr.find_last_of(str,fromIndex);
}
*/

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

/*
String String::subString(dg_int beginIndex)
{
	return substring(beginIndex);
}

String String::subString(dg_int beginIndex,dg_int endIndex)
{
	return substring(beginIndex,endIndex);
}

String& String::concat(String& str)
{
	mstr.append(str.mstr);
	return *this;
}

String& String::append(const dg_char* str)
{
	mstr.append(str);
	return *this;
}

String& String::append(CharSequence* s)
{
	dg_int slen=s->length();
	dg_char* temp=new dg_char[slen+1];

	for(dg_int i=0;i<slen;i++)
	{
		temp[i]=s->charAt(i);
	}

	temp[slen]=0;
	mstr.append(temp);
	delete[] temp;

	return *this;
}

String& String::replace(dg_char oldChar,dg_char newChar)
{
	dg_int len=mstr.length();
	for(dg_int i=0;i<len;i++)
	{
		if(mstr[i]==oldChar)
		{
			mstr[i]=newChar;
		}
	}

	return *this;
}

dg_int String::compareTo(String& o)
{
	return mstr.compare(o.mstr);
}
*/

dg_char String::charAt(dg_int index) {
	if (index < 0) index = 0;

	if (index >= this->count) 
		index = this->count -1;

	return this->value[index];
}

dg_int String::length() const {
	return this->count;
}

/*
CharSequence* String::subSequence(dg_int start,dg_int end)
{
	return &this->substring(start,end);
}

String String::toString()
{
	return String(mstr);
}
*/

const dg_char* String::toChars() {
	return Arrays<dg_char>::copyOf(this->value, this->count);
}

Array<dg_char> String::toCharArray() {
	return Array<dg_char>(this->toChars(), this->count);
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

/*
dg_boolean String::contains(CharSequence* s)
{
	if(s==null)
	{
		throw NullPointerException();
	}

	dg_int mlen=this->length();
	dg_int slen=s->length();

	for(dg_int i=0;i<mlen;i++)
	{
		if(this->charAt(i)==s->charAt(0))
		{
			dg_boolean isEque=true;
			for(dg_int j=0;j<slen;j++)
			{
				if(this->charAt(i+j)!=s->charAt(j))
				{
					isEque=false;
					break;
				}
			}

			if(isEque)
			{
				return true;
			}
		}
	}

	return false;
}

dg_boolean String::contains(String s)
{
	dg_int pos=this->mstr.find(s.mstr,0);

	return pos>0?true:false;
}

String& String::replace(CharSequence* target,CharSequence* replacement)
{
	String* temp=new String();
	
	dg_int index1=0,index2=0;
	dg_int len=this->length();
	dg_int tlen=target->length();

	for(;;)
	{
		index2=this->indexOf(target,index1);
		if(index2==-1)
		{
			break;
		}

		temp->append(this->subSequence(index1,index2));
		temp->append(replacement);
		index1=index2+tlen;
		index2=index1;
	}

	temp->append(this->subSequence(index1,len));

	return *temp;
}

String& String::replaceFirst(String& regex,String& replacement)
{
	Regexp tempReg(regex);
	dg_char* result = tempReg.Replace(this->mstr.c_str(),replacement.mstr.c_str(),-1,1);
	return *new String(result);
}

String& String::replaceFirst(String& regex,const dg_char* replacement)
{
	Regexp tempReg(regex);
	dg_char* result = tempReg.Replace(this->mstr.c_str(),replacement,-1,1);
	return *new String(result);
}

String& String::replaceAll(String& regex,String& replacement)
{
	Regexp tempReg(regex);
	dg_char* result = tempReg.Replace(this->mstr.c_str(),replacement.mstr.c_str(),-1,-1);
	return *new String(result);
}

String& String::replaceAll(String& regex,const dg_char* replacement)
{
	Regexp tempReg(regex);
	dg_char* result = tempReg.Replace(this->mstr.c_str(),replacement,-1,-1);
	return *new String(result);
}

Array<String>& String::split(dg_char ch)
{
	dg_int npart=1;

	dg_int index=0;
	for(;;)
	{
		index=this->indexOf(ch,index);
		if(index==-1)
		{	
			break;
		}
		index++;
		npart++;
	}

	Array<String>& arr=*new Array<String>(npart);

	dg_int index1=0,index2=0;

	for(dg_int i=0;;i++)
	{
		index2=this->indexOf(ch,index1);
		if(index2==-1)
		{	
			arr[npart-1]=this->substring(index1,this->length());
			break;
		}
		
		arr[i]=this->substring(index1,index2);

		index1=index2+1;
		index2=index1;
	}

	return arr;
}

Array<String>& String::split(String reg)
{
	Regexp regexp(reg);

	CContext * pContext = regexp.PrepareMatch(this->mstr.c_str());


	dg_int npart=1;

    MatchResult result = regexp.Match(pContext);

    while( result.IsMatched() )
    {
		npart++;
        result = regexp.Match(pContext);
    }

	Array<String>& arr=*new Array<String>(npart);

	pContext = regexp.PrepareMatch(this->mstr.c_str());
	result = regexp.Match(pContext);

	dg_int index1=0,index2=0;
	dg_int i=0;
    while(result.IsMatched())
    {
		index2=result.GetStart();
		arr[i]=this->substring(index1,index2);
		index1=result.GetEnd();

        result = regexp.Match(pContext);
		i++;
    }

	arr[npart-1]=this->substring(index1,this->length());

    regexp.ReleaseContext(pContext);

	return arr;
}

String& String::toLowerCase()
{
	dg_int len=this->length();

	for(dg_int i=0;i<len;i++)
	{
		mstr[i]=tolower(mstr[i]);
	}

	return *this;
}

String& String::toUpperCase()
{
	dg_int len=this->length();

	for(dg_int i=0;i<len;i++)
	{
		mstr[i]=toupper(mstr[i]);
	}

	return *this;
}

String String::trim()
{
	dg_int start=0;
	dg_int end=this->length();

	if(end <= start) return String(mstr);

	for(dg_int i=0;i<end;i++)
	{
		if(mstr[i]>0x20)
		{
			start=i;
			break;
		}
	}

	for(dg_int i=end-1;i>start;i--)
	{
		if(mstr[i]>0x20)
		{
			end=i+1;
			break;
		}
	}

	return this->substring(start,end);
}


String& String::copyValueOf(const dg_char* data)
{
	return *new String(data);
}

String& String::copyValueOf(const dg_char* data,dg_int offset,dg_int count)
{
	return *new String(data,offset,count);
}

String String::format(const dg_char* format,...)
{
	dg_char text[256];
	va_list ap;

	va_start(ap, format);
	    vstprintf_s(text,256,format, ap);
	va_end(ap);	

	return String::valueOf(text);
}

String String::format(String& format, ...)
{
	dg_char text[256];
	va_list ap;

	const dg_char* fmt=format.mstr.c_str();

	va_start(ap, fmt);
	    vstprintf_s(text,256,fmt, ap);
	va_end(ap);	
        
	return String::valueOf(text);
}

String String::valueOf(dg_boolean b)
{
	if(b)
	{
		return String::valueOf(L"true");
	}

	return String::valueOf(L"false");
}

String String::valueOf(dg_char c)
{
	return String(&c);
}

String String::valueOf(dg_int i)
{
	return String::format(L"%d", i);
}

String String::valueOf(long l)
{
	return String::format(L"%ld", l);
}

String String::valueOf(float f)
{
	return String::format(L"%f", f);
}

String String::valueOf(double d)
{
	return String::format(L"%lf", d);
}

String String::valueOf(const Char* data)
{
	return String(data);
}

String String::valueOf(const Char* data, dg_int offset, dg_int count)
{
	return String(data, offset, count);
}*/

