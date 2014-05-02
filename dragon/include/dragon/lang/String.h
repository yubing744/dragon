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

#ifndef String_Lang_Dragon_H
#define String_Lang_Dragon_H

#include <dragon/config.h>

#include <dragon/lang/Math.h>
#include <dragon/lang/Array.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Comparable.h>
#include <dragon/lang/CharSequence.h>

#include <iostream>
#include <cstdlib>
#include <locale>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

BeginPackage2(dragon, lang)

Import std;

/**
 * The <code>String</code> class represents character strings. All
 * string literals in Java programs, such as <code>"abc"</code>, are
 * implemented as instances of this class.
 * <p>
 * Strings are constant; their values cannot be changed after they
 * are created. String buffers support mutable strings.
 * Because String objects are immutable they can be shared. For example:
 * <p><blockquote><pre>
 *     String str = "abc";
 * </pre></blockquote><p>
 * is equivalent to:
 * <p><blockquote><pre>
 *     char data[] = {'a', 'b', 'c'};
 *     String str = new String(data);
 * </pre></blockquote><p>
 * Here are some more examples of how strings can be used:
 * <p><blockquote><pre>
 *     System.out.println("abc");
 *     String cde = "cde";
 *     System.out.println("abc" + cde);
 *     String c = "abc".substring(2,3);
 *     String d = cde.substring(1, 2);
 * </pre></blockquote>
 * <p>
 * The class <code>String</code> includes methods for examining
 * individual characters of the sequence, for comparing strings, for
 * searching strings, for extracting substrings, and for creating a
 * copy of a string with all characters translated to uppercase or to
 * lowercase. Case mapping is based on the Unicode Standard version 
 * specified by the {@link java.lang.Character Character} class.
 * <p>
 * The Java language provides special support for the string
 * concatenation operator (&nbsp;+&nbsp;), and for conversion of
 * other objects to strings. String concatenation is implemented
 * through the <code>StringBuilder</code>(or <code>StringBuffer</code>)
 * class and its <code>append</code> method.
 * String conversions are implemented through the method
 * <code>toString</code>, defined by <code>Object</code> and
 * inherited by all classes in Java. For additional information on
 * string concatenation and conversion, see Gosling, Joy, and Steele,
 * <i>The Java Language Specification</i>.
 *
 * <p> Unless otherwise noted, passing a <tt>null</tt> argument to a constructor
 * or method in this class will cause a {@link NullPointerException} to be
 * thrown.
 *
 * <p>A <code>String</code> represents a string in the UTF-16 format
 * in which <em>supplementary characters</em> are represented by <em>surrogate
 * pairs</em> (see the section <a href="Character.html#unicode">Unicode
 * Character Representations</a> in the <code>Character</code> class for
 * more information).
 * Index values refer to <code>char</code> code units, so a supplementary
 * character uses two positions in a <code>String</code>.
 * <p>The <code>String</code> class provides methods for dealing with
 * Unicode code points (i.e., characters), in addition to those for
 * dealing with Unicode code units (i.e., <code>char</code> values).
 */
