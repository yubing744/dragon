#include "util.h"

#ifndef Util_Queue_H
#define Util_Queue_H
#pragma once

#include "List.h"

BeginPackage2(dragon,util)

template<class E>
interface Queue:public List<E>
{
public:
	virtual ~Queue(){};

public:
	virtual bool offer(const E& e)=0;
	virtual E poll()=0;
	virtual E peek()=0;
};

EndPackage2

#endif