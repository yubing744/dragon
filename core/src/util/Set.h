#include "util.h"

#ifndef Util_Set_H
#define Util_Set_H
#pragma once

#include "Collection.h"

BeginPackage2(ProjectName,util)

Import ProjectName::lang;

template<class E>
interface Set:public Collection<E>
{
public:
	virtual ~Set(){};

public:
	virtual P<Iterator<E>> iterator() =0;

	virtual void clear()=0;
	virtual bool add(const E& e)=0;
	virtual bool remove(const E& e)=0;
	virtual int size()=0;
	virtual bool isEmpty()=0;
	virtual bool contains(const E& e)=0;
};

EndPackage2

#endif