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

#include "Math.h"
#include "Array.h"
//#include "Comparable.h"
//#include "CharSequence.h"

BeginPackage2(dragon, lang)

class _DragonExport String
	//public CharSequence
{
	/*
	friend wostream& operator << (wostream& os,const String& str);
	friend wostream& operator << (wostream& os,String* str);
	friend size_t hash_value(const String& str);
	friend dg_boolean operator<(const String& left,const String& right);
    */
	
public:
	String();
	String(string value);
	String(wstring value);
    String(const String& value);
	String(const dg_char* value);
	String(const String* value);
   	String(const dg_char* value, dg_int offset, dg_int count);
	~String();
/*
public:
	void operator = (const dg_char*  str);
	void operator = (wstring  str);

	String& operator+ (const String& str);
	String& operator+=(const String& str);
	dg_boolean operator==(const dg_char* str);
	dg_boolean operator==(const String& str);

	operator wstring();
	operator const Char*();
	operator size_t();

	size_t operator()(const String& str);

public:
	dg_int compareTo(String& o);
	*/


    /**
     * Compares this string to the specified object.
     * The result is <code>true</code> if and only if the argument is not
     * <code>null</code> and is a <code>String</code> object that represents
     * the same sequence of characters as this object.
     *
     * @param   str   the object to compare this <code>String</code>
     *                     against.
     * @return  <code>dg_true</code> if the <code>String </code>are equal;
     *          <code>dg_false</code> otherwise.
     * @see     dragon.lang.String#compareTo(const dragon.lang.String*)
     * @see     dragon.lang.String#equalsIgnoreCase(const dragon.lang.String*)
     */
	dg_boolean equals(const String* str);

	/**
     * Tests if this string starts with the specified prefix beginning
     * a specified index.
     *
     * @param   prefix    the prefix.
     * @param   toffset   where to begin looking in the string.
     * @return  <code>dg_true</code> if the character sequence represented by the
     *          argument is a prefix of the substring of this object starting
     *          at index <code>toffset</code>; <code>dg_false</code> otherwise.
     *          The result is <code>false</code> if <code>toffset</code> is
     *          negative or greater than the length of this
     *          <code>String</code> object; otherwise the result is the same
     *          as the result of the expression
     *          <pre>
     *          this->substring(toffset)->startsWith(prefix)
     *          </pre>
     */
	dg_boolean startsWith(const String* prefix, dg_int toffset);

    /**
     * Tests if this string starts with the specified prefix.
     *
     * @param   prefix   the prefix.
     * @return  <code>dg_true</code> if the character sequence represented by the
     *          argument is a prefix of the character sequence represented by
     *          this string; <code>dg_false</code> otherwise.
     *          Note also that <code>true</code> will be returned if the
     *          argument is an empty string or is equal to this
     *          <code>String</code> object as determined by the
     *          {@link #equals(Object)} method.
     * @since   1. 0
     */	
	dg_boolean startsWith(const String* prefix);

    /**
     * Tests if this string ends with the specified suffix.
     *
     * @param   suffix   the suffix.
     * @return  <code>dg_true</code> if the character sequence represented by the
     *          argument is a suffix of the character sequence represented by
     *          this object; <code>dg_false</code> otherwise. Note that the
     *          result will be <code>true</code> if the argument is the
     *          empty string or is equal to this <code>String</code> object
     *          as determined by the {@link #equals(Object)} method.
     */
	dg_boolean endsWith(const String* suffix);

	/*
	dg_int hashCode();

	dg_int indexOf(dg_char ch);
	dg_int indexOf(dg_char ch,dg_int fromIndex);
	dg_int indexOf(const dg_char* str);
	dg_int indexOf(CharSequence* s);
	dg_int indexOf(String& str,dg_int fromIndex);
	dg_int indexOf(CharSequence* s,dg_int fromIndex);

	dg_int lastIndexOf(dg_char ch);
	dg_int lastIndexOf(dg_char ch,dg_int fromIndex);
	dg_int lastIndexOf(const dg_char* str);
	dg_int lastIndexOf(const dg_char* str,dg_int fromIndex);

	String substring(dg_int beginIndex);
	String substring(dg_int beginIndex,dg_int endIndex);

	String subString(dg_int beginIndex);
	String subString(dg_int beginIndex,dg_int endIndex);

	String& concat(String& str);
	String& append(const dg_char* str);
	String& append(CharSequence* s);
	String& replace(dg_char oldChar,dg_char newChar);
*/
public:
	dg_int length() const;
	dg_char charAt(dg_int index);


/*
	CharSequence* subSequence(dg_int start,dg_int end);
	String toString();
*/

	const dg_char* toChars();
	Array<dg_char> toCharArray();

/*
	dg_boolean matches(String regex);
	dg_boolean contains(CharSequence* s);
	dg_boolean contains(String s); 

	String& replace(CharSequence* target,CharSequence* replacement);
	String& replaceFirst(String& regex,String& replacement);
	String& replaceFirst(String& regex,const dg_char* replacement);
	String& replaceAll(String& regex,String& replacement);
	String& replaceAll(String& regex,const dg_char* replacement);

	Array<String>& split(dg_char ch);
	Array<String>& split(String regex);

	String& toLowerCase();
	String& toUpperCase();
	String trim();

public:
	static String valueOf(const dg_char* data);
	static String valueOf(const dg_char* data,dg_int offset,dg_int count);

	static String& copyValueOf(const dg_char* data);
	static String& copyValueOf(const dg_char* data,dg_int offset,dg_int count);

	static String format(String& format,...);
	static String format(const dg_char* format,...);

	static String valueOf(dg_boolean b);
	static String valueOf(dg_char c);
	static String valueOf(const char* value);
	static String valueOf(dg_int i);
	static String valueOf(long l);
	static String valueOf(float f);
	static String valueOf(double d);
*/

private:
	dg_char* value;
	dg_int offset;
	dg_int count;
};

/*
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

inline dg_boolean operator<(const String& left,const String& right)
{
	return left.mstr<right.mstr;
}

inline size_t hash_value(const String& str)
{
	dg_int n=str.mstr.size();
	dg_int hc=0;

	for(dg_int i=0;i<n;i++)
	{
		hc+=(str.mstr[i]*(dg_int)Math::pow(31.0, n-i+1));
	}

	return hc;
}
*/

EndPackage2//(dragon, lang)

#endif//String_Lang_H
