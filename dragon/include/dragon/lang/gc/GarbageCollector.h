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

#ifndef GarbageCollector_GC_Lang_Dragon_H 
#define GarbageCollector_GC_Lang_Dragon_H

#include <dragon/config.h>

#include <map>
#include <string>

using namespace std;

BeginPackage3(dragon, lang, gc)

typedef void (*FnDestructor)(void* pThis);

enum _DragonExport GCMode {
	GCMODE_AUTOCOLLECT = 0,
	GCMODE_HANDCOLLECT = 1
};

class _DragonExport GarbageCollector {
public:
	struct PointerInfo {
		int refCount;
		void* memPtr;
		void* ployPtr;
		FnDestructor fnDestroy;
	};

	typedef map<void*, PointerInfo> KeyMap;
	typedef KeyMap::iterator Iterator;

public:
	void addRef(void* p);
	void addRef(void* p, void* tp, FnDestructor fn);
	void regist(void* p, FnDestructor fn);
	void regist(void* p, void* tp, FnDestructor fn);
	void release(void* p);

public:
	static GarbageCollector* GetInstance();
	static void Collect();
	static void ShowState();
	static void SetCollectMode(GCMode mode);

private:
	static void ClearAll();

private:
	static GarbageCollector* gc;

private:
	GarbageCollector();
	KeyMap mpMap;
	GCMode collectMode;
};

typedef GarbageCollector GC;

EndPackage3//(dragon, lang, gc)

#endif//GarbageCollector_GC_Lang_Dragon_H
