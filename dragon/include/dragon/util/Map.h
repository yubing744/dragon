#include "util.h"

#ifndef Util_Map_H
#define Util_Map_H
#pragma once

BeginPackage2(dragon,util)

#define PEntryMap(K,V) P<Map<K,V>::Entry>
#define PIteratorMap(K,V) P<Iterator<PEntryMap(K,V)>>

template<class K=String,class V=P<Object>>
interface Map
{
public:
	interface Entry
	{
	public:
		virtual K getKey()=0;
		virtual V getValue()=0;
	};
public:
	virtual ~Map(){};

public:
	virtual int size()=0;
	virtual bool containsKey(K key)=0;
	virtual V get(K key)=0;
	virtual V put(K key,V value)=0;
	virtual V remove(K key)=0;
	virtual void clear()=0;
	virtual bool isEmpty()=0;
	virtual P<Iterator<P<Entry>>> iterator()=0;

};

typedef Map<String,P<Object>> SoMap;
typedef P<Map<String,P<Object>>> PSoMap;

//template<class K,class V>
//typedef typename P<Map<K,V>::Entry> PEntryMap
//
//template<class K,class V>
//typedef typename P<Iterator<PEntryMap<String,P<Method>>>> PIteratorMap

EndPackage2

#endif
