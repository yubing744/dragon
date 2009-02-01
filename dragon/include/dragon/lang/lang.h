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

#ifndef Lang_Dragon_H
#define Lang_Dragon_H

#include <dragon/config.h>
#include "basic_type.h"

BeginPackage2(dragon,lang)

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

#include <dragon/lang/gc/gc.h>
#include <dragon/util/regex/regex.h>

Import dragon::lang::gc;
Import dragon::util::regex;

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

#include "help_func.h"

#endif