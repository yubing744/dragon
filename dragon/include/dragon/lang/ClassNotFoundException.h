

#ifndef Lang_ClassNotFoundException_H
#define Lang_ClassNotFoundException_H

#include "lang.h"
#include "Exception.h"

BeginPackage2(dragon,lang)

class _DragonExport ClassNotFoundException :public Exception
{
public:
	ClassNotFoundException();
	ClassNotFoundException(String& message);
};

EndPackage2

#endif