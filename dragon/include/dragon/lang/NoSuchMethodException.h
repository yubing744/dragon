#include "lang.h"

#ifndef Lang_NoSuchMethodException_H
#define Lang_NoSuchMethodException_H
#pragma once

#include "Exception.h"

BeginPackage2(dragon,lang)

class _DragonExport NoSuchMethodException :public Exception
{
public:
	NoSuchMethodException();
	NoSuchMethodException(String& message);
};

EndPackage2

#endif