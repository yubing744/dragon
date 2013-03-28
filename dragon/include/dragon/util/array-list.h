#include "util.h"
#include <vector>

#ifndef Util_ArrayList_H
#define Util_ArrayList_H
#pragma once

#include "List.h"

BeginPackage2(ProjectName,util)

template<class E>
class ArrayList:public Object,public List<E>
{
public:
	typedef typename vector<E>::iterator StlIterator;

	class VectorIterator:public Iterator<E>
	{
	public:
		VectorIterator(StlIterator it,StlIterator itEnd)
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
	ArrayList();
	ArrayList(int initialCapacity);

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

	//Stack and PriorityQueue
	

	////Stack Interface Method
	//virtual E push(const E& e);
	//virtual E pop();
	//virtual E peek();
	//virtual bool empty();
	//virtual int search(const E& e);

	////PriorityQueue Interface Method
	//virtual bool offer(const E& e);
	//virtual E poll();
	//virtual E peek();



private:
	vector<E> mVector;
};

template<class E>
ArrayList<E>::ArrayList()
{
	mVector=vector<E>();
}

template<class E>
ArrayList<E>::ArrayList(int initialCapacity)
{
	mVector=vector<E>(initialCapacity);
}

//Implements List Interface

template<class E>
bool ArrayList<E>::add(const E& e)
{
	mVector.push_back(e);
	return true;
}

template<class E>
void ArrayList<E>::add(int index,const E& e)
{
	StlIterator pos=mVector.begin();
	StlIterator	iend = mVector.end();
	for(int i=0;i<index && pos!=iend;i++,pos++);
	mVector.insert(pos,e);
}

template<class E>
bool ArrayList<E>::remove(const E& e)
{
	bool found=false;

	StlIterator ibegin,iend;
	ibegin = mVector.begin();
	iend = mVector.end();

	for(;ibegin != iend;++ibegin)
	{
		if(*ibegin==e)
		{
			found=true;
			mVector.erase(ibegin);
			break;
		}
	}

	return found;
}

template<class E>
int ArrayList<E>::size()
{
	return mVector.size();
}

template<class E>
bool ArrayList<E>::isEmpty()
{
	return mVector.empty();
}

template<class E>
P<Iterator<E>> ArrayList<E>::iterator()
{
	return new VectorIterator(mVector.begin(),mVector.end());
}

template<class E>
bool ArrayList<E>::contains(const E& e)
{
	StlIterator ibegin,iend;
	ibegin = mVector.begin();
	iend = mVector.end();

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
E ArrayList<E>::get(int index)
{
	return mVector[index];
}

template<class E>
E ArrayList<E>::set(int index,const E& e)
{
	E olde=mVector[index];
	mVector[index]=e;
	return olde;
}

template<class E>
void ArrayList<E>::clear()
{
	mVector.clear();
}



EndPackage2

#endif