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

#include <stdarg.h>
#include <ctype.h>
#include <cwchar>

//#include <dragon/util/regex/regex.h>
#include <dragon/lang/Arrays.h>
#include <dragon/lang/NullPointerException.h>
#include <dragon/lang/IndexOutOfBoundsException.h>

//#include "internal/platform.h"

//#define vstprintf_s vswprintf_s
//#define _ltot_s _ltow_s

Import dragon::lang;
//Import dragon::util::regex;

String::String(){
   this->offset = 0;
   this->count = 0;
   this->value = NULL;
}

String::~String(){
	if (this->value != NULL) {
		delete[] this->value;
	}
}

String::String(const Char* value){
	this->offset = 0;
	
	int size = 0;
	Char* cur = const_cast<Char*>(value);
	while(*(cur++) != NULL_CHAR) {
		size++;
	}
	
	this->count = size;
	this->value = Arrays<Char>::copyOf(value, size);
}

String::String(string value){
	this->offset = 0;
	int count = (int)value.size();
	const char* raw = value.c_str();

    Char* buf = new Char[count + 1];	
	char* target = (char*)buf;

	for (int i=0; i<count; i++) {
		target[i*4] = '\0';
		target[i*4 + 1] = '\0';
		target[i*4 + 2] = '\0';
		target[i*4 + 3] = raw[i];
	}

	buf[count] = NULL_CHAR;

	this->count = count;
	this->value = buf;
}


String::String(wstring value){
	int offset = 0;
	int count = (int)value.size();
	const wchar_t* raw = value.c_str();

    Char* buf = new Char[count + 1];	
	char* target = (char*)buf;

	for (int i=0; i<count; i++) {
		char* pch = (char*)(&raw[i]);

		target[i*4] = '\0';
		target[i*4 + 1] = '\0';
		target[i*4 + 2] = pch[0];
		target[i*4 + 3] = pch[1];
	}

	buf[count] = NULL_CHAR;

	this->offset = offset;
	this->count = count;
	this->value = buf;	
}

String::String(const String& value){
	this->offset = 0;
	this->count = value.count;
	this->value = Arrays<Char>::copyOf(value.value, value.count);
}

String::String(const String* value) {
	this->offset = 0;
	this->count = value->count;
	this->value = Arrays<Char>::copyOf(value->value, value->count);
}

String::String(const Char* value, int offset, int count){
	this->offset = 0;
	
	int size = 0;
	Char* cur = const_cast<Char*>(value);
	while(*(cur++) != NULL_CHAR) {
		size++;
	}
	
	this->count = size;
	this->value = Arrays<Char>::copyOf(value, size, offset, count);
}

/*
void String::operator = (const Char*  str)
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

Boolean String::operator==(const Char* str)
{
	if(this->mstr==str)
	{
		return true;
	}

	return false;
}

Boolean String::operator==(const String& str)
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

String::operator const Char*()
{
	return mstr.c_str();
}


String::operator size_t()
{
	return this->hashCode();
}

size_t String::operator()(const String& str)
{
	int n=str.mstr.size();
	int hc=0;

	for(int i=0;i<n;i++)
	{
		hc+=(str.mstr[i]*(int)Math::pow(31.0,n-i+1));
	}

	return hc;

}

*/

