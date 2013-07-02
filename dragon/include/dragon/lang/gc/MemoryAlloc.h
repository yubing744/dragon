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

#ifndef MemoryAlloc_GC_Lang_Dragon_H 
#define MemoryAlloc_GC_Lang_Dragon_H

#include <dragon/config.h>

#include "GarbageCollector.h"

#ifndef MEMORY_BLOCK_SIZE
	#define MEMORY_BLOCK_SIZE 2048
#endif

BeginPackage3(dragon, lang, gc)

class _DragonExport MemoryAlloc {
public:
	enum {BLOCK_SIZE = MEMORY_BLOCK_SIZE};

private:
	struct MemBlock {
        MemBlock* pPrev;
        char buffer[BLOCK_SIZE];
    };

	enum {HEADER_SIZE = sizeof(MemBlock) - BLOCK_SIZE};

private:
	MemoryAlloc();

private:
    void* alloc(size_t cb);
    void  clear();

public:
	static MemoryAlloc* GetInstance();
	static void* Alloc(size_t cb);
	static void  Free(void* p);
	static void  Clear(void* p);
	
private:
	MemBlock* getChainHeader() const;

private:
	char* mpBegin;
    char* mpEnd;

private:
	static MemoryAlloc* ma;
};

typedef MemoryAlloc MA;

template <class Type,int Size=0>
struct DestructorMA {
	static void destruct(void* data) {
		Type* td=(Type*)data;
		Log("\n[%s] @%d is destructing...\n",typeid(td).name(),td);
		td->~Type();
		MA::Free(td);
	}

	static void destructArray(void* arr) {
		Type* data=(Type*)arr;
		Log("\n[%s] Array @%d is destructing...\n",typeid(data).name(),data);
		
		int size=(Size<1)?1:Size;
		for(int i=0;i<size;i++) {
			(data+i)->~Type();
			MA::Free(data+i);
		}
	}
};


template <class Type>
Type* New() {
	Type* p=new(MA::Alloc(sizeof(Type))) Type;
	GC::GetInstance()->regist(p,DestructorMA<Type>::destruct);
	return p;
}

template <class Type, class ArgType1>
Type* New(ArgType1 arg1) {
	Type* p=new(MA::Alloc(sizeof(Type))) Type(arg1);
	GC::GetInstance()->regist(p,DestructorMA<Type>::destruct);
	return p;
}

template <class Type, class A1, class A2>
Type* New(A1 a1, A2 a2) {
	Type* p=new(MA::Alloc(sizeof(Type))) Type(a1, a2);
	GC::GetInstance()->regist(p,DestructorMA<Type>::destruct);
	return p;
}

template <class Type, class A1, class A2, class A3>
Type* New(A1 a1,A2 a2,A3 a3) {
	Type* p=new(MA::Alloc(sizeof(Type))) Type(a1, a2, a3);
	GC::GetInstance()->regist(p,DestructorMA<Type>::destruct);
	return p;
}

template <class Type, class A1, class A2, class A3, class A4>
Type* New(A1 a1, A2 a2, A3 a3, A4 a4) {
	Type* p=new(MA::Alloc(sizeof(Type))) Type(a1, a2, a3, a4);
	GC::GetInstance()->regist(p,DestructorMA<Type>::destruct);
	return p;
}

template <class Type, int Count>
Type* NewArray() {
	Type* p = new(MA::Alloc(sizeof(size_t)+sizeof(Type)*Count)) Type[Count];
	GC::GetInstance()->regist(p,DestructorMA<Type,Count>::destructArray);
	return p;
}

EndPackage3//(dragon, lang, gc)

#endif//MemoryAlloc_GC_Lang_Dragon_H