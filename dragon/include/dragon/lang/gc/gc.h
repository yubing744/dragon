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

#ifndef GC_Lang_Dragon_H
#define GC_Lang_Dragon_H

#include <dragon/config.h>


BeginPackage3(dragon, lang, gc)

	class GarbageCollector;
	class MemoryAlloc;

	template<class Type, int Size=0>
	class SmartPointer;

EndPackage3//(dragon, lang, gc)


#ifdef MEM_CHECK
#	include "MemoryLeakCheck.h"
#endif

#include "MemoryAlloc.h"
#include "SmartPointer.h"

#include "GarbageCollector.h"

#define P SmartPointer

#endif//GC_Lang_Dragon_H