Boolean String::equals(const String* str) {
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

/*
Boolean String::startsWith(const Char* prefix)
{
	wstring temp(prefix);

	if(mstr.substr(0,temp.length())==temp)
	{
		return true;
	}

	return false;
}

Boolean String::startsWith(const Char* prefix,int toffset)
{
	wstring temp(prefix);

	if(mstr.substr(toffset,temp.length())==temp)
	{
		return true;
	}

	return false;
}

Boolean String::endsWith(String& suffix)
{
	int mlen=mstr.length();
	int slen=suffix.mstr.length();
	
	if(mlen<slen)
	{
		return false;
	}

	if(mstr.substr(mlen-slen,slen)==suffix.mstr)
	{
		return true;
	}

	return false;
}

int String::hashCode()
{
	int n=mstr.length();
	int hc=0;

	for(int i=0;i<n;i++)
	{
		hc+=(mstr[i]*(int)Math::pow(31.0,n-i+1));
	}

	return hc;
}

int String::indexOf(Char ch)
{
	return mstr.find_first_of(ch,0);
}

int String::indexOf(Char ch,int fromIndex)
{
	return mstr.find_first_of(ch,fromIndex);
}

int String::indexOf(const Char* str)
{
	return mstr.find_first_of(str,0);
}

int String::indexOf(CharSequence* s,int fromIndex)
{
	int mlen=this->length();
	int slen=s->length();

	for(int i=fromIndex;i<mlen;i++)
	{
		if(this->charAt(i)==s->charAt(0))
		{
			Boolean isEque=true;
			for(int j=0;j<slen;j++)
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
int String::indexOf(CharSequence* s)
{
	return this->indexOf(s,0);
}


int String::indexOf(String& str,int fromIndex)
{
	return mstr.find_first_of(str.mstr,fromIndex);
}

int String::lastIndexOf(Char ch)
{
	return mstr.find_last_of(ch,0);
}

int String::lastIndexOf(Char ch,int fromIndex)
{
	return mstr.find_last_of(ch,fromIndex);
}

int String::lastIndexOf(const Char* str)
{
	return mstr.find_last_of(str,mstr.size());
}

int String::lastIndexOf(const Char* str,int fromIndex)
{
	return mstr.find_last_of(str,fromIndex);
}

String String::substring(int beginIndex)
{
	int len=mstr.length();
	
	if(beginIndex<0 || beginIndex>=len)
	{
		throw IndexOutOfBoundsException();
	}

	return String(mstr.substr(beginIndex,len-beginIndex));
}

String String::substring(int beginIndex,int endIndex)
{
	int len=mstr.length();

	if (endIndex == beginIndex) return String(L"");

	if(beginIndex<0 || beginIndex>=len || beginIndex>endIndex || endIndex<0 || endIndex>len)
	{
		throw IndexOutOfBoundsException();
	}

	return String(mstr.substr(beginIndex,endIndex-beginIndex));
}

String String::subString(int beginIndex)
{
	return substring(beginIndex);
}

String String::subString(int beginIndex,int endIndex)
{
	return substring(beginIndex,endIndex);
}

String& String::concat(String& str)
{
	mstr.append(str.mstr);
	return *this;
}

String& String::append(const Char* str)
{
	mstr.append(str);
	return *this;
}

String& String::append(CharSequence* s)
{
	int slen=s->length();
	Char* temp=new Char[slen+1];

	for(int i=0;i<slen;i++)
	{
		temp[i]=s->charAt(i);
	}

	temp[slen]=0;
	mstr.append(temp);
	delete[] temp;

	return *this;
}

String& String::replace(Char oldChar,Char newChar)
{
	int len=mstr.length();
	for(int i=0;i<len;i++)
	{
		if(mstr[i]==oldChar)
		{
			mstr[i]=newChar;
		}
	}

	return *this;
}

int String::compareTo(String& o)
{
	return mstr.compare(o.mstr);
}
*/

Char String::charAt(int index)
{
	if (index < 0) index = 0;
	if (index >= this->count) index = this->count -1;

	return this->value[index];
}

int String::length()
{
	return this->count;
}

/*
CharSequence* String::subSequence(int start,int end)
{
	return &this->substring(start,end);
}

String String::toString()
{
	return String(mstr);
}
*/

const Char* String::toChars() {
	return Arrays<Char>::copyOf(this->value, this->count);
}

Array<Char> String::toCharArray()
{
	return Array<Char>(this->value, this->count);
}

/*
Boolean String::matches(String regex)
{
	Regexp tempReg(regex);
	MatchResult result = tempReg.MatchExact(this->mstr.c_str());
	return result.IsMatched()!=0;
}

Boolean String::contains(CharSequence* s)
{
	if(s==null)
	{
		throw NullPointerException();
	}

	int mlen=this->length();
	int slen=s->length();

	for(int i=0;i<mlen;i++)
	{
		if(this->charAt(i)==s->charAt(0))
		{
			Boolean isEque=true;
			for(int j=0;j<slen;j++)
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

Boolean String::contains(String s)
{
	int pos=this->mstr.find(s.mstr,0);

	return pos>0?true:false;
}

String& String::replace(CharSequence* target,CharSequence* replacement)
{
	String* temp=new String();
	
	int index1=0,index2=0;
	int len=this->length();
	int tlen=target->length();

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
	Char* result = tempReg.Replace(this->mstr.c_str(),replacement.mstr.c_str(),-1,1);
	return *new String(result);
}

String& String::replaceFirst(String& regex,const Char* replacement)
{
	Regexp tempReg(regex);
	Char* result = tempReg.Replace(this->mstr.c_str(),replacement,-1,1);
	return *new String(result);
}

String& String::replaceAll(String& regex,String& replacement)
{
	Regexp tempReg(regex);
	Char* result = tempReg.Replace(this->mstr.c_str(),replacement.mstr.c_str(),-1,-1);
	return *new String(result);
}

String& String::replaceAll(String& regex,const Char* replacement)
{
	Regexp tempReg(regex);
	Char* result = tempReg.Replace(this->mstr.c_str(),replacement,-1,-1);
	return *new String(result);
}

Array<String>& String::split(Char ch)
{
	int npart=1;

	int index=0;
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

	int index1=0,index2=0;

	for(int i=0;;i++)
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


	int npart=1;

    MatchResult result = regexp.Match(pContext);

    while( result.IsMatched() )
    {
		npart++;
        result = regexp.Match(pContext);
    }

	Array<String>& arr=*new Array<String>(npart);

	pContext = regexp.PrepareMatch(this->mstr.c_str());
	result = regexp.Match(pContext);

	int index1=0,index2=0;
	int i=0;
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
	int len=this->length();

	for(int i=0;i<len;i++)
	{
		mstr[i]=tolower(mstr[i]);
	}

	return *this;
}

String& String::toUpperCase()
{
	int len=this->length();

	for(int i=0;i<len;i++)
	{
		mstr[i]=toupper(mstr[i]);
	}

	return *this;
}

String String::trim()
{
	int start=0;
	int end=this->length();

	if(end <= start) return String(mstr);

	for(int i=0;i<end;i++)
	{
		if(mstr[i]>0x20)
		{
			start=i;
			break;
		}
	}

	for(int i=end-1;i>start;i--)
	{
		if(mstr[i]>0x20)
		{
			end=i+1;
			break;
		}
	}

	return this->substring(start,end);
}


String& String::copyValueOf(const Char* data)
{
	return *new String(data);
}

String& String::copyValueOf(const Char* data,int offset,int count)
{
	return *new String(data,offset,count);
}

String String::format(const Char* format,...)
{
	Char text[256];
	va_list ap;

	va_start(ap, format);
	    vstprintf_s(text,256,format, ap);
	va_end(ap);	

	return String::valueOf(text);
}

String String::format(String& format, ...)
{
	Char text[256];
	va_list ap;

	const Char* fmt=format.mstr.c_str();

	va_start(ap, fmt);
	    vstprintf_s(text,256,fmt, ap);
	va_end(ap);	
        
	return String::valueOf(text);
}

String String::valueOf(Boolean b)
{
	if(b)
	{
		return String::valueOf(L"true");
	}

	return String::valueOf(L"false");
}

String String::valueOf(Char c)
{
	return String(&c);
}

String String::valueOf(int i)
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

String String::valueOf(const Char* data, int offset, int count)
{
	return String(data, offset, count);
}*/

