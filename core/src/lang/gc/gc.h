#ifndef Lang_GC_H
#define Lang_GC_H

#include "../../config/config.h"

#define P SmartPointer

BeginPackage3(ProjectName,lang,gc)

	class GarbageCollector;
	class MemoryAlloc;

	template<class Type,int Size=0>
	class SmartPointer;

EndPackage3


#ifdef MEM_CHECK
#	include "MemoryLeakCheck.h"
#endif

#include "MemoryAlloc.h"
#include "SmartPointer.h"

#include "GarbageCollector.h"


#endif