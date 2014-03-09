/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/21
 **********************************************************************/


#ifndef HashMap_Util_Dragon_H
#define HashMap_Util_Dragon_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/util/Map.h>

#include <map>

BeginPackage2(dragon, util)

Import std;
Import dragon::lang;

template<class K, class V>
class HashMap :public Object, public Map<K, V> {
public:

	class HashMapEntry implements(Map)<K, V>::Entry {
	public:
		HashMapEntry(K key, V* value) {
			this->key = key;
			this->value = value;
		};

		~HashMapEntry(){};

	public:
		virtual K getKey() {
			return key;
		};

		virtual V* getValue() {	
			V* v = value;
			SafeRetain(v);
			return v;
		};

	private:
		K key;
		V* value;
	};

public:
	typedef typename map<K, V*>::iterator StlIterator;
	typedef typename Map<K, V>::Entry MapEntry;

	class HashMapIterator implements(Iterator<MapEntry>) {
	public:
		HashMapIterator(StlIterator it, StlIterator itEnd) {
			this->it = it;
			this->itEnd = itEnd;
		}

		~HashMapIterator(){};

	public:
		virtual bool hasNext() {
			if(it != itEnd) {
				return true;
			}

			return false;
		};

		virtual MapEntry* next() {
			MapEntry* mapEntry = new HashMapEntry(it->first, it->second);
			it++;
			return mapEntry;
		};

	private:
		StlIterator it;
		StlIterator itEnd;
	};

public:
	HashMap();
	virtual ~HashMap();

public: //Implements Map<K, V> 
	virtual Iterator<MapEntry>* iterator();

	virtual V* put(K key,V* value);
	virtual V* get(K key);
	virtual bool containsKey(K key);
	virtual void clear();
	virtual V* remove(K key);
	virtual int size();
	virtual bool isEmpty();

private:
	map<K, V*> keyMap;
};

template<class K, class V>
HashMap<K, V>::HashMap(void){}

template<class K, class V>
HashMap<K, V>::~HashMap(void){
	this->clear();
}

template<class K, class V>
V* HashMap<K, V>::put(K key, V* value) {
	if (value != null) {
		keyMap[key] = value;
		SafeRetain(value);
	}

	return value;
}

template<class K, class V>
V* HashMap<K, V>::get(K key) {
	StlIterator it = keyMap.find(key);

	if(it != keyMap.end()) {
		V* v = keyMap[key];
		SafeRetain(v);
		return v;
	}

	return null;
}

template<class K, class V>
bool HashMap<K, V>::containsKey(K key) {
	StlIterator it = keyMap.find(key);
	return (it != keyMap.end());
}

template<class K, class V>
void HashMap<K, V>::clear() {
	for(StlIterator it=keyMap.begin(); it!=keyMap.end(); it++) { 
		V* val = it->second;
		SafeRelease(val);
	}

	keyMap.clear();
}

template<class K, class V>
V* HashMap<K, V>::remove(K key) {
	StlIterator it = keyMap.find(key);
	V* toDel = null;

	if(it != keyMap.end()) {
		toDel = it->second;
		keyMap.erase(it);

		SafeRelease(toDel);

		return toDel;
	}

	return null;
}

template<class K, class V>
Iterator<typename HashMap<K, V>::MapEntry>* HashMap<K, V>::iterator() {
	return new HashMapIterator(keyMap.begin(), keyMap.end());
}

template<class K, class V>
int HashMap<K, V>::size() {
	return keyMap.size();
}

template<class K, class V>
bool HashMap<K,V>::isEmpty() {
	return keyMap.empty();
}

EndPackage2//(dragon, util)

#endif//HashMap_Util_Dragon_H
