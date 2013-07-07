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

#ifndef SmartPointer_GC_Lang_Dragon_H 
#define SmartPointer_GC_Lang_Dragon_H

#include <dragon/config.h>

#include "GarbageCollector.h"

BeginPackage3(dragon, lang, gc)

typedef void (*FnDestructor)(void* pThis);


template<class Type, int Size = 0>
class SmartPointer {
public:
	template<class T, int S >
	friend bool operator<(const SmartPointer<T, S>& left, const SmartPointer<T, S>& right);

	template<class T, int S>
	friend size_t hash_value(const SmartPointer<T, S>& sp);

public:
	template <class T>
	struct DestructorNormal {
		static void destruct(void* data) {
			try {
				T* td=(T*)(data);
				Log("\n[%s] @%d is destructing...\n", typeid(*td).name(), td);
				delete td;
			} catch(...) {
				Log("\ndelete[%s] @%d error...\n", typeid(*td).name(), td);
				return;
			}
		}

		static void destructArray(void* arr) {
			try {
				T* data=(T*)(arr);
				Log("\n[%s] Array @%d is destructing...\n",typeid(*data).name(),data);
				delete[] data;
			} catch(...) {
				Log("\ndelete[%s] Array @%d error...\n",typeid(*td).name(),td);
				return;
			}
		}
	};

public:
	SmartPointer();
	SmartPointer(Type* p);
	SmartPointer(const SmartPointer& sp);
	~SmartPointer();

public:
	Type* operator=(Type* p);
	SmartPointer& operator=(const SmartPointer& sp);
	Type& operator*(){ return *mpType;};
	Type* operator->(){ return mpType;};
	Type& operator[](int index);
	operator Type*() { return mpType; };
	bool operator==(const SmartPointer& sp);

public:
	bool isArray(){ return mIsArray;};
	int  length(){ return mIsArray?mArraySize:-1;};
	Type* raw(){ return mpType;};
	void* ployCast(Type* p);

private:
	Type* mpType;
	bool  mIsArray;
	int   mArraySize;
};


template<class Type, int Size>
SmartPointer<Type,Size>::SmartPointer() {
	mpType=null;

	mArraySize=Size;
	mIsArray=(mArraySize>0);
}

template<class Type, int Size>
SmartPointer<Type,Size>::SmartPointer(Type* p) {
	mpType = p;

	if(mpType==null) return;

	mArraySize=Size;
	mIsArray=(mArraySize>0);

	FnDestructor fnDestroy;

	if(mIsArray) {
		fnDestroy=DestructorNormal<Type>::destructArray;
	} else {
		fnDestroy=DestructorNormal<Type>::destruct;
	}

	GC::GetInstance()->addRef(ployCast(mpType), mpType, fnDestroy);
}

template<class Type, int Size>
SmartPointer<Type,Size>::SmartPointer(const SmartPointer& sp) {
	mpType = dynamic_cast<Type*>(sp.mpType);
	mArraySize = sp.mArraySize;
	mIsArray = (mArraySize>0);

	GC::GetInstance()->addRef(ployCast(mpType));
}

template<class Type, int Size>
SmartPointer<Type,Size>::~SmartPointer() {
	GC::GetInstance()->release(ployCast(mpType));
}


template<class Type, int Size>
Type* SmartPointer<Type,Size>::operator=(Type* p) {
	GC::GetInstance()->release(mpType);

	if(p!=null) {
		GC::GetInstance()->addRef(ployCast(p), p, DestructorNormal<Type>::destruct);
	}

	mpType=p;
	return p;
}

template<class Type, int Size>
SmartPointer<Type,Size>& SmartPointer<Type,Size>::operator=(const SmartPointer& sp) {
	GC::GetInstance()->release(ployCast(mpType));
	GC::GetInstance()->addRef(ployCast(sp.mpType));

	mpType=sp.mpType;

	return *this;
}

template<class Type, int Size>
bool SmartPointer<Type,Size>::operator==(const SmartPointer& sp) {
	if(mpType==sp.mpType) {
		return true;
	}

	return false;
}


template<class Type, int Size>
Type& SmartPointer<Type,Size>::operator[](int index) {
	if(index<0) {
		index = 0;
	} else if(index>=mArraySize) {
		index = mArraySize-1;
	}

	if(mIsArray) {
		return mpType[index];
	}

	return *mpType;
}

template<class Type, int Size>
void* SmartPointer<Type, Size>::ployCast(Type* p) {
	try {
		void* pObj = dynamic_cast<void*>(p);
		if(pObj==null) pObj=p;
		return pObj;
	} catch(...) {
		return null;
	}
}


template<class Type, int Size>
inline bool operator<(const SmartPointer<Type, Size>& left,const SmartPointer<Type, Size>& right) {
	return left.mpType < right.mpType;
}

template<class Type, int Size>
inline size_t hash_value(const SmartPointer<Type, Size>& sp) {
	return (size_t)sp.mpType;
}

EndPackage3//(dragon, lang, gc)


#define P SmartPointer

#endif//SmartPointer_GC_Lang_Dragon_H
