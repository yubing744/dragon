#include "lang.h"

#ifndef Lang_IllegalArgumentException_H
#define Lang_IllegalArgumentException_H
#pragma once

#include "RuntimeException.h"

BeginPackage2(ProjectName,lang)

class _DragonExport IllegalArgumentException :public RuntimeException
{
public:
	IllegalArgumentException();
	IllegalArgumentException(String& message);
};

EndPackage2

#endif