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
 * Created:     2013/03/31
 **********************************************************************/

#include <stdlib.h>
 
#include <dragon/lang/gc/MemoryAlloc.h>

Import dragon::lang::gc;

MemoryAlloc* MemoryAlloc::ma = null;

MemoryAlloc::MemoryAlloc() {
	mpBegin = (char*)HEADER_SIZE;
	mpEnd = (char*)HEADER_SIZE;
}

MemoryAlloc* MemoryAlloc::GetInstance() {
	if(ma==null) {
		ma = new MemoryAlloc();
		atexit(MemoryAlloc::Clear);
	}

	return ma;
}

void* MemoryAlloc::Alloc(size_t cb) {
	return MA::GetInstance()->alloc(cb);
}

void MemoryAlloc::Free(void* p) {
	//Log("MemoryAlloc::Free\n");
}

void MemoryAlloc::Clear() {
	//Log("MemoryAlloc::Clear\n");
	MA::GetInstance()->clear();
	delete ma;
}


//------------------------------------------------------------
void* MemoryAlloc::alloc(size_t cb) {
	if((size_t)(mpEnd-mpBegin)<cb)
	{
		if (cb >= BLOCK_SIZE)
		{
			MemBlock* pHeader = getChainHeader();
			MemBlock* pNew = (MemBlock*)malloc(HEADER_SIZE+cb);

			if (pHeader)
			{
				pNew->pPrev = pHeader->pPrev;
				pHeader->pPrev = pNew;
			}
			else
			{
				mpBegin=pNew->buffer;
				mpEnd=pNew->buffer;
				pNew->pPrev=null;
			}

			return pNew->buffer;
		}
		else
		{
			MemBlock* pNew = (MemBlock*)malloc(sizeof(MemBlock));
			pNew->pPrev = getChainHeader();

			mpBegin = pNew->buffer;
			mpEnd = mpBegin + BLOCK_SIZE;
		}
	}

	return mpEnd -= (cb+1);
}


void MemoryAlloc::clear() {
	MemBlock* pHeader = getChainHeader();

	while(pHeader) {
		MemBlock* pTemp=pHeader->pPrev;
		free(pHeader);
		pHeader = pTemp;
	}

	mpBegin=(char*)HEADER_SIZE;
	mpEnd=(char*)HEADER_SIZE;
}

MemoryAlloc::MemBlock* MemoryAlloc::getChainHeader() const {
	return (MemBlock*)(mpBegin - HEADER_SIZE);
}