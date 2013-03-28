#include "lang.h"

#if !defined(Lang_IndexOutOfBoundsException_H)
#define Lang_IndexOutOfBoundsException_H
#pragma once

#include "RuntimeException.h"

BeginPackage2(ProjectName,lang)

class _DragonExport IndexOutOfBoundsException :public RuntimeException
{
public: 
	IndexOutOfBoundsException();
	IndexOutOfBoundsException(const Char* message);

};

EndPackage2

#endif