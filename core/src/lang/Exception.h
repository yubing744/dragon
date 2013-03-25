#include "lang.h"

#if !defined(Lang_Exception_H)
#define Lang_Exception_H
#pragma once

#include "Throwable.h"

BeginPackage2(ProjectName,lang)

class _DragonExport Exception :public Throwable
{
public:
	Exception();
	Exception(String& message);
	Exception(Throwable* cause);
	Exception(String& message, Throwable* cause);
};

EndPackage2

#endif