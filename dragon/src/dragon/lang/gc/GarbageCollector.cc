#include <dragon/lang/gc/GarbageCollector.h>

Import dragon::lang::gc;

GarbageCollector* GarbageCollector::gc=null;

GarbageCollector::GarbageCollector()
{
	collectMode=GCMODE_AUTOCOLLECT;
	mpMap=KeyMap();

	//atexit(ClearAll);
}

void GarbageCollector::ClearAll()
{
 	KeyMap& tMap=GC::GetInstance()->mpMap;

	Log("\n\nProgram is exiting...\n");
	Log("Prepare to delete all Object...\n\n");

	for(Iterator it=tMap.begin();tMap.size()>0;it=tMap.begin())
	{ 
		//it->second.fnDestroy(it->second.ployPtr);
		tMap.erase(it);
	}

	Log("\n");

	delete gc;

}
void GarbageCollector::Collect()
{
	KeyMap& tMap=GC::GetInstance()->mpMap;

	Log("\n\nGarbageCollector beginning working...\n\n");

	for(Iterator it=tMap.begin();tMap.size()>0 && it!=tMap.end();)
	{ 
		if(it->second.refCount<1)
		{
			it->second.fnDestroy(it->second.ployPtr);
			tMap.erase(it);
			it=tMap.begin();
		}
		else
		{
			it++;
		}
	}
}

void GarbageCollector::ShowState()
{
	KeyMap& tMap=GC::GetInstance()->mpMap;
	printf("\n--------------------\n");
	printf("Garbage State:\n\n");

	for(Iterator it=tMap.begin();it!=tMap.end();it++)
	{ 
		printf("@%d %d\n",it->first,it->second.refCount);
	}

	printf("--------------------\n\n");
}


void GarbageCollector::addRef(void* p)
{
	Iterator it=mpMap.find(p);

	if(it!=mpMap.end())
	{
		it->second.refCount++;
	}
}

void GarbageCollector::addRef(void* p,void* tp,FnDestructor fn)
{
	Iterator it=mpMap.find(p);

	if(it==mpMap.end())
	{
		PointerInfo pInfo;
		pInfo.refCount=1;
		pInfo.memPtr=p;
		pInfo.ployPtr=tp;
		pInfo.fnDestroy=fn;
		
		mpMap[pInfo.memPtr]=pInfo;
	}
	else
	{
		it->second.refCount++;
	}
}

void GarbageCollector::regist(void* p,void* tp,FnDestructor fn)
{
	Iterator it=mpMap.find(p);

	if(it==mpMap.end())
	{
		PointerInfo pInfo;
		pInfo.refCount=0;
		pInfo.memPtr=p;
		pInfo.ployPtr=tp;
		pInfo.fnDestroy=fn;

		mpMap[pInfo.memPtr]=pInfo;
	}
}

void GarbageCollector::release(void* p)
{
	Iterator it=mpMap.find(p);

	if(it==mpMap.end()) return;

	it->second.refCount--;

	if(this->collectMode==GCMODE_AUTOCOLLECT)
	{
		if(it->second.refCount<1)
		{
			it->second.fnDestroy(it->second.ployPtr);
			mpMap.erase(it);
		}
	}
}

GarbageCollector* GarbageCollector::GetInstance()
{
	if(gc==null)
	{
		gc=new GarbageCollector();
	}

	return gc;
}

void GarbageCollector::SetCollectMode(GCMode mode)
{
	GC::GetInstance()->collectMode=mode;
}