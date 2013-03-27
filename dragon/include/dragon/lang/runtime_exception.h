#include "lang.h"

#if !defined(Lang_RuntimeException_H)
#define Lang_RuntimeException_H
#pragma once

#include "Exception.h"

BeginPackage2(ProjectName,lang)

class _DragonExport RuntimeException :public Exception
{
public:
	RuntimeException();
	RuntimeException(String& message);
	RuntimeException(Throwable* cause);
	RuntimeException(String& message, Throwable* cause);
};

EndPackage2

#endif