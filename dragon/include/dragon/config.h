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
 * File:        config.h
 * Description: base config for all other classes
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/03/31
 **********************************************************************/

#ifndef Config_Dragon_H
#define Config_Dragon_H

// Define BeginPackage and EndPackage
#define BeginPackage1(name1) namespace name1{
#define EndPackage1		     }

#define BeginPackage2(name1,name2)  namespace name1{namespace name2{
#define EndPackage2			        }}

#define BeginPackage3(name1,name2,name3)  namespace name1{namespace name2{namespace name3{
#define EndPackage3						  }}}

#define BeginPackage4(name1,name2,name3,name4) namespace name1{namespace name2{namespace name3{namespace name4{
#define EndPackage4							   }}}}

#define BeginPackage5(name1,name2,name3,name4,name5) namespace name1{namespace name2{namespace name3{namespace name4{namespace name5{
#define EndPackage5							   }}}}}

#define BeginPackage6(name1,name2,name3,name4,name5,name6) namespace name1{namespace name2{namespace name3{namespace name4{namespace name5{namespace name6{
#define EndPackage6							   }}}}}}

// Define import
#define Import using namespace


// Define release
#define SafeRelease(pObject) if(pObject != NULL) {pObject->Release(); pObject=NULL;}
#define SafeDelete(pObject)  if(pObject != NULL) {delete pObject; pObject=NULL;}
#define SafeDeleteArray(pArray) if(pArray != NULL) {delete[] pArray; pArray=NULL;}


//#define DRAGON_STATIC_LIB
//#define MEM_CHECK
//#define ENABLE_LOG


// Define export
#ifdef _WIN32

	// Setup for Windows DLL export/import. When building the DRAGON DLL the
	// BUILDING_DRAGON_SHARED needs to be defined. When building a program which uses
	// the DRAGON DLL USING_DRAGON_SHARED needs to be defined. When either building the DRAGON
	// static library or building a program which uses the DRAGON static library neither
	// BUILDING_DRAGON_SHARED nor USING_DRAGON_SHARED should be defined.
	#if defined(BUILDING_DRAGON_SHARED) && defined(USING_DRAGON_SHARED)
		#error both BUILDING_DRAGON_SHARED and USING_DRAGON_SHARED are set - please check the\
		  build configuration to ensure that at most one of these is set
	#endif

	#ifdef BUILDING_DRAGON_SHARED
		#define DRAGONEXPORT __declspec(dllexport)
	#elif USING_DRAGON_SHARED
		#define DRAGONEXPORT __declspec(dllimport)
	#else
		#define DRAGONEXPORT
	#endif  // BUILDING_DRAGON_SHARED

#else  // _WIN32

	// Setup for Linux shared library export.
	#if defined(__GNUC__) && ((__GNUC__ >= 4) || \
		(__GNUC__ == 3 && __GNUC_MINOR__ >= 3)) && defined(DRAGON_SHARED)
		#ifdef BUILDING_DRAGON_SHARED
			#define DRAGONEXPORT __attribute__ ((visibility("default")))
		#else
			#define DRAGONEXPORT
		#endif
	#else
		#define DRAGONEXPORT
	#endif

#endif

#define _DragonExport DRAGONEXPORT


// Define interface
#undef interface
#undef __RPCNDR_H__

#ifndef _WIN32
	#define interface struct
#else
	#ifndef interface
		#define interface class __declspec(novtable)
	#endif
#endif


// Define Extends
#undef extends
#define extends(super_class) :public super_class	


// Define Implements
#undef implements
#define implements(interface_class) :public interface_class


// Define inline
#if defined(__GNUC__) && !defined(DEBUG)
	#define DRAGON_INLINE(declarator) inline __attribute__((always_inline)) declarator
#elif defined(_MSC_VER) && !defined(DEBUG)
	#define DRAGON_INLINE(declarator) __forceinline declarator
#else
	#define DRAGON_INLINE(declarator) inline declarator
#endif

// Define deprecated
#if defined(__GNUC__) && !DRAGON_DISABLE_DEPRECATIONS
	#define DRAGON_DEPRECATED(declarator) declarator __attribute__ ((deprecated))
#elif defined(_MSC_VER) && !DRAGON_DISABLE_DEPRECATIONS
	#define DRAGON_DEPRECATED(declarator) __declspec(deprecated) declarator
#else
	#define DRAGON_DEPRECATED(declarator) declarator
#endif


// Define null
#define null 0

// Enable Unicode
#define _UNICODE 1

// Config Log
#ifdef ENABLE_LOG
#	define Log(format,...) \
		printf(format,__VA_ARGS__)
#else
#	define Log(format,...)
#endif

// depressed some warnings 
#ifdef _WIN32
	#pragma warning (disable:4290)
	#pragma warning (disable:4584)
	#pragma warning (disable:4482)
#endif // _WIN32


// dragon basic types
typedef unsigned char dg_byte;
typedef short dg_short;
typedef int dg_int;
typedef long long dg_long;
typedef float dg_float;
typedef double dg_double;

typedef unsigned int dg_char;
typedef bool dg_boolean;

// NULL char
#define NULL_CHAR (dg_char)NULL

// boolean value
#define dg_true true
#define dg_false false

#endif // Config_Dragon_H
