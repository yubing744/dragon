/*
* Copyright 2006 the original author or authors.
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

#include "reflect.h"

#ifndef Lang_Reflect_Method_H 
#define Lang_Reflect_Method_H
#pragma once

/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageReflect



typedef void* (__thiscall *Method0)();
typedef void* (__thiscall *Method1)(void* p);
typedef void* (__thiscall *AgrsMethod1)(void* p,void* agr1);
typedef void* (__thiscall *AgrsMethod2)(void* p,void* agr1,void* agr2);
typedef void* (__thiscall *AgrsMethod3)(void* p,void* agr1,void* agr2,void* agr3);
typedef void* (__thiscall *AgrsMethod4)(void* p,void* agr1,void* agr2,void* agr3,void* agr4);
typedef void* (__thiscall *AgrsMethod5)(void* p,void* agr1,void* agr2,void* agr3,void* agr4,void* agr5);
typedef void* (__thiscall *AgrsMethod6)(void* p,void* agr1,void* agr2,void* agr3,void* agr4,void* agr5,void* agr6);

class _DragonExport Method:public Object
{
public:
	Method();
	virtual ~Method(){};
	operator const Char*();
public:
	virtual void setPackageName(String packageName);
	virtual void setClassName(String className);
	virtual void setName(String name);
	virtual void setParameterTypes(Array<String>* parameterTypes);
	virtual void build();

	virtual void setFullName(String fullName);
	virtual String getFullName();

	virtual void setProcAddress(FARPROC procAddress);
	virtual FARPROC getProcAddress();
	virtual void setThis(void* base);
	virtual void* getThis();

	virtual void* invoke();
	virtual void* invoke(void* pThis);
	virtual void* invoke(void* pThis,Array<void*>& args);

protected:
	String packageName;
	String className;
	String name;

	P<Array<String>> parameterTypes;
	
	String fullName;
	FARPROC procAddress;
	void* self;
};

EndPackageReflect

#endif