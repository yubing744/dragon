#include "gc.h"

#ifndef Lang_GC_GarbageCollector_H 
#define Lang_GC_GarbageCollector_H
#pragma once

#pragma  warning(disable:4251)   

#include <map>
#include <hash_map>
#include <string>

using namespace stdext;
using namespace std;

BeginPackage3(ProjectName,lang,gc)

typedef void (*FnDestructor)(void* pThis);

enum _DragonExport GCMode{
	GCMODE_AUTOCOLLECT = 0,
	GCMODE_HANDCOLLECT = 1
};

class _DragonExport GarbageCollector
{

public:
	struct PointerInfo
	{
		int refCount;
		void* memPtr;
		void* ployPtr;
		FnDestructor fnDestroy;
	};

	typedef hash_map<void*,PointerInfo> KeyMap;
	typedef KeyMap::iterator Iterator;

public:
	void addRef(void* p);
	void addRef(void* p,void* tp,FnDestructor fn);
	void regist(void* p,void* tp,FnDestructor fn);
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

EndPackage3

#endif