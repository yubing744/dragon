#include "lang.h"

#ifndef Lang_Number_H
#define Lang_Number_H 
#pragma once


BeginPackage2(dragon,lang)


class _DragonExport Number :public Object
{
public:
	Number();

public:
	static int ParseInt(String num) throw(NumberFormatException);
	static long ParseLong(String num) throw(NumberFormatException);
	static double ParseDouble(String num) throw(NumberFormatException);
	static float ParseFloat(String num) throw(NumberFormatException);
};

EndPackage2

#endif