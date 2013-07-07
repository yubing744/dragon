#include "lang.h"

#if !defined(Lang_SecurityException_H)
#define Lang_SecurityException_H
#pragma once

BeginPackage2(dragon,lang)

class _DragonExport SecurityException :public RuntimeException
{
public:
	SecurityException();
	SecurityException(Char* message);
};

EndPackage2

#endif