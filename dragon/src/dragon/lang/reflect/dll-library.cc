#include "DllLibrary.h"
#include <windows.h>
#include <Dbghelp.h>
#include "../lang.h"


#pragma comment(lib,"Dbghelp.lib")

Import Reflect;
Import ProjectName::lang;

DllLibrary::DllLibrary()
{
	hModule=null;
	this->methodCount=0;
	this->methodMap=new HashMap<String,P<Method>>();
	this->classMap=new HashMap<String,P<Class<Object>>>();
}

DllLibrary::DllLibrary(HMODULE hModule)
{
	this->hModule=hModule;
	this->methodCount=0;
	this->methodMap=new HashMap<String,P<Method>>();
	this->classMap=new HashMap<String,P<Class<Object>>>();
	this->processLib();
}

DllLibrary::DllLibrary(String dllPath) throw(FileNotFoundException)
{
	File file(dllPath);
	if(!file.exists())
	{
		throw FileNotFoundException();
	}

	this->methodCount=0;
	this->hModule=LoadLibrary(file.getCanonicalPath());
	this->methodMap=new HashMap<String,P<Method>>();
	this->classMap=new HashMap<String,P<Class<Object>>>();
	this->processLib(); 
}

DllLibrary::~DllLibrary()
{
	if(this->hModule!=null)
	{
		FreeLibrary(this->hModule);
	}
}

void DllLibrary::free()
{
	if(this->hModule!=null)
	{
		methodMap->clear();
		FreeLibrary(this->hModule);
	}
}

void DllLibrary::load(String libPath) throw(FileNotFoundException)
{
	this->free();

	File file(libPath);
	if(!file.exists())
	{
		throw FileNotFoundException();
	}

	this->hModule=LoadLibrary(file.getCanonicalPath());
	this->processLib();
}

bool DllLibrary::processLib()
{
	if(this->hModule==null)
	{
		return false;
	}

	LONG pModuleBase=(LONG)this->hModule;

	IMAGE_DOS_HEADER* pDosHead;
	pDosHead=(IMAGE_DOS_HEADER*)pModuleBase;

	if(pDosHead->e_magic!=IMAGE_DOS_SIGNATURE)
	{
		return false;
	}

	IMAGE_NT_HEADERS* pImageNTHead;

	pImageNTHead=(IMAGE_NT_HEADERS*)(pModuleBase + pDosHead->e_lfanew);

	if(pImageNTHead->Signature!=IMAGE_NT_SIGNATURE)
	{
		return false;
	}

	IMAGE_FILE_HEADER imageFileHead=pImageNTHead->FileHeader;

	if(imageFileHead.Machine!=IMAGE_FILE_MACHINE_I386)
	{
		return false;
	}

	IMAGE_DATA_DIRECTORY exportItem=pImageNTHead->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	IMAGE_EXPORT_DIRECTORY*  pImageExportDirectory= (IMAGE_EXPORT_DIRECTORY*)(pModuleBase+exportItem.VirtualAddress);

	DWORD OffsetStart = exportItem.VirtualAddress;
	DWORD Size = exportItem.Size;

	int numFuncs=pImageExportDirectory->NumberOfFunctions;
	int numNames = pImageExportDirectory->NumberOfNames;

	LPDWORD pAddressOfFunctions = (LPDWORD)(pImageExportDirectory->AddressOfFunctions + pModuleBase);
	LPWORD  pAddressOfOrdinals = (LPWORD)(pImageExportDirectory->AddressOfNameOrdinals + pModuleBase);
	LPDWORD pAddressOfNames = (LPDWORD)(pImageExportDirectory->AddressOfNames + pModuleBase);

	char tName[512];

	DWORD Flags=UNDNAME_COMPLETE;
	Flags|=UNDNAME_NO_ALLOCATION_LANGUAGE;
	Flags|=UNDNAME_NO_ACCESS_SPECIFIERS;
	Flags|=UNDNAME_NO_ALLOCATION_MODEL;
	Flags|=UNDNAME_NO_FUNCTION_RETURNS;
	Flags|=UNDNAME_NO_MEMBER_TYPE;
	Flags|=UNDNAME_NO_MS_KEYWORDS;
	Flags|=UNDNAME_NO_MS_THISTYPE;
	Flags|=UNDNAME_NO_THROW_SIGNATURES;
	Flags|=UNDNAME_NO_THISTYPE;
	Flags|=UNDNAME_NO_RETURN_UDT_MODEL;

	for(int i=0;i<numFuncs;i++)
	{
		char* pName= (char* )(pAddressOfNames[i] + pModuleBase);
		DWORD len=UnDecorateSymbolName(pName,tName,512,Flags);
		FARPROC pfn=(FARPROC)(pAddressOfFunctions[i]+pModuleBase);
		this->processMethod(String::valueOf(tName),pfn);
	}

	return true;
}

