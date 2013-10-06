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

#ifndef HelpFunc_Lang_Dragon_H
#define HelpFunc_Lang_Dragon_H

#include <dragon/config.h>

class dragon::lang::Object;

BeginPackage2(dragon, lang)


template <typename E, int N>
inline int Lenth(E (&arr)[N]){
    return N;
}     

inline int Lenth(void* p) {
	int* pSize=(int*)p;
	pSize--;
	return *pSize;
}

template<class Type>
inline bool InstanceOf(Object* pObj) {
	Type* pType = dynamic_cast<Type*>(pObj);
	return pType?true:false;
}

template<class Type>
void* PloyCast(Type* p) {
	void* pObj = dynamic_cast<void*>(p);
	if(pObj==null) pObj=p;
	return pObj;
}

template<class Type>
inline bool TypeOf(Object* pObj) {
    
}


EndPackage2

#endif