class _DragonExport String extends(Object) 
     implements2(CharSequence, Comparable<String>)
{
public:
	friend wostream& operator << (wostream& os, const String& str);
	friend wostream& operator << (wostream& os, String* str);
	friend size_t hash_value(const String& str);
	friend bool operator<(const String& left, const String& right);

//-------------------------------------------------------------------
public:
     static const Type* TYPE;

private:
	static const char* LOCAL_UCS4_CHARSET;
	static const Array<wchar_u> EMPTY_CHAR_ARRAY;
	static const Array<byte> EMPTY_BYTE_ARRAY;

private:
	static char* init();
	static void destroy();

public:
     static char* DEFAULT_CHARSET_NAME;
     static Array<wchar_u> decode(Array<byte> bytes, int offset, int length, const char* charset);
     static Array<byte> encode(Array<wchar_u> chars, int offset, int length, const char* charset);

public:
	String();

     String(const char* value);
     String(const char* value, int length);
     String(const char* value, int offset, int length);

     String(const wchar_t* value);
     String(const wchar_t* value, int length);
     String(const wchar_t* value, int offset, int length);

     String(const wchar_u* value);
     String(const wchar_u* value, int length);
     String(const wchar_u* value, int offset, int length);
     
	String(Array<byte> bytes, int length);
	String(Array<byte> bytes, int offset, int length);
	String(Array<byte> bytes, int offset, int length, const char* charset);

     String(const String& value);
     String(const String* value);

	~String();

protected:
	// Package private constructor which shares value array for speed.
	String(int offset, int count, wchar_u* value);

public:
	String* operator = (const char* str);
	String* operator = (const wchar_t* str);
     String& operator = (const String& str);

     String* operator->() { return this; };
     const String* operator->() const { return this; };

     //bool operator< (const String& str) const;	
/*
	String& operator+ (const String& str);
	String& operator+=(const String& str);
	bool operator==(const wchar_u* str);
	bool operator==(const String& str);

	operator wstring();
	operator string();

	operator size_t();
	size_t operator()(const String& str);
*/

public:
	/**
     * Compares two strings lexicographically.
     * The comparison is based on the Unicode value of each character in
     * the strings. The character sequence represented by this
     * <code>String</code> object is compared lexicographically to the
     * character sequence represented by the argument string. The result is
     * a negative integer if this <code>String</code> object
     * lexicographically precedes the argument string. The result is a
     * positive integer if this <code>String</code> object lexicographically
     * follows the argument string. The result is zero if the strings
     * are equal; <code>compareTo</code> returns <code>0</code> exactly when
     * the {@link #equals(Object)} method would return <code>true</code>.
     * <p>
     * This is the definition of lexicographic ordering. If two strings are
     * different, then either they have different characters at some index
     * that is a valid index for both strings, or their lengths are different,
     * or both. If they have different characters at one or more index
     * positions, let <i>k</i> be the smallest such index; then the string
     * whose character at position <i>k</i> has the smaller value, as
     * determined by using the &lt; operator, lexicographically precedes the
     * other string. In this case, <code>compareTo</code> returns the
     * difference of the two character values at position <code>k</code> in
     * the two string -- that is, the value:
     * <blockquote><pre>
     * this.charAt(k)-anotherString.charAt(k)
     * </pre></blockquote>
     * If there is no index position at which they differ, then the shorter
     * string lexicographically precedes the longer string. In this case,
     * <code>compareTo</code> returns the difference of the lengths of the
     * strings -- that is, the value:
     * <blockquote><pre>
     * this.length()-anotherString.length()
     * </pre></blockquote>
     *
     * @param   anotherString   the <code>String</code> to be compared.
     * @return  the value <code>0</code> if the argument string is equal to
     *          this string; a value less than <code>0</code> if this string
     *          is lexicographically less than the string argument; and a
     *          value greater than <code>0</code> if this string is
     *          lexicographically greater than the string argument.
     */
	int compareTo(String* str);

	/**
     * Compares two strings lexicographically, ignoring case
     * differences. This method returns an integer whose sign is that of
     * calling <code>compareTo</code> with normalized versions of the strings
     * where case differences have been eliminated by calling
     * <code>Character.toLowerCase(Character.toUpperCase(character))</code> on
     * each character.
     * <p>
     * Note that this method does <em>not</em> take locale into account,
     * and will result in an unsatisfactory ordering for certain locales.
     * The java.text package provides <em>collators</em> to allow
     * locale-sensitive ordering.
     *
     * @param   str   the <code>String</code> to be compared.
     * @return  a negative integer, zero, or a positive integer as the
     *		specified String is greater than, equal to, or less
     *		than this String, ignoring case considerations.
     * @see     java.text.Collator#compare(String, String)
     * @since   1.2
     */
    int compareToIgnoreCase(String* str);

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
	bool equals(const String* str) const;
     bool equals(const String& str) const;

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
	bool startsWith(const String& prefix, int toffset) const;

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
	bool startsWith(const String& prefix) const;

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
	bool endsWith(const String& suffix) const;

    /**
     * Returns a hash code for this string. The hash code for a
     * <code>String</code> object is computed as
     * <blockquote><pre>
     * s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
     * </pre></blockquote>
     * using <code>int</code> arithmetic, where <code>s[i]</code> is the
     * <i>i</i>th character of the string, <code>n</code> is the length of
     * the string, and <code>^</code> indicates exponentiation.
     * (The hash value of the empty string is zero.)
     *
     * @return  a hash code value for this object.
     */
	int hashCode();

    /**
     * Returns the index within this string of the first occurrence of
     * the specified character. If a character with value
     * <code>ch</code> occurs in the character sequence represented by
     * this <code>String</code> object, then the index (in Unicode
     * code units) of the first such occurrence is returned. For
     * values of <code>ch</code> in the range from 0 to 0xFFFF
     * (inclusive), this is the smallest value <i>k</i> such that:
     * <blockquote><pre>
     * this.charAt(<i>k</i>) == ch
     * </pre></blockquote>
     * is true. For other values of <code>ch</code>, it is the
     * smallest value <i>k</i> such that:
     * <blockquote><pre>
     * this.codePointAt(<i>k</i>) == ch
     * </pre></blockquote>
     * is true. In either case, if no such character occurs in this
     * string, then <code>-1</code> is returned.
     *
     * @param   ch   a character (Unicode code point).
     * @return  the index of the first occurrence of the character in the
     *          character sequence represented by this object, or
     *          <code>-1</code> if the character does not occur.
     */
	int indexOf(wchar_u ch) const;

	/**
     * Returns the index within this string of the first occurrence of the
     * specified character, starting the search at the specified index.
     * <p>
     * If a character with value <code>ch</code> occurs in the
     * character sequence represented by this <code>String</code>
     * object at an index no smaller than <code>fromIndex</code>, then
     * the index of the first such occurrence is returned. For values
     * of <code>ch</code> in the range from 0 to 0xFFFF (inclusive),
     * this is the smallest value <i>k</i> such that:
     * <blockquote><pre>
     * (this.charAt(<i>k</i>) == ch) && (<i>k</i> &gt;= fromIndex)
     * </pre></blockquote>
     * is true. For other values of <code>ch</code>, it is the
     * smallest value <i>k</i> such that:
     * <blockquote><pre>
     * (this.codePointAt(<i>k</i>) == ch) && (<i>k</i> &gt;= fromIndex)
     * </pre></blockquote>
     * is true. In either case, if no such character occurs in this
     * string at or after position <code>fromIndex</code>, then
     * <code>-1</code> is returned.
     *
     * <p>
     * There is no restriction on the value of <code>fromIndex</code>. If it
     * is negative, it has the same effect as if it were zero: this entire
     * string may be searched. If it is greater than the length of this
     * string, it has the same effect as if it were equal to the length of
     * this string: <code>-1</code> is returned.
     *
     * <p>All indices are specified in <code>char</code> values
     * (Unicode code units).
     *
     * @param   ch          a character (Unicode code point).
     * @param   fromIndex   the index to start the search from.
     * @return  the index of the first occurrence of the character in the
     *          character sequence represented by this object that is greater
     *          than or equal to <code>fromIndex</code>, or <code>-1</code>
     *          if the character does not occur.
     */
	int indexOf(wchar_u ch, int fromIndex) const;

    /**
     * Returns the index within this string of the first occurrence of the
     * specified substring. The integer returned is the smallest value
     * <i>k</i> such that:
     * <blockquote><pre>
     * this.startsWith(str, <i>k</i>)
     * </pre></blockquote>
     * is <code>true</code>.
     *
     * @param   str   any string.
     * @return  if the string argument occurs as a substring within this
     *          object, then the index of the first character of the first
     *          such substring is returned; if it does not occur as a
     *          substring, <code>-1</code> is returned.
     */	
	int indexOf(String* str) const;

    /**
     * Returns the index within this string of the first occurrence of the
     * specified substring, starting at the specified index.  The integer
     * returned is the smallest value <tt>k</tt> for which:
     * <blockquote><pre>
     *     k &gt;= Math.min(fromIndex, str.length()) && this.startsWith(str, k)
     * </pre></blockquote>
     * If no such value of <i>k</i> exists, then -1 is returned.
     *
     * @param   str         the substring for which to search.
     * @param   fromIndex   the index from which to start the search.
     * @return  the index within this string of the first occurrence of the
     *          specified substring, starting at the specified index.
     */	
	int indexOf(String* str, int fromIndex) const;

    /**
     * Returns the index within this string of the last occurrence of
     * the specified character. For values of <code>ch</code> in the
     * range from 0 to 0xFFFF (inclusive), the index (in Unicode code
     * units) returned is the largest value <i>k</i> such that:
     * <blockquote><pre>
     * this.charAt(<i>k</i>) == ch
     * </pre></blockquote>
     * is true. For other values of <code>ch</code>, it is the
     * largest value <i>k</i> such that:
     * <blockquote><pre>
     * this.codePointAt(<i>k</i>) == ch
     * </pre></blockquote>
     * is true.  In either case, if no such character occurs in this
     * string, then <code>-1</code> is returned.  The
     * <code>String</code> is searched backwards starting at the last
     * character.
     *
     * @param   ch   a character (Unicode code point).
     * @return  the index of the last occurrence of the character in the
     *          character sequence represented by this object, or
     *          <code>-1</code> if the character does not occur.
     */
	int lastIndexOf(wchar_u ch);

    /**
     * Returns the index within this string of the last occurrence of
     * the specified character, searching backward starting at the
     * specified index. For values of <code>ch</code> in the range
     * from 0 to 0xFFFF (inclusive), the index returned is the largest
     * value <i>k</i> such that:
     * <blockquote><pre>
     * (this.charAt(<i>k</i>) == ch) && (<i>k</i> &lt;= fromIndex)
     * </pre></blockquote>
     * is true. For other values of <code>ch</code>, it is the
     * largest value <i>k</i> such that:
     * <blockquote><pre>
     * (this.codePointAt(<i>k</i>) == ch) && (<i>k</i> &lt;= fromIndex)
     * </pre></blockquote>
     * is true. In either case, if no such character occurs in this
     * string at or before position <code>fromIndex</code>, then
     * <code>-1</code> is returned.
     *
     * <p>All indices are specified in <code>char</code> values
     * (Unicode code units).
     *
     * @param   ch          a character (Unicode code point).
     * @param   fromIndex   the index to start the search from. There is no
     *          restriction on the value of <code>fromIndex</code>. If it is
     *          greater than or equal to the length of this string, it has
     *          the same effect as if it were equal to one less than the
     *          length of this string: this entire string may be searched.
     *          If it is negative, it has the same effect as if it were -1:
     *          -1 is returned.
     * @return  the index of the last occurrence of the character in the
     *          character sequence represented by this object that is less
     *          than or equal to <code>fromIndex</code>, or <code>-1</code>
     *          if the character does not occur before that point.
     */	
	int lastIndexOf(wchar_u ch, int fromIndex);

    /**
     * Returns the index within this string of the rightmost occurrence
     * of the specified substring.  The rightmost empty string "" is
     * considered to occur at the index value <code>this.length()</code>.
     * The returned index is the largest value <i>k</i> such that
     * <blockquote><pre>
     * this.startsWith(str, k)
     * </pre></blockquote>
     * is true.
     *
     * @param   str   the substring to search for.
     * @return  if the string argument occurs one or more times as a substring
     *          within this object, then the index of the first character of
     *          the last such substring is returned. If it does not occur as
     *          a substring, <code>-1</code> is returned.
     */	
	int lastIndexOf(const String& str) const;


    /**
     * Returns the index within this string of the last occurrence of the
     * specified substring, searching backward starting at the specified index.
     * The integer returned is the largest value <i>k</i> such that:
     * <blockquote><pre>
     *     k &lt;= Math.min(fromIndex, str.length()) && this.startsWith(str, k)
     * </pre></blockquote>
     * If no such value of <i>k</i> exists, then -1 is returned.
     * 
     * @param   str         the substring to search for.
     * @param   fromIndex   the index to start the search from.
     * @return  the index within this string of the last occurrence of the
     *          specified substring.
     */	
	int lastIndexOf(const String& str, int fromIndex) const;
    
    /**
     * Returns a new string that is a substring of this string. The
     * substring begins with the character at the specified index and
     * extends to the end of this string. <p>
     * Examples:
     * <blockquote><pre>
     * "unhappy".substring(2) returns "happy"
     * "Harbison".substring(3) returns "bison"
     * "emptiness".substring(9) returns "" (an empty string)
     * </pre></blockquote>
     *
     * @param      beginIndex   the beginning index, inclusive.
     * @return     the specified substring.
     * @exception  IndexOutOfBoundsException  if
     *             <code>beginIndex</code> is negative or larger than the
     *             length of this <code>String</code> object.
     */
	String* substring(int beginIndex) const;

    /**
     * Returns a new string that is a substring of this string. The
     * substring begins at the specified <code>beginIndex</code> and
     * extends to the character at index <code>endIndex - 1</code>.
     * Thus the length of the substring is <code>endIndex-beginIndex</code>.
     * <p>
     * Examples:
     * <blockquote><pre>
     * "hamburger".substring(4, 8) returns "urge"
     * "smiles".substring(1, 5) returns "mile"
     * </pre></blockquote>
     *
     * @param      beginIndex   the beginning index, inclusive.
     * @param      endIndex     the ending index, exclusive.
     * @return     the specified substring.
     * @exception  IndexOutOfBoundsException  if the
     *             <code>beginIndex</code> is negative, or
     *             <code>endIndex</code> is larger than the length of
     *             this <code>String</code> object, or
     *             <code>beginIndex</code> is larger than
     *             <code>endIndex</code>.
     */	
	String* substring(int beginIndex, int endIndex) const;

    /**
     * Concatenates the specified string to the end of this string.
     * <p>
     * If the length of the argument string is <code>0</code>, then this
     * <code>String</code> object is returned. Otherwise, a new
     * <code>String</code> object is created, representing a character
     * sequence that is the concatenation of the character sequence
     * represented by this <code>String</code> object and the character
     * sequence represented by the argument string.<p>
     * Examples:
     * <blockquote><pre>
     * "cares".concat("s") returns "caress"
     * "to".concat("get").concat("her") returns "together"
     * </pre></blockquote>
     *
     * @param   str   the <code>String</code> that is concatenated to the end
     *                of this <code>String</code>.
     * @return  a string that represents the concatenation of this object's
     *          characters followed by the string argument's characters.
     */   
	String* concat(const String& str) const;

public: // Implements Interface CharSequence

    /**
     * Returns the length of this string.
     * The length is equal to the number of 16-bit
     * Unicode characters in the string.
     *
     * @return  the length of the sequence of characters represented by this
     *          object.
     */
	virtual int length() const;

    /**
     * Returns the <code>char</code> value at the
     * specified index. An index ranges from <code>0</code> to
     * <code>length() - 1</code>. The first <code>char</code> value of the sequence
     * is at index <code>0</code>, the next at index <code>1</code>,
     * and so on, as for array indexing.
     *
     * <p>If the <code>char</code> value specified by the index is a
     * <a href="Character.html#unicode">surrogate</a>, the surrogate
     * value is returned.
     *
     * @param      index   the index of the <code>char</code> value.
     * @return     the <code>char</code> value at the specified index of this string.
     *             The first <code>char</code> value is at index <code>0</code>.
     * @exception  IndexOutOfBoundsException  if the <code>index</code>
     *             argument is negative or not less than the length of this
     *             string.
     */	
	virtual wchar_u charAt(int index) const;
	virtual CharSequence* subSequence(int start, int end) const;
	virtual String* toString() const;

public: 
	const wchar_u* toChars() const;
     const Array<wchar_u> toCharArray() const;
     void getChars(int srcBegin, int srcEnd, wchar_u* dst, int dstBegin) const;
     
     const Array<byte> getBytes() const;
     const Array<byte> getBytes(const char* charset) const;
     const Array<byte> getBytes(const String& charset) const;

     const Array<char> toUTF8CharArray() const;

     char* toUTF8String() const;
     char* toCString() const; 
     wchar_t* toWCHARString() const;

     bool matches(const String& regex) const;
	bool matches(String* regex) const;
	bool contains(CharSequence* s) const;
     bool contains(const String& s) const;

	String* replace(wchar_u oldChar, wchar_u newChar);
	String* replace(CharSequence* target, CharSequence* replacement);
	String* replaceAll(String* regex, String* replacement);
     String* replaceAll(const String& regex, const String& replacement);
     String* replaceFirst(String* regex, String* replacement);

     Array<String*> split(const String& regex) const;
	Array<String*> split(const String* regex) const;
     Array<String*> split(const String* regex, int limit) const;

	String* toLowerCase();
	String* toUpperCase();
	String* trim();

public:
	static String* copyValueOf(const wchar_u* data, int offset, int count);
	static String* copyValueOf(const wchar_u* data);

     static String* vformat(String* format, va_list arg);
	static String* format(String* format, ...);

     static String* vformat(const char* format, va_list arg);
	static String* format(const char* format, ...);

     static String* vformat(const wchar_t* format, va_list arg);
	static String* format(const wchar_t* format, ...);

    /**
     * Returns the string representation of a specific subarray of the
     * <code>wchar_u</code> array argument.
     * <p>
     * The <code>offset</code> argument is the index of the first
     * wchar_uacter of the subarray. The <code>count</code> argument
     * specifies the length of the subarray. The contents of the subarray
     * are copied; subsequent modification of the wchar_uacter array does not
     * affect the newly created string.
     *
     * @param   data     the wchar_uacter array.
     * @param   offset   the initial offset into the value of the
     *                  <code>String</code>.
     * @param   count    the length of the value of the <code>String</code>.
     * @return  a string representing the sequence of wchar_uacters contained 
     *          in the subarray of the wchar_uacter array argument.
     * @exception IndexOutOfBoundsException if <code>offset</code> is
     *          negative, or <code>count</code> is negative, or
     *          <code>offset+count</code> is larger than
     *          <code>data.length</code>.
     */
	static String* valueOf(const wchar_u* data, int offset, int count);
	static String* valueOf(const wchar_u* data);
	static String* valueOf(const char* value);
	static String* valueOf(const wchar_t* value);

	/**
     * Returns the string representation of the <code>bool</code> argument.
     *
     * @param   b   a <code>bool</code>.
     * @return  if the argument is <code>dg_true</code>, a string equal to
     *          <code>"dg_true"</code> is returned; otherwise, a string equal to
     *          <code>"dg_false"</code> is returned.
     */
	static String* valueOf(bool b);

	/**
     * Returns the string representation of the <code>wchar_u</code>
     * argument.
     *
     * @param   c   a <code>wchar_u</code>.
     * @return  a string of length <code>1</code> containing
     *          as its single wchar_uacter the argument <code>c</code>.
     */
	static String* valueOf(wchar_u c);

    /**
     * Returns the string representation of the <code>int</code> argument.
     * <p>
     * The representation is exactly the one returned by the
     * <code>Integer.toString</code> method of one argument.
     *
     * @param   i   an <code>int</code>.
     * @return  a string representation of the <code>int</code> argument.
     * @see     java.lang.Integer#toString(int, int)
     */
	static String* valueOf(int i);
	static String* valueOf(dg_long l);
	static String* valueOf(dg_float f);
	static String* valueOf(dg_double d);

private:
	wchar_u* value;
	int offset;
	int count;
};

// suport compare and hash
inline wostream& operator << (wostream& os,const String& str) {
     String* theStr = const_cast<String*>(&str);
     Array<byte> bytes = theStr->getBytes();
     os << bytes.raw();
     return os;
}

inline wostream& operator << (wostream& os, const String* str) {
     String* theStr = const_cast<String*>(str);
     Array<byte> bytes = theStr->getBytes();
     os << bytes.raw();
     return os;
}

inline bool operator<(const String& left, const String& right) {
     String* theStr = const_cast<String*>(&left);
     String* otherStr = const_cast<String*>(&right);
	return theStr->compareTo(otherStr) > 0;
}

inline size_t hash_value(const String& str) {
     String* theStr = const_cast<String*>(&str);
	return theStr->hashCode();
}

inline const char* operator+(const String& left, const String& right) {
     String* theStr = const_cast<String*>(&left);
     String* otherStr = const_cast<String*>(&right);

     String* retStr = theStr->concat(otherStr);
     const char* utf8Str = retStr->toUTF8String();
     SafeRelease(retStr);

     return utf8Str;
}

EndPackage2//(dragon, lang)

#endif//String_Lang_Dragon_H
