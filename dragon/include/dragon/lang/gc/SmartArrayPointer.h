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
 * Created:     2013/07/07
 **********************************************************************/


#ifndef SmartArrayPointer_Gc_Lang_Dragon_H
#define SmartArrayPointer_Gc_Lang_Dragon_H

#include <dragon/config.h>

#include "GarbageCollector.h"


BeginPackage3(dragon, lang, gc)


template<class Type>
class _DragonExport SmartArrayPointer {
public:
	template <class T>
	struct DestructorNormal {
		static void NotDestructArray(void* arr) {

		}

		static void destructArray(void* arr) {
			T* data=(T*)(arr);
			delete[] data;
		}
	};

public:
	SmartArrayPointer();
	SmartArrayPointer(Type* p);
	SmartArrayPointer(Type* p, FnDestructor d);
	SmartArrayPointer(const SmartArrayPointer& sp);
	~SmartArrayPointer();

public:
	Type* operator=(Type* p);
	SmartArrayPointer& operator=(const SmartArrayPointer& sp);
	Type& operator*(){ return *mpType;};
	Type* operator->(){ return mpType;};
	operator Type*() { return mpType; };
	bool operator==(const SmartArrayPointer& sp);

public:
	const Type* raw() const { return mpType;};
	void* ployCast(Type* p);

private:
	Type* mpType;
}; //SmartArrayPointer


template<class Type>
SmartArrayPointer<Type>::SmartArrayPointer() {
	mpType = null;
}


template<class Type>
SmartArrayPointer<Type>::SmartArrayPointer(Type* p) {
	mpType = p;

	if(mpType==null) return;

	GC::GetInstance()->addRef(ployCast(mpType), mpType, DestructorNormal<Type>::destructArray);
}

template<class Type>
SmartArrayPointer<Type>::SmartArrayPointer(Type* p, FnDestructor d) {
	mpType = p;

	if(mpType==null) return;

	GC::GetInstance()->addRef(ployCast(mpType), mpType, d);
}

template<class Type>
SmartArrayPointer<Type>::SmartArrayPointer(const SmartArrayPointer& sp) {
	mpType = sp.mpType;
	GC::GetInstance()->addRef(ployCast(mpType));
}

template<class Type>
SmartArrayPointer<Type>::~SmartArrayPointer() {
	if (mpType != null) {
		GC::GetInstance()->release(ployCast(mpType));
	}
}


template<class Type>
Type* SmartArrayPointer<Type>::operator=(Type* p) {
	GC::GetInstance()->release(ployCast(mpType));

	if(p != null) {
		GC::GetInstance()->addRef(ployCast(p), p, DestructorNormal<Type>::destructArray);
	}

	mpType = p;
	return p;
}

template<class Type>
SmartArrayPointer<Type>& SmartArrayPointer<Type>::operator=(const SmartArrayPointer& sp) {
	GC::GetInstance()->release(ployCast(mpType));
	GC::GetInstance()->addRef(ployCast(sp.mpType));

	mpType = sp.mpType;

	return *this;
}

template<class Type>
dg_boolean SmartArrayPointer<Type>::operator==(const SmartArrayPointer& sp) {
	if(mpType == sp.mpType) {
		return dg_true;
	}

	return dg_false;
}


template<class Type>
void* SmartArrayPointer<Type>::ployCast(Type* p) {
	return (void*)p;
}


template<class Type>
inline bool operator<(const SmartArrayPointer<Type>& left,const SmartArrayPointer<Type>& right) {
	return left.mpType < right.mpType;
}

template<class Type>
inline size_t hash_value(const SmartArrayPointer<Type>& sp) {
	return (size_t)sp.mpType;
}


EndPackage3 //(dragon, lang, gc)

#define PArray SmartArrayPointer

#endif //SmartArrayPointer_Gc_Lang_Dragon_H
