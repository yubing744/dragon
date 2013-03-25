#include "lang.h"
#include "stdarg.h"


#if !defined(Lang_String_H)
#define Lang_String_H
#pragma once

#include "IndexOutOfBoundsException.h"
#include "NullPointerException.h"
#include "Math.h"

#define vstprintf_s vswprintf_s
#define _ltot_s _ltow_s

BeginPackage2(ProjectName,lang)

typedef wstring TString;
typedef wostream tostream;

class _DragonExport String:public Object,public Comparable<String>,public CharSequence
{
	friend tostream& operator << (tostream& os,const String& str);
	friend tostream& operator << (tostream& os,String* str);
	friend size_t hash_value(const String& str);
	friend bool operator<(const String& left,const String& right);

public:
	String();
	String(TString value);
	String(const String& value);
	String(const Char* value);
	String(const Char* value, int offset, int count) throw(IndexOutOfBoundsException);
	~String();

public:
	void operator = (const Char*  str);
	void operator = (TString  str);

	String& operator+ (const String& str);
	String& operator+=(const String& str);
	bool operator==(const Char* str);
	bool operator==(const String& str);

	operator TString();
	operator const Char*();
	operator size_t();

	size_t operator()(const String& str);

public:
	int compareTo(String& o);
	bool equals(const Char* str);
	bool startsWith(const Char* prefix);
	bool startsWith(const Char* prefix,int toffset);
	bool endsWith(String& suffix);
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

	bool matches(String regex);
	bool contains(CharSequence* s) throw(NullPointerException);
	bool contains(String s); 
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

	char* toMultiByte();

public:
	static String valueOf(const Char* data);
	static String valueOf(const Char* data,int offset,int count);
	static String& copyValueOf(const Char* data);
	static String& copyValueOf(const Char* data,int offset,int count);

	static String format(String& format,...);
	static String format(const Char* format,...);
	static String format(const char* format,...);

	static String valueOf(bool b);
	static String valueOf(Char c);
	static String valueOf(const char* value);
	static String valueOf(int i);
	static String valueOf(long l);
	static String valueOf(float f);
	static String valueOf(double d);


private:
	TString mstr;

};

inline tostream& operator << (tostream& os,const String& str)
{
    os<<str.mstr;
    return os;
}

inline tostream& operator << (tostream& os,String* str)
{
    os<<str->mstr;
    return os;
}

inline bool operator<(const String& left,const String& right)
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

EndPackage2

#endif