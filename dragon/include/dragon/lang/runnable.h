#include "lang.h"

#if !defined(Lang_Runnable_H)
#define Lang_Runnable_H
#pragma once

BeginPackage2(ProjectName,lang)

interface _DragonExport Runnable
{
public:
	virtual void run()=0;
};

EndPackage2

#endif