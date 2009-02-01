#include "util.h"

#ifndef Util_Collection_H
#define Util_Collection_H
#pragma once

#include "Iterable.h"

BeginPackage2(dragon,util)

template<class E>
interface Collection:public Iterable<E>
{
public:
	virtual ~Collection(){};

public:
	virtual P<Iterator<E>> iterator() =0;

	virtual void clear()=0;
	virtual int size()=0;
	virtual bool isEmpty()=0;
	virtual bool contains(const E& e)=0;
};

EndPackage2

#endif