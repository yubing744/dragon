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

#include "dragon.h"

#ifndef Lang_dragon_LibraryManager_H 
#define Lang_dragon_LibraryManager_H
#pragma once

#include "Library.h"


BeginPackage3(dragon, lang, reflect)


class _DragonExport LibraryManager:public Object,public Library
{
private:
	LibraryManager();
	virtual ~LibraryManager(){};

public:
 	virtual void free();
	virtual void load(String libPath) throw(FileNotFoundException);

	virtual P<Class<Object>> getClassForName(String className);
	virtual bool updateClass(Class<Object>* clazz);
	virtual bool containsClass(String className);
	virtual int getClassCount();

	virtual int getMethodCount();
	virtual FARPROC getClassProc(String methodName);
	virtual P<Method> getClassMethod(String methodName);
	virtual P<Array<P<Method>>> getClassMethods();

public:
	virtual void registLibrary(String libName,Library* lib);
	virtual void freeLibrary(String libName);
	virtual P<Library> getLibrary(String libName);

public:
	static LibraryManager* GetInstance();
	static void Clear(void* p);
	static LibraryManager* InitLM();
	static FARPROC GetProcAddress(String methodName);

private:
	static LibraryManager* libMana;

private:
	P<Map<String,P<Library>>> librarys;
};

typedef LibraryManager LM;

EndPackage3//(dragon, lang, reflect)

#endif