bool DllLibrary::processMethod(String methodSign,FARPROC pfn)
{
	int leftBracket=methodSign.indexOf(L'(');
	if(leftBracket==-1) return false;
	int rightBracket=methodSign.indexOf(L')',leftBracket);
	int packageEnd=methodSign.lastIndexOf(L"::",leftBracket);
	int packageBegin=methodSign.lastIndexOf(L" ",packageEnd);
	packageBegin=(packageBegin==-1)?0:packageBegin+1;

	String className=methodSign.substring(packageBegin,packageEnd-1);

	P<Class<Object>> clazz=null;

	if(this->classMap->containsKey(className))
	{
		clazz=this->classMap->get(className);
	}
	else
	{
		clazz=new Class<Object>(className);
		this->classMap->put(className,clazz);
	}

	String methodName=methodSign.substring(packageEnd+1,leftBracket);

	Method* method=new Method();
	method->setFullName(methodSign);

	method->setName(methodName);
	method->setProcAddress(pfn);

	if(methodName.startsWith(L"set") && methodName.length()>3)
	{
		String fieldName;

		String tempName=methodName.substring(3);
		fieldName.append(tempName.substring(0,1).toLowerCase());
		fieldName.append(tempName.substring(1));

		String fieldType=methodSign.substring(leftBracket+1,rightBracket);

		Property* prop=(Property*)clazz->getField(fieldName);
		if(prop==null)
		{
			prop=new Property(fieldName,fieldType,method,null);
		}
		else
		{
			prop->setSetter(method);
		}

		clazz->addField(prop);
	}
	else if(methodName.startsWith(L"get") && methodName.length()>3)
	{
		String fieldName;

		String tempName=methodName.substring(3);
		fieldName.append(tempName.substring(0,1).toLowerCase());
		fieldName.append(tempName.substring(1));

		String fieldType=methodSign.substring(leftBracket+1,rightBracket);

		Property* prop=(Property*)clazz->getField(fieldName);
		if(prop==null)
		{
			prop=new Property(fieldName,fieldType,null,method);
		}
		else
		{
			prop->setGetter(method);
		}

		clazz->addField(prop);
	}

	clazz->addMethod(method);

	//methodMap->put(methodSign,method);

	return true;
}

P<Class<Object>> DllLibrary::getClassForName(String className)
{
	return this->classMap->get(className);
}

bool DllLibrary::updateClass(Class<Object>* clazz)
{
	if(this->classMap->containsKey(clazz->getName()))
	{
		this->classMap->put(clazz->getName(),clazz);
		return true;
	}

	return false;
}

bool DllLibrary::containsClass(String className)
{
	if(this->classMap->containsKey(className))
	{
		return true;
	}

	return false;
}

int DllLibrary::getClassCount()
{
	return this->classMap->size();
}

FARPROC DllLibrary::getClassProc(String methodName)
{
	P<Method> method=getClassMethod(methodName);

	if(method!=null)
	{
		return method->getProcAddress();
	}

	return (FARPROC)null;
}

P<Method> DllLibrary::getClassMethod(String methodName)
{
	if(methodMap->containsKey(methodName))
	{
		return methodMap->get(methodName);
	}

	return (P<Method>)null;
}


P<Array<P<Method>>> DllLibrary::getClassMethods()
{
	int size=methodMap->size();
	P<Array<P<Method>>> methodArray=new Array<P<Method>>(size);

	PIteratorMap(String,P<Method>) it=methodMap->iterator();

	for(int i=0;it->hasNext() && i<size;i++)
	{
		PEntryMap(String,P<Method>) entry=it->next();

		String fullName=entry->getKey();
		P<Method> method=entry->getValue();

		methodArray->set(i,method);
	}

	return methodArray;
}

int DllLibrary::getMethodCount()
{
	return methodMap->size();
}