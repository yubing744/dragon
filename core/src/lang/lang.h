#ifndef Lang_H
#define Lang_H

#include "../config/config.h"

BeginPackage2(ProjectName,lang)

	//basic type
	typedef bool Boolean;
	typedef unsigned char Byte;
	typedef wchar_t Char;
	typedef short Short;
	typedef int Integer;
	typedef long long Long;
	typedef float Float;
	typedef double Double;



	template<class Type>
	class Class;

	template<class Type>
	class Array;

	template<class T>
	interface Comparable;



	interface CharSequence;
	interface Throwable;
	interface Runnable;

	class Object;
	class String;
	class Math;
	class Exception;
	class System;
	class NullPointerException;
	class IndexOutOfBoundsException;
	class SecurityException;
	class ClassNotFoundException;
	class NoSuchMethodException;
	class UnsupportedOperationException;
	class IllegalArgumentException;
	class NumberFormatException;
	class Number;
	class Thread;

EndPackage2


#include "gc/gc.h"
#include "../util/regex/regex.h"

Import ProjectName::lang::gc;
Import ProjectName::util::regex;

#include "Object.h"

#include "Throwable.h"
#include "Exception.h"
#include "NullPointerException.h"
#include "IndexOutOfBoundsException.h"
#include "SecurityException.h"
#include "ClassNotFoundException.h"
#include "NoSuchMethodException.h"
#include "UnsupportedOperationException.h"
#include "IllegalArgumentException.h"
#include "NumberFormatException.h"

#include "System.h"
#include "Comparable.h"
#include "CharSequence.h"
#include "String.h"
#include "Class.h"
#include "Array.h"
#include "Math.h"
#include "Number.h"
#include "Runnable.h"
#include "Thread.h"
#include "HelpFunc.h"

#endif