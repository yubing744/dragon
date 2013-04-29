#include "gc.h"


#ifdef _DEBUG

#ifndef Lang_GC_MemoryLeakCheck_H 
#define Lang_GC_MemoryLeakCheck_H
#pragma once

#undef OutputDebugString
//#define OutputDebugString  OutputDebugStringA
#define OutputDebugString  printf

#include <exception>
#include <list>

BeginPackage3(dragon,lang,gc)

struct ALLOC_INFO{ 
	DWORD address; 
	DWORD size; 
	char file[64]; 
	DWORD line; 
};

typedef std::list<ALLOC_INFO*> AllocList;

_DragonExport AllocList* GetAllocList();

_DragonExport void AddTrack(DWORD addr, DWORD asize, const char *fname, DWORD lnum);

_DragonExport void RemoveTrack(DWORD addr);

_DragonExport void DumpUnfreed();

EndPackage3

Import dragon::lang::gc;

inline void* operator new(unsigned int size,const char *file, int line)
{
	if (size==(size_t)0) size=1;
	void* ptr=::operator new(size);
	if (!ptr) throw std::bad_alloc();

	AddTrack((DWORD)ptr, size, file, line); 
	return(ptr); 

}

inline void* operator new[](unsigned int size,const char *file, int line)
{
	return operator new(size, file, line);
}

inline void operator delete(void* p,const char*, int)
{
	RemoveTrack((DWORD)p); 
	::operator delete(p); 
}

inline void operator delete[](void* p,const char*, int)
{
	RemoveTrack((DWORD)p); 
	::operator delete(p);
}

inline void operator delete(void* p)
{
	RemoveTrack((DWORD)p); 
	free(p); 
}

inline void operator delete[](void* p)
{
	RemoveTrack((DWORD)p); 
	free(p); 
}


#endif 

#ifdef _DEBUG 
#	define new new(__FILE__, __LINE__)
#endif 

#endif



