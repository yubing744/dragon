#include <dragon/lang/gc/MemoryAlloc.h>

Import dragon::lang::gc;

MemoryAlloc* MemoryAlloc::ma=null;

MemoryAlloc::MemoryAlloc()
{
	mpBegin=(char*)HEADER_SIZE;
	mpEnd=(char*)HEADER_SIZE;
}

MemoryAlloc* MemoryAlloc::GetInstance()
{
	if(ma==null)
	{
		ma=new MemoryAlloc();
		GC::GetInstance()->addRef(ma,ma,MemoryAlloc::Clear);
	}

	return ma;
}

void* MemoryAlloc::Alloc(size_t cb)
{
	return MA::GetInstance()->alloc(cb);
}

void MemoryAlloc::Free(void* p)
{
	Log("MemoryAlloc::Free\n");
}

void  MemoryAlloc::Clear(void* p)
{
	Log("MemoryAlloc::Clear\n");
	MA::GetInstance()->clear();
	delete ma;
}

void* MemoryAlloc::alloc(size_t cb)
{
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


void MemoryAlloc::clear()
{
	MemBlock* pHeader = getChainHeader();

	while(pHeader)
	{
		MemBlock* pTemp=pHeader->pPrev;
		free(pHeader);
		pHeader = pTemp;
	}

	mpBegin=(char*)HEADER_SIZE;
	mpEnd=(char*)HEADER_SIZE;
}

MemoryAlloc::MemBlock* MemoryAlloc::getChainHeader() const
{
	return (MemBlock*)(mpBegin - HEADER_SIZE);
}