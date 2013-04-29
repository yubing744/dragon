#include <dragon/lang/gc/MemoryLeakCheck.h>

#ifdef _DEBUG

#undef new

BeginPackage3(dragon,lang,gc)

static AllocList *allocList=null;

AllocList* GetAllocList()
{
	if(!allocList)
	{
		allocList=new(AllocList);
		atexit(DumpUnfreed);
	}

	return allocList;
}

void AddTrack(DWORD addr, DWORD asize, const char *fname, DWORD lnum) 
{ 
	ALLOC_INFO* info; 

	info = new(ALLOC_INFO); 
	info->address = addr; 
	strncpy_s(info->file,64,fname, 63); 
	info->line = lnum; 
	info->size = asize; 
	GetAllocList()->insert(GetAllocList()->begin(), info); 
}; 

void RemoveTrack(DWORD addr) 
{ 
	AllocList::iterator i; 


	if(GetAllocList()->size()<1) return; 

	for(i = GetAllocList()->begin(); i != GetAllocList()->end(); i++) 
	{ 
		if((*i)->address == addr) 
		{ 
			GetAllocList()->remove((*i)); 
			break; 
		} 
	} 
}; 

void DumpUnfreed() 
{ 
	AllocList::iterator i; 
	DWORD totalSize = 0; 
	char buf[1024]; 

	if(GetAllocList()->size()<1) return; 

	sprintf_s(buf, "\n\n----MemoryLeakCheck-----------------------------------------\n\n"); 
	OutputDebugString(buf);

	for(i = GetAllocList()->begin(); i != GetAllocList()->end(); i++) { 
		sprintf_s(buf, "*%-50s \n Line %d, Address %d %d unfreed \n\n",(*i)->file, (*i)->line, (*i)->address, (*i)->size); 
		OutputDebugString(buf);

		totalSize += (*i)->size; 
	} 

	sprintf_s(buf, "----------------------------------------------------------- \n"); 
	OutputDebugString(buf);

	sprintf_s(buf, "Total Unfreed: %d bytes \n", totalSize); 
	OutputDebugString(buf); 

	delete GetAllocList();
	allocList=null;
};

EndPackage3

#endif
