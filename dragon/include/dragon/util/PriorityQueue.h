#include "util.h"

#ifndef Util_PriorityQueue_H
#define Util_PriorityQueue_H
#pragma once

#include "Queue.h"
#include "ArrayList.h"

BeginPackage2(dragon,util)

template<class E>
class PriorityQueue:public Object,public Queue<E>
{

public:
	PriorityQueue():mVector(){};
	virtual ~PriorityQueue(){};

public:
	virtual P<Iterator<E>> iterator();

	virtual bool add(const E& e);
	virtual bool remove(const E& e);
	virtual void clear();
	virtual int size();
	virtual bool isEmpty();
	virtual bool contains(const E& e);

	virtual void add(int index,const E& e);
	virtual E get(int index);
	virtual E set(int index,const E& e);


	virtual bool offer(const E& e);
	virtual E poll();
	virtual E peek();

private:
	ArrayList<E> mVector;
};

template<class E>
bool PriorityQueue<E>::add(const E& e)
{
	return mVector.add(e);
}

template<class E>
bool PriorityQueue<E>::remove(const E& e)
{
	return mVector.remove(e);
}

template<class E>
P<Iterator<E>> PriorityQueue<E>::iterator()
{
	return mVector.iterator();
}

template<class E>
void PriorityQueue<E>::clear()
{
	return mVector.clear();
}

template<class E>
int PriorityQueue<E>::size()
{
	return mVector.size();
}

template<class E>
bool PriorityQueue<E>::isEmpty()
{
	return mVector.isEmpty();
}

template<class E>
bool PriorityQueue<E>::contains(const E& e)
{
	return mVector.contains(e);
}

template<class E>
void PriorityQueue<E>::add(int index,const E& e)
{
	mVector.add(index,e);
}

template<class E>
E PriorityQueue<E>::get(int index)
{
	return mVector.get(index);
}

template<class E>
E PriorityQueue<E>::set(int index,const E& e)
{
	return mVector.set(index,e);
}


template<class E>
bool PriorityQueue<E>::offer(const E& e)
{
	return false;
}

template<class E>
E PriorityQueue<E>::poll()
{
	return null;
}

template<class E>
E PriorityQueue<E>::peek()
{
	return null;
}

EndPackage2

#endif