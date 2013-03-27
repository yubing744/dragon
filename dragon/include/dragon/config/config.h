// Copyright 2013 the Dragon project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef DRAGON_CONFIG_H_
#define DRAGON_CONFIG_H_

 
#if !defined(_UNICODE)
    #define _UNICODE
#endif
#if !defined(UNICODE)
    #define UNICODE
#endif

#ifdef _WIN32
#pragma warning (disable:4290)
#pragma warning (disable:4584)
#pragma warning (disable:4482)
#endif

#undef _HAS_ITERATOR_DEBUGGING
#define _HAS_ITERATOR_DEBUGGING 0

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <string>
#include <iostream>

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

#define Import using namespace
#define import using namespace

#define SafeRelease(pObject) if(pObject != NULL) {pObject->Release(); pObject=NULL;}
#define SafeDelete(pObject)  if(pObject != NULL) {delete pObject; pObject=NULL;}

#undef interface
#undef __RPCNDR_H__

#ifndef _WIN32
#	define interface struct
#else
#	define interface class __declspec(novtable)
#endif

//#define DRAGON_STATIC_LIB
//#define MEM_CHECK
//#define OPEN_LOG


/*
#if defined( DRAGON_STATIC_LIB )
# 	define _DragonExport
#  	define _DragonPrivate
#else
#   if defined( DRAGON_HEADER_BUILD )
#       if defined( __MINGW32__ )
#           define _DragonExport
#       else
#       	define _DragonExport __declspec( dllimport )
#       endif
#   else
#      	define _DragonExport __declspec( dllexport )
#   endif
#   define _DragonPrivate
#endif
*/
#define _DragonExport
#define _DragonPrivate


#ifdef WIN32
#    define Export __declspec(dllexport)
#    define ExportClass class Export
#    define ExportInterface interface Export
#endif

#define null 0
#define final const 
#define extends :
#define implements ,

#define publicc public:
#define protectedc protected:
#define privatec private:

#define publicm public:
#define protectedm protected:
#define privatem private:

#define publicf public: virtual
#define protectedf protected: virtual
#define privatef private: virtual



#ifdef OPEN_LOG
#	define Log(format,...) \
		printf(format,__VA_ARGS__)
#else
#	define Log(format,...)
#endif


Import std;

#endif
