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
 * Created:     2013/07/26
 **********************************************************************/


#include <dragon/lang/internal/LibraryClassLoader.h>
#include <dragon/lang/Class.h>
#include <dragon/lang/internal/platform.h>

#include <stdlib.h>

Import dragon::lang;
Import dragon::lang::reflect;
Import dragon::lang::internal;

LibraryClassLoader::LibraryClassLoader(){
	this->librarys = new LibraryList();
}

LibraryClassLoader::LibraryClassLoader(const char* libPath) {
	this->load(libPath);	
}

LibraryClassLoader::~LibraryClassLoader() {
	while (!this->librarys->empty()){
		Library* lib = this->librarys->back();
		this->librarys->pop_back();
		SafeDelete(lib);
	}

	SafeDelete(this->librarys);
}

void LibraryClassLoader::load(const char* libPath) {
	Library* lib = new Library(libPath);
	lib->resolve();
	this->librarys->push_back(lib);
}

const char* next_param_token(const char* str, int offset, size_t len) {
	int kk_count = 0;

	for(int i=offset; i<offset + len; i++) {
		char ch = str[i];
		if (ch == '<') {
			kk_count++;
		} else if (ch == '>') {
			kk_count--;
		} else if (ch == ',') {
			if (kk_count == 0) {
				return str + i;
			}
		}
	}

	return NULL;
}

Array<Type*> make_param_types(const char* sign, const char* className, const char* methodName) {
	size_t sign_len = strlen(sign);

	int offset = strlen(className) + strlen(methodName) + 3;
	size_t len = sign_len;

	Type** types = NULL;
	int t_count = 0;

	const char* token = NULL;

	do {
		len = sign_len - offset;
		token = next_param_token(sign, offset, len);

		if (token != NULL) {
			len = token - sign - offset;
		} else {
			len = len - 1;
		}

		Type* type = null;

		if (len != 0) {
			type = new Type(sign, offset, len);
		} else {
			break;
		}

		types = (Type**)realloc(types, sizeof(Type*)*(t_count+0x1));
		types[t_count++] = type;

		offset = offset + len + 2;
	} while(token != NULL);


	return Array<Type*>(types, t_count);
}

dg_boolean is_constructor(Class* clazz, Library::ExportSymbol* es) {
	const char* name = clazz->getName();
	const char* simpleName = clazz->getSimpleName();

	char* sign = Demangle(es->symbol);

	size_t len = strlen(simpleName);
	int offset = strlen(name) + 2;

	dg_boolean ret = dg_false;

	char* bb = sign + offset;
	if (offset + len <= strlen(sign) 
		&& memcmp(sign + offset, simpleName, len)==0x0
		&& bb[len] == '(') {
		ret = true;
	}

	free(sign);

	return ret;
}


Constructor* make_constructor(Class* clazz, Library::ExportSymbol* es) {
	const char* name = clazz->getName();
	const char* simpleName = clazz->getSimpleName();

	char* sign = Demangle(es->symbol);
	Array<Type*> parameterTypes = make_param_types(sign, name, simpleName);
	
	free(sign);

	return new Constructor(clazz, simpleName, es->address, parameterTypes);
}

dg_boolean is_method(Class* clazz, const char* methodName, Library::ExportSymbol* es) {
	const char* name = clazz->getName();

	char* sign = Demangle(es->symbol);
	size_t sign_size = strlen(sign);

	size_t len = strlen(methodName);
	int offset = strlen(name) + 2;

	dg_boolean ret = dg_false;

	char* bb = sign + offset;
	if (offset + len <= sign_size
		&& memcmp(sign + offset, methodName, len)==0x0
		&& bb[len] == '(') {
		ret = true;
	}

	free(sign);

	return ret;
}

Method* make_method(Class* clazz, const char* methodName, Library::ExportSymbol* es) {
	const char* name = clazz->getName();

	char* sign = Demangle(es->symbol);

	Array<Type*> parameterTypes = make_param_types(sign, name, methodName);
	
	free(sign);

	return new Method(clazz, methodName, es->address, parameterTypes);
}

Class* LibraryClassLoader::defineClass(const char* name, Library::NameSpace* ns) {
	const ClassLoader* classLoader = this;
	
	char* simpleName = new char[strlen(ns->name) + 1];
	strcpy(simpleName, ns->name);

	size_t p_size = strlen(name) - strlen(simpleName) - 2;
	char* packageName = new char[p_size + 1];
	memcpy(packageName, name, p_size);
	packageName[p_size] = '\0';
	delete[] simpleName;

	Class* clazz = createClass(this, packageName, name);
	delete[] packageName;

	Constructor** constructors = NULL;
	size_t cc_count = 0;

	Method** methods = NULL;
	size_t m_count = 0;

	Field** fields = NULL;
	size_t f_count = 0;

	size_t es_size = ns->symbolCount;

	for (int i=0; i<es_size; i++) {
		Library::ExportSymbol* es = &ns->symbols[i];

		if (is_constructor(clazz, es)) {
			Constructor* c = make_constructor(clazz, es);
			constructors = (Constructor**)realloc(constructors, sizeof(Constructor*)*(cc_count+0x1));
			constructors[cc_count++] = c;
		}
	}

	Library::NameSpace* p = ns->spaces;

	while(p != NULL) {
		es_size = p->symbolCount;

		for (int i=0; i<es_size; i++) {
			Library::ExportSymbol* es = &p->symbols[i];

			if (is_method(clazz, p->name, es)) {
				Method* m = make_method(clazz, p->name, es);
				methods = (Method**)realloc(methods, sizeof(Method*)*(m_count+0x1));
				methods[m_count++] = m;
			}
		}

		p = p->next;
	}

	setClassConstructors(clazz, Array<Constructor*>(constructors, cc_count));
	setClassMethods(clazz, Array<Method*>(methods, m_count));

	return clazz;
}

Class* LibraryClassLoader::findClass(const char* name){
	for (Iterator it = this->librarys->begin() ; it != this->librarys->end(); ++it) {
		Library* lib = *it;
		Library::NameSpace* ns = lib->findClassDefine(name);

		if (ns != NULL) {
			return this->defineClass(name, ns);
		}
	}

	return null;
}


/*

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

 */

