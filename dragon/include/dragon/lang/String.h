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

#ifndef String_Lang_H
#define String_Lang_H

#include <dragon/config.h>

#include <iostream>
#include <cstdlib>
#include <locale>

Import std;

#include "basic_type.h"

#include "Math.h"
#include "Array.h"
#include "Comparable.h"
#include "CharSequence.h"

#define vstprintf_s vswprintf_s
#define _ltot_s _ltow_s

BeginPackage2(dragon, lang)

class IndexOutOfBoundsException;
class NullPointerException;

class _DragonExport String : public Object, public Comparable<String>, 
	public CharSequence
{
	friend wostream& operator << (wostream& os,const String& str);
	friend wostream& operator << (wostream& os,String* str);
	friend size_t hash_value(const String& str);
	friend Boolean operator<(const String& left,const String& right);

public:
	String();
	String(wstring value);
	String(const String& value);
	String(const Char* value);
	String(const Char* value, int offset, int count) throw(IndexOutOfBoundsException);
	~String();

public:
	void operator = (const Char*  str);
	void operator = (wstring  str);

	String& operator+ (const String& str);
	String& operator+=(const String& str);
	Boolean operator==(const Char* str);
	Boolean operator==(const String& str);

	operator wstring();
	operator const Char*();
	operator size_t();

	size_t operator()(const String& str);

public:
	int compareTo(String& o);
	Boolean equals(const Char* str);
	Boolean startsWith(const Char* prefix);
	Boolean startsWith(const Char* prefix,int toffset);
	Boolean endsWith(String& suffix);
	int hashCode();

	int indexOf(Char ch);
	int indexOf(Char ch,int fromIndex);
	int indexOf(const Char* str);
	int indexOf(CharSequence* s);
	int indexOf(String& str,int fromIndex);
	int indexOf(CharSequence* s,int fromIndex);

	int lastIndexOf(Char ch);
	int lastIndexOf(Char ch,int fromIndex);
	int lastIndexOf(const Char* str);
	int lastIndexOf(const Char* str,int fromIndex);

	String substring(int beginIndex) throw(IndexOutOfBoundsException);
	String substring(int beginIndex,int endIndex) throw(IndexOutOfBoundsException);

	String subString(int beginIndex) throw(IndexOutOfBoundsException);
	String subString(int beginIndex,int endIndex) throw(IndexOutOfBoundsException);

	String& concat(String& str);
	String& append(const Char* str);
	String& append(CharSequence* s);
	String& replace(Char oldChar,Char newChar);

	int length();
	Char charAt(int index);
	CharSequence* subSequence(int start,int end) throw(IndexOutOfBoundsException);
	String toString();
	const Char* toCharArray();

	Boolean matches(String regex);
	Boolean contains(CharSequence* s) throw(NullPointerException);
	Boolean contains(String s); 

	String& replace(CharSequence* target,CharSequence* replacement);
	String& replaceFirst(String& regex,String& replacement);
	String& replaceFirst(String& regex,const Char* replacement);
	String& replaceAll(String& regex,String& replacement);
	String& replaceAll(String& regex,const Char* replacement);

	Array<String>& split(Char ch);
	Array<String>& split(String regex);

	String& toLowerCase();
	String& toUpperCase();
	String trim();

public:
	static String valueOf(const Char* data);
	static String valueOf(const Char* data,int offset,int count);

	static String& copyValueOf(const Char* data);
	static String& copyValueOf(const Char* data,int offset,int count);

	static String format(String& format,...);
	static String format(const Char* format,...);

	static String valueOf(Boolean b);
	static String valueOf(Char c);
	static String valueOf(const char* value);
	static String valueOf(int i);
	static String valueOf(long l);
	static String valueOf(float f);
	static String valueOf(double d);

private:
	wstring mstr;
};

inline wostream& operator << (wostream& os,const String& str)
{
    os<<str.mstr;
    return os;
}

inline wostream& operator << (wostream& os,String* str)
{
    os<<str->mstr;
    return os;
}

inline Boolean operator<(const String& left,const String& right)
{
	return left.mstr<right.mstr;
}

inline size_t hash_value(const String& str)
{
	int n=str.mstr.size();
	int hc=0;

	for(int i=0;i<n;i++)
	{
		hc+=(str.mstr[i]*(int)Math::pow(31.0,n-i+1));
	}

	return hc;
}

EndPackage2//(dragon,lang)

#endif//String_Lang_H