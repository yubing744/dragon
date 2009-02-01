#include "util.h"


#ifndef Util_HashSet_H
#define Util_HashSet_H
#pragma once

#include "Iterable.h"
#include <list>
#include <hash_set>

BeginPackage2(dragon,util)

Import std;
Import stdext;

template<class E>
class HashSet:public Object,public Set<E>
{
public:
	typedef typename hash_set<E>::iterator StlIterator;
	typedef typename hash_set<E>::size_type sizeType;

	class HashSetIterator:public Iterator<E>
	{
	public:
		HashSetIterator(StlIterator it,StlIterator itEnd)
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
	HashSet();

public:
	virtual bool add(const E& e);
	virtual bool remove(const E& e);
	virtual int size();
	virtual bool isEmpty();
	virtual P<Iterator<E>> iterator();
	virtual bool contains(const E& e);
	virtual void clear();

private:
	hash_set<E> mHashSet;
};

template<class E>
HashSet<E>::HashSet()
{
	mHashSet=hash_set<E>();
}


template<class E>
bool HashSet<E>::add(const E& e)
{
	pair<StlIterator,bool> out=mHashSet.insert(e);
	return out.second;
}


template<class E>
bool HashSet<E>::remove(const E& e)
{
	sizeType out=mHashSet.erase(e);
	return out>0?true:false;
}

template<class E>
int HashSet<E>::size()
{
	return mHashSet.size();
}

template<class E>
bool HashSet<E>::isEmpty()
{
	return mHashSet.empty();
}

template<class E>
P<Iterator<E>> HashSet<E>::iterator()
{
	return new HashSetIterator(mHashSet.begin(),mHashSet.end());
}

template<class E>
bool HashSet<E>::contains(const E& e)
{
	StlIterator pos = mHashSet.find(e);
	StlIterator iend = mHashSet.end();

	if(pos!=iend)
	{
		return true;
	}

	return false;
}

template<class E>
void HashSet<E>::clear()
{
	mHashSet.clear();
}

EndPackage2

#endif