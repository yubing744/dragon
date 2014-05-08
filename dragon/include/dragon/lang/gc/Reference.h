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
#include <dragon/lang/Object.h>
#include <dragon/lang/NullPointerException.h>

BeginPackage3(dragon, lang, gc)

Import dragon::lang;

template<class Type>
class Reference {
public:
	Reference();
	Reference(const Type* p);
	Reference(const Reference& ref);
	~Reference();

public:
	Type* operator=(Type* p);
	Reference& operator=(const Reference& ref);
	Type& operator*(){ checkNullPointer(); return *referent; };
	Type* operator->(){ checkNullPointer(); return referent; };
	operator Type&() { checkNullPointer(); return *referent; };
	operator Type*() { checkNullPointer(); return referent; };
	bool operator==(const Reference& ref);
	

public:
	Type* raw() const { return referent;};
	Type& ref() const { checkNullPointer(); return *referent;};
	Type* retain() const { SafeRetain(referent); return referent; };
	void* ployCast(Type* p);

protected:
	void checkNullPointer() const {
		if (this->referent == null) {
			throw new NullPointerException();
		}
	}

private:
	Type* referent;
}; //Reference


template<class Type>
Reference<Type>::Reference() {
	referent = null;
}

template<class Type>
Reference<Type>::Reference(const Type* p) {
	referent = const_cast<Type*>(p);
}

template<class Type>
Reference<Type>::Reference(const Reference& ref) {
	referent = ref.referent;
	SafeRetain(referent);
}

template<class Type>
Reference<Type>::~Reference() {
	if (referent != null) {
		SafeRelease(referent);
	}
}

template<class Type>
Type* Reference<Type>::operator=(Type* p) {
	SafeRelease(referent);

	referent = p;
	return p;
}

template<class Type>
Reference<Type>& Reference<Type>::operator=(const Reference& ref) {
	SafeRelease(referent);
	SafeRetain(ref.referent);

	referent = ref.referent;

	return *this;
}

template<class Type>
bool Reference<Type>::operator==(const Reference& sp) {
	return (referent == sp.referent);
}

template<class Type>
void* Reference<Type>::ployCast(Type* p) {
	return (void*)p;
}

template<class Type>
inline bool operator<(const Reference<Type>& left, const Reference<Type>& right) {
	return left.raw() < right.raw();
}

template<class Type>
inline bool operator!=(const Reference<Type>& left, int address) {
	return left.raw() != (void*)address;
}

template<class Type>
inline bool operator==(const Reference<Type>& left, int address) {
	return left.raw() == (void*)address;
}

template<class Type>
inline size_t hash_value(const Reference<Type>& sp) {
	return (size_t)sp.referent;
}

EndPackage3 //(dragon, lang, gc)

#define Ref Reference

#endif //Reference_Gc_Lang_Dragon_H