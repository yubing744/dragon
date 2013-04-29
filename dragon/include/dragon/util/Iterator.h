#include "util.h"

#ifndef Util_Iterator_H
#define Util_Iterator_H
#pragma once

BeginPackage2(dragon,util)

template<class E>
interface Iterator
{
public:
	virtual bool hasNext()=0;
	virtual E next()=0;
};

EndPackage2

#endif
