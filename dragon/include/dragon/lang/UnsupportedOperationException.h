#include "lang.h"

#ifndef Lang_UnsupportedOperationException_H
#define Lang_UnsupportedOperationException_H
#pragma once

#include "RuntimeException.h"

BeginPackage2(dragon,lang)

class _DragonExport UnsupportedOperationException :public RuntimeException
{
public:
	UnsupportedOperationException();
	UnsupportedOperationException(String& message);
};

EndPackage2

#endif