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

#ifndef ArrayList_Util_Dragon_H
#define ArrayList_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/util/List.h>

#include <vector>

BeginPackage2(dragon, util)

Import std;
Import dragon::lang;

template<class E>
class ArrayList extends(Object) 
	implements1(List<E>) {
public:
	typedef typename vector<E*>::iterator StlIterator;

	class VectorIterator implements(Iterator<E>) {
	public:
		VectorIterator(StlIterator it, StlIterator itEnd) {
			this->it = it;
			this->itEnd = itEnd;
		}

	public:
		virtual bool hasNext() {
			if(it != itEnd) {
				return true;
			}

			return false;
		};

		virtual E* next() {
			E* e = *(it++);
			SafeRetain(e);
			return e;
		};

	private:
		StlIterator it;
		StlIterator itEnd;
	};

public:
	ArrayList();
	ArrayList(int initialCapacity);
	~ArrayList();

public: // implements List
	virtual Iterator<E>* iterator();

	virtual bool add(E* e);
	virtual void add(int index, E* e);
	virtual bool remove(E* e);
	virtual int size();
	virtual bool isEmpty();
	virtual bool contains(E* e);
	virtual E* get(int index);
	virtual E* set(int index, E* e);
	virtual void clear();

public:
	List<E>* subList(int fromIndex, int toIndex);

public:
	virtual Array<E*> toArray();
	virtual void toArray(Array<E*>& a);

private:
	vector<E*> mVector;
};

template<class E>
ArrayList<E>::ArrayList() 
	:mVector(vector<E*>()) {
}

template<class E>
ArrayList<E>::ArrayList(int initialCapacity) 
	:mVector(vector<E*>(initialCapacity)) {
}

template<class E>
ArrayList<E>::~ArrayList() {
	this->clear();
}

//Implements List Interface

template<class E>
bool ArrayList<E>::add(E* e) {
	SafeRetain(e);

	mVector.push_back(e);
	return true;
}

template<class E>
void ArrayList<E>::add(int index, E* e) {
	SafeRetain(e);

	StlIterator pos = mVector.begin();
	StlIterator	iend = mVector.end();

	for(int i=0; i<index && pos!=iend; i++,pos++) ;

	mVector.insert(pos, e);
}

template<class E>
bool ArrayList<E>::remove(E* e) {
	bool found = false;

	StlIterator ibegin,iend;
	ibegin = mVector.begin();
	iend = mVector.end();

	while(ibegin!=iend) {
		if(*ibegin == e) {
			found = true;

			mVector.erase(ibegin);
			SafeRelease(e);

			break;
		}

		ibegin++;
	}

	return found;
}

template<class E>
int ArrayList<E>::size() {
	return mVector.size();
}

template<class E>
bool ArrayList<E>::isEmpty() {
	return mVector.empty();
}

template<class E>
Iterator<E>* ArrayList<E>::iterator() {
	return new VectorIterator(mVector.begin(), mVector.end());
}

template<class E>
bool ArrayList<E>::contains(E* e) {
	StlIterator ibegin,iend;

	ibegin = mVector.begin();
	iend = mVector.end();

	for(;ibegin!=iend; ++ibegin) {
		if(*ibegin==e) {
			return true;
		}
	}

	return false;
}

template<class E>
E* ArrayList<E>::get(int index) {
	E* e = mVector[index];
	SafeRetain(e);

	return e;
}

template<class E>
E* ArrayList<E>::set(int index, E* e) {
	E* olde = mVector[index];
	SafeRelease(olde);

	mVector[index] = e;
	SafeRetain(e);

	return olde;
}

template<class E>
void ArrayList<E>::clear() {
	StlIterator ibegin,iend;

	ibegin = mVector.begin();
	iend = mVector.end();

	for(;ibegin!=iend; ++ibegin) {
		E* e = (*ibegin);
		SafeRelease(e);
	}

	mVector.clear();
}

template<class E>
void ArrayList<E>::toArray(Array<E*>& a) {
    int size = a.length();

    for(int i=0; i<size; i++) {
    	E* e = this->get(i);
        a.set(i, e);
    }
}

template<class E>
Array<E*> ArrayList<E>::toArray() {
	int size = this->size();
    Array<E*> result(size);
    this->toArray(result);

    return Array<E*>(result);
}

template<class E>
List<E>* ArrayList<E>::subList(int fromIndex, int toIndex) {
	int size = this->size();

	if (fromIndex < 0)
		fromIndex = 0;

	if (toIndex > size)
		toIndex = size;

	if (fromIndex >= toIndex) {
		return new ArrayList<E>();
	}

	ArrayList<E>* sub = new ArrayList<E>();

	for (int i=fromIndex; i<toIndex; i++) {
		E* e = this->get(i);
		sub->add(e);
		SafeRelease(e);
	}

	return sub;
}

EndPackage2//(dragon, util)

#endif//ArrayList_Util_Dragon_H
