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

#ifndef Library_Internal_Lang_Dragon_H 
#define Library_Internal_Lang_Dragon_H

#include <dragon/config.h>

BeginPackage3(dragon, lang, internal)

class _DragonExport Library
{
public:
	struct ExportSymbol {
		char* symbol;
		void* address;
	};

	struct NameSpace {
		char* name;

		NameSpace* spaces;

		ExportSymbol* symbols;
		int symbolCount;

		NameSpace* next;
	};

	struct ClassTree {
		NameSpace* spaces;
	};

public:
	Library(const char* libPath);
	virtual ~Library();

public:
	virtual void resolve();
	virtual NameSpace* findClassDefine(const char* name);

protected:
	char* libPath;
	dg_boolean resolved;
	ClassTree* classTree;

/*
public:
	Library();
	Library(HMODULE hModule);
	Library(String dllPath) throw(FileNotFoundException);
	virtual ~Library();

public:
	virtual void load(String libPath) throw(FileNotFoundException);
	virtual void free();

	virtual P<Class<Object>> getClassForName(String className);
	virtual bool updateClass(Class<Object>* clazz);
	virtual bool containsClass(String className);
	virtual int getClassCount();

	virtual FARPROC getClassProc(String methodName);
	virtual P<Method> getClassMethod(String methodName);
	virtual P<Array<P<Method>>> getClassMethods();
	virtual int getMethodCount();

protected:
	virtual bool processLib();
	virtual bool processMethod(String methodSign, FARPROC pfn);

protected:
	HMODULE hModule;
	int methodCount;
	P<Map<String, P<Method>>> methodMap;
	P<Map<String, P<Class<Object>>>> classMap;
*/
};

EndPackage3//(dragon, lang, internal)

#endif//Library_Internal_Lang_Dragon_H