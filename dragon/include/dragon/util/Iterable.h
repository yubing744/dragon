#include "util.h"

#ifndef Util_Iterable_H
#define Util_Iterable_H
#pragma once

#include "Iterator.h"

BeginPackage2(dragon,util)

template<class E>
interface Iterable
{
public:
	virtual ~Iterable(){};

public:
	virtual P<Iterator<E>> iterator() =0;
};

EndPackage2

#endif
