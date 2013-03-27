#include "util.h"

#ifndef Util_Deque_H
#define Util_Deque_H
#pragma once

#include "Queue.h"

BeginPackage2(ProjectName,util)

template<class E>
interface Deque:public Queue<E>
{
public:
	virtual ~Deque(){};

public:
	virtual bool offerFirst(const E& e)=0;
	virtual E pollLast()=0;
	virtual E peekLast()=0;

};

EndPackage2

#endif