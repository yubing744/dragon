#include "lang.h"

#ifndef Lang_System_H
#define Lang_System_H 
#pragma once


BeginPackage2(dragon,lang)


class _DragonExport System :public Object
{
public:
	System();

public:
	static void load(String filename);
};

EndPackage2

#endif