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
#define EndPackage5							       }}}}}

#define BeginPackage6(name1,name2,name3,name4,name5,name6) namespace name1{namespace name2{namespace name3{namespace name4{namespace name5{namespace name6{
#define EndPackage6							            }}}}}}

#define BeginPackage7(name1,name2,name3,name4,name5,name6,name7) namespace name1{namespace name2{namespace name3{namespace name4{namespace name5{namespace name6{namespace name7{
#define EndPackage7							                }}}}}}}

#define BeginPackage8(name1,name2,name3,name4,name5,name6,name7,name8) namespace name1{namespace name2{namespace name3{namespace name4{namespace name5{namespace name6{namespace name7{namespace name8{
#define EndPackage8							                    }}}}}}}

// Define import
#define Import using namespace

// Safe Delete
#define SafeDelete(pObject) if(pObject != null) {delete pObject; pObject = null;}
#define SafeDeleteArray(pArray) if(pArray != null) {delete[] pArray; pArray = null;}

// Safe Free
#define SafeFree(pMem) if(pMem != null) {free(pMem); pMem = null;}

// Safe Retain and Release
#define SafeRetain(pRef) { Object* pObject = dynamic_cast<Object*>(pRef); if (pObject != null) {pObject->retain();} }
#define SafeRelease(pRef) { Object* pObject = dynamic_cast<Object*>(pRef); if(pObject != null) {if (pObject->getRefCount() == 0) {pObject->release(); pRef = null;} else {pObject->release(); } }}
#define SafeReplace(pRef1, pRef2) { SafeRelease(pRef1); SafeRetain(pRef2); pRef1 = pRef2; } 

//#define DRAGON_STATIC_LIB
//#define MEM_CHECK

// Log switch
#define ENABLE_LOG         1 // enable log
#define ENABLE_LOG_LEVEL   5 // only show error

// Assert
#ifdef NDEBUG 
	#define ASSERT
#else
 	#include <assert.h>
	#define ASSERT assert
#endif

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

	#ifndef DRAGONEXPORT	  
		#ifdef BUILDING_DRAGON_SHARED
			#define DRAGONEXPORT __declspec(dllexport)
		#endif
    #endif

    #ifndef DRAGONEXPORT
		#ifdef USING_DRAGON_SHARED
			#define DRAGONEXPORT __declspec(dllimport)
		#endif  // BUILDING_DRAGON_SHARED
    #endif 

    #ifndef DRAGONEXPORT
		  #define DRAGONEXPORT
    #endif
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

// Define Extends
#undef extends
#define extends(super_class) :public super_class	

// Define Implements
#undef implements
#define implements(interface_class) :public interface_class
#define implements1(interface_class1) ,public interface_class1
#define implements2(interface_class1, interface_class2) ,public interface_class1, \
	public interface_class2
#define implements3(interface_class1, interface_class2, interface_class3) ,public interface_class1, \
	public interface_class2, public interface_class3
#define implements4(interface_class1, interface_class2, interface_class3, interface_class4) ,\
	public interface_class1, public interface_class2, public interface_class3, public interface_class4
#define implements5(interface_class1, interface_class2, interface_class3, interface_class4, interface_class5) ,\
	public interface_class1, public interface_class2, public interface_class3, public interface_class4, \
	public interface_class5

// Define interface
#undef interface
#undef __RPCNDR_H__

#ifndef interface
	#ifdef _WIN32
		#define __interface class __declspec(novtable)
		#define DRAGON_INTERFACE class __declspec(novtable)
		#define interface class __declspec(novtable)
	#else
		#define __interface struct
		#define interface struct
	#endif
#endif


// Define dragon class
#define DragonClass class _DragonExport
#define DragonInterface __interface _DragonExport
#define class_ DragonClass
#define interface_ DragonInterface

// Define inline
#if defined(__GNUC__) && !defined(DEBUG)
	#define DRAGON_INLINE(declarator) inline __attribute__((always_inline)) declarator
#elif defined(_MSC_VER) && !defined(DEBUG)
	#define DRAGON_INLINE(declarator) __forceinline declarator
#else
	#define DRAGON_INLINE(declarator) inline declarator
#endif

// Define stdcall
#if defined(__GNUC__)
	#define DRAGON_STDCALL __attribute__((stdcall))
