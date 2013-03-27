#include "util.h"

#ifndef Util_Stack_H
#define Util_Stack_H
#pragma once

#include "ArrayList.h"

BeginPackage2(ProjectName,util)

template<class E>
class Stack:public ArrayList<E>
{

public:
	Stack():ArrayList(){};
	virtual ~Stack(){};

public:
	virtual E push(const E& e);
	virtual E pop();
	virtual E peek();
	virtual bool empty();
	virtual int search(const E& e);
};

//Implements Stack Interface

template<class E>
E Stack<E>::push(const E& e)
{
	this->add(e);
	return e;
}

template<class E>
E Stack<E>::pop()
{
	int size=this->size();
	E e=this->get(size-1);
	this->remove(e);
	return e;
}

template<class E>
E Stack<E>::peek()
{
	int size=this->size();
	return this->get(size-1);
}

template<class E>
bool Stack<E>::empty()
{
	return this->isEmpty();
}

template<class E>
int Stack<E>::search(const E& e)
{
	P<Iterator<E>> it=this->iterator();
	
	int index=0;

	while(it->hasNext())
	{
		index++;
		if(it->next()==e)
		{
			break;
		}
	}

	return index;
}

EndPackage2

#endif