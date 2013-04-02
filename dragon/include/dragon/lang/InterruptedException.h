#include "lang.h"

#ifndef Lang_InterruptedException_H
#define Lang_InterruptedException_H
#pragma once

#include "Exception.h"

BeginPackage2(dragon,lang)

class _DragonExport InterruptedException :public Exception
{
public:
	InterruptedException();
	InterruptedException(String& message);
};

EndPackage2

#endif