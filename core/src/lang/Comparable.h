#include "lang.h"

#if !defined(Lang_Comparable_H)
#define Lang_Comparable_H
#pragma once

BeginPackage2(ProjectName,lang)

template<class T>
interface Comparable
{
public:
	virtual int compareTo(T& o)=0;
};

EndPackage2

#endif