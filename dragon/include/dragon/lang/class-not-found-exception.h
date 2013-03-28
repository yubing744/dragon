#include "lang.h"

#ifndef Lang_ClassNotFoundException_H
#define Lang_ClassNotFoundException_H
#pragma once

#include "Exception.h"

BeginPackage2(ProjectName,lang)

class _DragonExport ClassNotFoundException :public Exception
{
public:
	ClassNotFoundException();
	ClassNotFoundException(String& message);
};

EndPackage2

#endif