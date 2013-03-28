#include "lang.h"

#ifndef Lang_NumberFormatException_H
#define Lang_NumberFormatException_H
#pragma once

#include "IllegalArgumentException.h"

BeginPackage2(ProjectName,lang)

class _DragonExport NumberFormatException :public IllegalArgumentException, public Object
{
public:
	NumberFormatException();
	NumberFormatException(String& message);
};

EndPackage2

#endif