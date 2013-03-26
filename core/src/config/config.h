#if !defined(DRAGON_CONFIG)
#define DRAGON_CONFIG

 
#if !defined(_UNICODE)
	#define _UNICODE
#endif
#if !defined(UNICODE)
	#define UNICODE
#endif

#define ProjectName dragon
#pragma warning (disable:4290)
#pragma warning (disable:4584)
#pragma warning (disable:4482)

#undef _HAS_ITERATOR_DEBUGGING
#define _HAS_ITERATOR_DEBUGGING 0

#ifdef WIN32
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
