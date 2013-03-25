#include "lang.h"
#include "RuntimeException.h"

#if !defined(Lang_NullPointerException_H)
#define Lang_NullPointerException_H
#pragma once

BeginPackage2(ProjectName,lang)

class _DragonExport NullPointerException :public RuntimeException
{
public:
	NullPointerException();
	NullPointerException(const Char* message);
public:
	Class<Object>* getClass();
};

EndPackage2

#endif