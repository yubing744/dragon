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


#ifndef Reference_Gc_Lang_Dragon_H
#define Reference_Gc_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/gc/GarbageCollector.h>

BeginPackage3(dragon, lang, gc)

template<class Type>
class Reference {
public:
	Reference();
	Reference(const Type* p);
	Reference(const Type* p, FnDestructor d);
	Reference(const Reference& ref);
	~Reference();

public:
	Type* operator=(Type* p);
	Reference& operator=(const Reference& ref);
	Type& operator*(){ return *mpType; };
	Type* operator->(){ return mpType; };
	operator Type*() { return mpType; };
	bool operator==(const Reference& ref);

public:
	Type* raw() const { return mpType;};
	void* ployCast(Type* p);

private:
	Type* mpType;
}; //Reference


template<class Type>
Reference<Type>::Reference() {
	mpType = null;
}

template<class Type>
Reference<Type>::Reference(const Type* p) {
	mpType = const_cast<Type*>(p);

	if (p != null) {
		GC::GetInstance()->addRef(ployCast(mpType), mpType, DestructorNormal<Type>::destruct);
	}
}

template<class Type>
Reference<Type>::Reference(const Type* p, FnDestructor d) {
	mpType = const_cast<Type*>(p);

	if (p != null) {
		GC::GetInstance()->addRef(ployCast(mpType), mpType, d);
	}
}

template<class Type>
Reference<Type>::Reference(const Reference& ref) {
	mpType = ref.mpType;
	GC::GetInstance()->addRef(ployCast(mpType));
}

template<class Type>
Reference<Type>::~Reference() {
	if (mpType != null) {
		GC::GetInstance()->release(ployCast(mpType));
	}
}

template<class Type>
Type* Reference<Type>::operator=(Type* p) {
	GC::GetInstance()->release(ployCast(mpType));

	if(p != null) {
		GC::GetInstance()->addRef(ployCast(p), p, DestructorNormal<Type>::destructArray);
	}

	mpType = p;
	return p;
}

template<class Type>
Reference<Type>& Reference<Type>::operator=(const Reference& ref) {
	GC::GetInstance()->release(ployCast(mpType));
	GC::GetInstance()->addRef(ployCast(ref.mpType));

	mpType = ref.mpType;

	return *this;
}

template<class Type>
bool Reference<Type>::operator==(const Reference& sp) {
	return (mpType == sp.mpType);
}

template<class Type>
void* Reference<Type>::ployCast(Type* p) {
	return (void*)p;
}

template<class Type>
inline bool operator<(const Reference<Type>& left, const Reference<Type>& right) {
	return left.mpType < right.mpType;
}

template<class Type>
inline size_t hash_value(const Reference<Type>& sp) {
	return (size_t)sp.mpType;
}

EndPackage3 //(dragon, lang, gc)

#define Ref Reference

#endif //Reference_Gc_Lang_Dragon_H
