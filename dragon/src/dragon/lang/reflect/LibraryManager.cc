#include "LibraryManager.h"



Import Reflect;
Import dragon::lang;

LibraryManager* LibraryManager::libMana=LibraryManager::InitLM();

LibraryManager* LibraryManager::InitLM()
{
	GC::SetCollectMode(GCMODE_AUTOCOLLECT);

	LibraryManager::libMana=null;

	HMODULE thisExe=GetModuleHandle(NULL);
	P<Library> lib=new DllLibrary(thisExe);
	LM::GetInstance()->registLibrary(L"local",lib);

	HMODULE hSysLib;
	LPCTSTR address=(LPCTSTR)LibraryManager::InitLM;
	if(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,address,&hSysLib))
	{
		P<Library> syslib=new DllLibrary(hSysLib);
		LM::GetInstance()->registLibrary(L"dragon",syslib);
	}

	File libDirectory(L".\\lib");
	if(libDirectory.exists() && libDirectory.isDirectory())
	{
		LM::GetInstance()->load(libDirectory.getCanonicalPath());
	}

	return LibraryManager::libMana;
}

LibraryManager::LibraryManager()
{
	this->librarys=new HashMap<String,P<Library>>();
}

void LibraryManager::load(String libPath) throw(FileNotFoundException)
{
	File file(libPath);
	if(!file.exists())
	{
		throw FileNotFoundException();
	}

	if (file.isDirectory())
	{
		P<Array<P<File>>> dllFiles=file.listFiles(L"*.dll");
		int fileCount=dllFiles->size();

		for(int i=0;i<fileCount;i++)
		{
			P<File> tempFile=dllFiles->get(i);
			String fileName=tempFile->getName();
			P<Library> lib=new DllLibrary(tempFile->getCanonicalPath());
			this->registLibrary(fileName,lib);
		}
	}
	else
	{
		P<Library> lib=new DllLibrary(file.getCanonicalPath());
		this->registLibrary(file.getName(),lib);
	}

}

int LibraryManager::getMethodCount()
{
	int sumSize=0;

	P<Iterator<P<Map<String,P<Library>>::Entry>>> it=librarys->iterator();
	while(it->hasNext())
	{
		P<Map<String,P<Library>>::Entry> entry=it->next();
		P<Library> lib=entry->getValue();
		sumSize+=lib->getMethodCount();
	}

	return sumSize;
}

FARPROC LibraryManager::getClassProc(String methodName)
{
	FARPROC result;
	
	P<Iterator<P<Map<String,P<Library>>::Entry>>> it=librarys->iterator();
	while(it->hasNext())
	{
		P<Map<String,P<Library>>::Entry> entry=it->next();
		String libName=entry->getKey();
		P<Library> lib=entry->getValue();

		result=lib->getClassProc(methodName);
		if(result!=null)
		{
			return result;
		}
	}

	return (FARPROC)null;
}

P<Method> LibraryManager::getClassMethod(String methodName)
{
	P<Method> result=null;
	
	P<Iterator<P<Map<String,P<Library>>::Entry>>> it=librarys->iterator();
	while(it->hasNext())
	{
		P<Map<String,P<Library>>::Entry> entry=it->next();
		String libName=entry->getKey();
		P<Library> lib=entry->getValue();

		result=lib->getClassMethod(methodName);
		if(result!=null)
		{
			return result;
		}
	}

	return (P<Method>)null;
}

P<Array<P<Method>>> LibraryManager::getClassMethods()
{
	int sumSize=this->getMethodCount();
	P<Array<P<Method>>> methodArray=new Array<P<Method>>(sumSize);

	P<Iterator<P<Map<String,P<Library>>::Entry>>> it=librarys->iterator();

	for(int i=0;it->hasNext();)
	{
		P<Map<String,P<Library>>::Entry> entry=it->next();
		P<Library> lib=entry->getValue();

		P<Array<P<Method>>> pm=lib->getClassMethods();
		int size=pm->size();

		for(int j=0;j<size;j++)
		{
			methodArray->set(i+j,pm->get(j));
		}

		i+=size;
	}

	return methodArray;
}

FARPROC LibraryManager::GetProcAddress(String methodName)
{
	return LM::GetInstance()->getClassProc(methodName);
}

P<Class<Object>> LibraryManager::getClassForName(String className)
{
	P<Class<Object>> result=null;
	
	P<Iterator<P<Map<String,P<Library>>::Entry>>> it=librarys->iterator();
	while(it->hasNext())
	{
		P<Map<String,P<Library>>::Entry> entry=it->next();

		P<Library> lib=entry->getValue();

		result=lib->getClassForName(className);

		if(result!=null)
		{
			return result;
		}
	}

	return (P<Class<Object>>)null;
}

bool LibraryManager::updateClass(Class<Object>* clazz)
{
	P<Iterator<P<Map<String,P<Library>>::Entry>>> it=librarys->iterator();
	while(it->hasNext())
	{
		P<Map<String,P<Library>>::Entry> entry=it->next();
		P<Library> lib=entry->getValue();
		
		if(lib->updateClass(clazz))
		{
			return true;
		}
	}
	
	return false;
}

bool LibraryManager::containsClass(String className)
{
	P<Iterator<P<Map<String,P<Library>>::Entry>>> it=librarys->iterator();
	while(it->hasNext())
	{
		P<Map<String,P<Library>>::Entry> entry=it->next();
		P<Library> lib=entry->getValue();
		if(lib->containsClass(className))
		{
			return true;
		}
	}

	return false;
}

int LibraryManager::getClassCount()
{
	int sumSize=0;

	P<Iterator<P<Map<String,P<Library>>::Entry>>> it=librarys->iterator();
	while(it->hasNext())
	{
		P<Map<String,P<Library>>::Entry> entry=it->next();
		P<Library> lib=entry->getValue();
		sumSize+=lib->getClassCount();
	}

	return sumSize;

}

void LibraryManager::free()
{
	this->librarys->clear();
	delete this->librarys;
	this->librarys=null;
}

void LibraryManager::Clear(void* p)
{
	//delete LM::Instance();
}

LibraryManager* LibraryManager::GetInstance()
{
	if(LibraryManager::libMana==null)
	{
		LibraryManager::libMana=new LibraryManager();
		GC::GetInstance()->addRef(ployCast(libMana),libMana,LibraryManager::Clear);
	}

	return LibraryManager::libMana;
}

void LibraryManager::registLibrary(String libName,Library* lib)
{
	this->librarys->put(libName,lib);
}

P<Library> LibraryManager::getLibrary(String libName)
{
	if(this->librarys->containsKey(libName))
	{
		return this->librarys->get(libName);
	}

	return null;
}

void LibraryManager::freeLibrary(String libName)
{
	if(this->librarys->containsKey(libName))
	{
		P<Library> lib=this->librarys->remove(libName);
		lib->free();
	}
}