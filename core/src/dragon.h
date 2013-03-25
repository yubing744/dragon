#ifndef Dragon_H
#define Dragon_H
#pragma once

#define DRAGON_HEADER_BUILD
//#define MEM_CHECK

#include "util/regex/regex.h"
#include "lang/gc/gc.h"
#include "lang/reflect/reflect.h"
#include "lang/lang.h"
#include "io/io.h"
#include "util/util.h"
#include "xml/xml.h"
#include "util/zip/zip.h"


#ifdef DRAGON_STATIC_LIB
#	pragma comment(lib,"Dragon_S.lib") 
#elif !defined NDEBUG
#	pragma comment(lib,"Dragon_D.lib")
#else
#	pragma comment(lib,"Dragon.lib")
#endif

Import dragon::lang::gc;
Import dragon::lang::reflect;
Import dragon::lang;
Import dragon::io;
Import dragon::util;
Import dragon::xml;
Import dragon::util::zip;

#endif