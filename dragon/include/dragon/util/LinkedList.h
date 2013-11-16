#include "util.h"
#include <list>

#ifndef Util_LinkedList_H
#define Util_LinkedList_H
#pragma once

#include "Iterable.h"
#include "List.h"
#include "Deque.h"


BeginPackage2(dragon,util)

template<class E>
class LinkedList:public Object,public Deque<E>
{
public:
	typedef typename list<E>::iterator StlIterator;

	class LinkedIterator:public Iterator<E>
	{
	public:
		LinkedIterator(StlIterator it,StlIterator itEnd)
		{
			this->it=it;
			this->itEnd=itEnd;
		}

	public:
		virtual bool hasNext()
		{
			if(it!=itEnd)
			{
				return true;
			}
			return false;
		};

		virtual E next()
		{
			return *(it++);
		};

	private:
		StlIterator it;
		StlIterator itEnd;
	};

public:
	LinkedList();

public:
	//List Interface Method
	virtual bool add(const E& e);
	virtual void add(int index,const E& e);
	virtual bool remove(const E& e);
	virtual int size();
	virtual bool isEmpty();
	virtual P<Iterator<E>> iterator();
	virtual bool contains(const E& e);
	virtual E get(int index);
	virtual E set(int index,const E& e);
	virtual void clear();

	//Queue and Deque Interface Method
	virtual bool offer(const E& e);
	virtual E poll();
	virtual E peek();

	//Deque Interface Method
	virtual bool offerFirst(const E& e);
	virtual E pollLast();
	virtual E peekLast();

public:
	virtual Array<E*> toArray();
	virtual Array<E*> toArray(Array<E*>& a);

private:
	list<E> mList;
};

template<class E>
LinkedList<E>::LinkedList()
{
	mList=list<E>();
}


//Implements List Interface

template<class E>
bool LinkedList<E>::add(const E& e)
{
	mList.push_back(e);
	return true;
}

template<class E>
void LinkedList<E>::add(int index,const E& e)
{
	int size=this->size();
	StlIterator pos;
	StlIterator ibegin=mList.begin();
	StlIterator	iend = mList.end();

	if(index<size/2)
	{
		pos=ibegin;
		for(int i=0;i<index && pos!=iend;i++,pos++);
	}
	else
	{
		pos=iend;
		for(int i=size;i>index && pos!=ibegin;i--,pos--);
	}

	mList.insert(pos,e);
}

template<class E>
bool LinkedList<E>::remove(const E& e)
{
	bool found=false;

	StlIterator ibegin,iend;
	ibegin = mList.begin();
	iend = mList.end();

	for(;ibegin != iend;++ibegin)
	{
		if(*ibegin==e)
		{
			found=true;
			mList.erase(ibegin);
			break;
		}
	}

	return found;
}

template<class E>
int LinkedList<E>::size()
{
	return mList.size();
}

template<class E>
bool LinkedList<E>::isEmpty()
{
	return mList.empty();
}

template<class E>
P<Iterator<E>> LinkedList<E>::iterator()
{
	return new LinkedIterator(mList.begin(),mList.end());
}

template<class E>
bool LinkedList<E>::contains(const E& e)
{
	StlIterator ibegin,iend;
	ibegin = mList.begin();
	iend = mList.end();

	for(;ibegin != iend;++ibegin)
	{
		if(*ibegin==e)
		{
			return true;
		}
	}

	return false;
}

template<class E>
E LinkedList<E>::get(int index)
{
	StlIterator pos=mList.begin();
	StlIterator	iend = mList.end();

	for(int i=0;i<index && pos!=iend;i++,pos++);

	return *pos;
}

template<class E>
E LinkedList<E>::set(int index,const E& e)
{
	StlIterator pos=mList.begin();
	StlIterator	iend = mList.end();

	for(int i=0;i<index && pos!=iend;i++,pos++);

	mList.insert(pos,e);
	pos++;
	E olde=*mList.erase(pos);
	return olde;
}

template<class E>
void LinkedList<E>::clear()
{
	mList.clear();
}

//Implements Queue Interface

template<class E>
bool LinkedList<E>::offer(const E& e)
{
	return this->add(e);
}

template<class E>
E LinkedList<E>::poll()
{
	if(this->isEmpty())
	{
		return null;
	}

	E e=this->get(0);
	this->remove(e);
	return e;
}

template<class E>
E LinkedList<E>::peek()
{
	if(this->isEmpty())
	{
		return null;
	}

	return this->get(0);
}



//Implements Deque Interface

template<class E>
bool LinkedList<E>::offerFirst(const E& e)
{
	this->add(0,e);
	return true;
}

template<class E>
E LinkedList<E>::pollLast()
{
	if(this->isEmpty())
	{
		return null;
	}

	E e=this->get(this->size()-1);
	LinkedList<E>::remove(e);
	return e;
}

template<class E>
E LinkedList<E>::peekLast()
{
	if(this->isEmpty())
	{
		return null;
	}

	return this->get(this->size()-1);
}

EndPackage2

#endif