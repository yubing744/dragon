#include "util.h"
#include "Iterator.h"

#ifndef Util_List_H
#define Util_List_H
#pragma once

#include "Collection.h"

BeginPackage2(dragon,util)

Import dragon::lang;

template<class E>
interface List:public Collection<E>
{
public:
	virtual ~List(){};

public:
	virtual P<Iterator<E>> iterator() =0;

	virtual bool add(const E& e)=0;
	virtual bool remove(const E& e)=0;
	virtual int size()=0;
	virtual bool isEmpty()=0;
	virtual bool contains(const E& e)=0;
	virtual void clear()=0;

	virtual void add(int index,const E& e)=0;
	virtual E get(int index)=0;
	virtual E set(int index,const E& e)=0;

};

EndPackage2

#endif