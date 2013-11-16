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
			return *(it++);
		};

	private:
		StlIterator it;
		StlIterator itEnd;
	};

public:
	ArrayList();
	ArrayList(int initialCapacity);

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
	virtual Array<E*> toArray();
	virtual Array<E*> toArray(Array<E*>& a);

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

//Implements List Interface

template<class E>
bool ArrayList<E>::add(E* e) {
	mVector.push_back(e);
	return true;
}

template<class E>
void ArrayList<E>::add(int index, E* e) {
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
	return mVector[index];
}

template<class E>
E* ArrayList<E>::set(int index, E* e)
{
	E* olde = mVector[index];
	mVector[index] = e;
	return olde;
}

template<class E>
void ArrayList<E>::clear() {
	mVector.clear();
}

template<class E>
Array<E*> ArrayList<E>::toArray(Array<E*>& a) {
    int size = a.length();

    for(int i=0; i<size; i++) {
    	E* e = this->get(i);
        a.set(i, e);
    }

    return a;
}

template<class E>
Array<E*> ArrayList<E>::toArray() {
	int size = this->size();
    Array<E*> result(size);
    return this->toArray(result);
}

EndPackage2//(dragon, util)

#endif//ArrayList_Util_Dragon_H
