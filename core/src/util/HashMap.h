#include "util.h"

#ifndef util_HashMap_Header
#define util_HashMap_Header
#pragma once

#include "Map.h"

#include <hash_map>

BeginPackage2(ProjectName,util)

Import std;
Import stdext;

template<class K=String,class V=P<Object>>
class HashMap :public Object,public Map<K,V>
{
public:
	typedef typename hash_map<K,V>::iterator StlIterator;
	typedef P<typename Map<K,V>::Entry> E;

	class HashMapEntry:public Map<K,V>::Entry
	{
	public:
		HashMapEntry(K key,V value)
		{
			this->key=key;
			this->value=value;
		};
	public:
		virtual K getKey()
		{
			return key;
		};

		virtual V getValue()
		{	
			return value;
		};

	private:
		K key;
		V value;
	};

	typedef P<HashMapEntry> HME;

	class HashMapIterator:public Iterator<E>
	{
	public:
		HashMapIterator(){};
		HashMapIterator(StlIterator it,StlIterator itEnd)
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
			E hmape=new HashMapEntry(it->first,it->second);
			it++;
			return hmape;
		};

	private:
		StlIterator it;
		StlIterator itEnd;
	};

public:
	HashMap();

public:
	virtual V put(K key,V value);
	virtual V get(K key);
	virtual bool containsKey(K key);
	virtual void clear();
	virtual V remove(K key);
	virtual int size();
	virtual bool isEmpty();

	virtual P<Iterator<E>> iterator();

private:
	hash_map<K,V> keyMap;

};

template<class K,class V>
HashMap<K,V>::HashMap(void){}


template<class K,class V>
V HashMap<K,V>::put(K key,V value)
{
	keyMap[key]=value;
	return value;
}

template<class K,class V>
V HashMap<K,V>::get(K key)
{
	StlIterator it=keyMap.find(key);

	if(it==keyMap.end())
	{
		return null;
	}

	return keyMap[key];
}

template<class K,class V>
bool HashMap<K,V>::containsKey(K key)
{
	StlIterator it=keyMap.find(key);

	if(it==keyMap.end())
	{
		return false;
	}

	return true;
}

template<class K,class V>
void HashMap<K,V>::clear()
{
	keyMap.clear();
}

template<class K,class V>
V HashMap<K,V>::remove(K key)
{
	StlIterator it=keyMap.find(key);
	StlIterator toDel;

	if(it!=keyMap.end())
	{
		toDel=keyMap.erase(it);
		return toDel->second;
	}

	return (V)null;
}

template<class K,class V>
P<Iterator<P<typename Map<K,V>::Entry>>> HashMap<K,V>::iterator()
{
	return new HashMapIterator(keyMap.begin(),keyMap.end());
}

template<class K,class V>
int HashMap<K,V>::size()
{
	return keyMap.size();
}

template<class K,class V>
bool HashMap<K,V>::isEmpty()
{
	return keyMap.empty();
}


typedef HashMap<String,P<Object>> SoHashMap;

EndPackage2

#endif