#else
	#define DRAGON_STDCALL __stdcall
#endif

// Define thiscall
#if defined(__GNUC__)
	#define DRAGON_THISCALL __attribute__((thiscall))
#else
	#define DRAGON_THISCALL __thiscall
#endif

// Define deprecated
#if defined(__GNUC__) && !DRAGON_DISABLE_DEPRECATIONS
	#define DRAGON_DEPRECATED(declarator) declarator __attribute__ ((deprecated))
#elif defined(_MSC_VER) && !DRAGON_DISABLE_DEPRECATIONS
	#define DRAGON_DEPRECATED(declarator) __declspec(deprecated) declarator
#else
	#define DRAGON_DEPRECATED(declarator) declarator
#endif

// Define volatile
#ifndef _WIN32
	#define DRAGON_ATOMICS_VOLATILE 
#else
	#define DRAGON_ATOMICS_VOLATILE volatile
#endif

// Byte Align
#if _WIN32
  /** This can be placed before a stack or member variable declaration to tell the compiler
      to align it to the specified number of bytes. */
  #define DRAGON_ALIGN(bytes)   __declspec (align (bytes))
#else
  #define DRAGON_ALIGN(bytes)   __attribute__ ((aligned (bytes)))
#endif

// Define native
#define native 

// Define null
#undef null	
#define null 0

// Enable Unicode
#define _UNICODE 1

// Config Log
#ifdef ENABLE_LOG
#	define Log(format,...) printf(format, __VA_ARGS__)
#else
#	define Log(format,...)
#endif

// depressed some warnings 
#ifdef _WIN32
	#pragma warning (disable:4290)
	#pragma warning (disable:4584)
	#pragma warning (disable:4482)
#endif //_WIN32


#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
    typedef unsigned __int32 uint32_t;
    typedef unsigned __int16 uint16_t;
    typedef unsigned __int8 uint8_t;
    typedef __int32 int32_t;
#elif defined(__GNUC__) || defined(__CYGWIN__) || defined(__MWERKS__) || defined(__WATCOMC__) || defined(__PGI) || defined(__LCC__)
    #include <stdint.h>
#else
    typedef unsigned int uint32_t;
    typedef unsigned short int uint16_t;
    typedef unsigned char uint8_t;
    typedef int int32_t;
#endif

// dragon basic types
#ifdef HAVE_INTTYPES_H
	#include <inttypes.h>       /* C99 */
	typedef bool                dg_boolean;       /* unsigned 8 bits */
	typedef char                dg_byte;          /* signed 8 bits */
	typedef int16_t             dg_short;         /* signed 16 bits */
	typedef uint32_t            dg_char;          /* unsigned 32 bits */
	typedef int32_t             dg_int;           /* signed 32 bits */
	typedef int64_t             dg_long;          /* signed 64 bits */
	typedef float               dg_float;         /* 32-bit IEEE 754 */
	typedef double              dg_double;        /* 64-bit IEEE 754 */

	typedef uint16_t            dg_ushort;
	typedef uint32_t            dg_uint;
	typedef uint64_t            dg_ulong;
#else
	typedef bool                dg_boolean;       /* unsigned 8 bits */
	typedef char                dg_byte;          /* signed 8 bits */
	typedef short               dg_short;         /* signed 16 bits */
	typedef unsigned int        dg_char;          /* unsigned 32 bits */
	typedef int                 dg_int;           /* signed 32 bits */
	typedef long long           dg_long;          /* signed 64 bits */
	typedef float               dg_float;         /* 32-bit IEEE 754 */
	typedef double              dg_double;        /* 64-bit IEEE 754 */

	typedef unsigned short      dg_ushort;
	typedef unsigned int        dg_uint;
	typedef unsigned long long  dg_ulong;
#endif

// simple type
typedef dg_byte wbyte_u;
typedef dg_char wchar_u;
typedef dg_long wlong_u;	

typedef dg_char char_u;
typedef dg_long long_u;
typedef dg_int int_u;

//#ifndef _WIN32
//	typedef dg_byte byte;
//#endif
typedef dg_byte byte;

#ifdef _WIN32
	#undef max
	#undef min
#endif

// NULL char
#define NULL_CHAR (dg_char)null;

// boolean value
#define dg_true true
#define dg_false false

#endif // Config_Dragon_H
