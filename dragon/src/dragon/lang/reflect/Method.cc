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
 * Created:     2013/07/25
 **********************************************************************/


#include <dragon/lang/reflect/Method.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang::reflect; 
Import dragon::lang::internal; 

typedef void* (DRAGON_THISCALL *Method0)();
typedef void* (DRAGON_THISCALL *Method1)(void* p);

typedef void* (DRAGON_THISCALL *AgrsMethod1)(void* p, void* agr1);
typedef void* (DRAGON_THISCALL *AgrsMethod2)(void* p, void* agr1, void* agr2);
typedef void* (DRAGON_THISCALL *AgrsMethod3)(void* p, void* agr1, void* agr2, void* agr3);
typedef void* (DRAGON_THISCALL *AgrsMethod4)(void* p, void* agr1, void* agr2, void* agr3, void* agr4);
typedef void* (DRAGON_THISCALL *AgrsMethod5)(void* p, void* agr1, void* agr2, void* agr3, void* agr4, void* agr5);
typedef void* (DRAGON_THISCALL *AgrsMethod6)(void* p, void* agr1, void* agr2, void* agr3, void* agr4, void* agr5, void* agr6);

Method::Method(const Class* clazz, const char* name, 
	void* procAddress, const Type* returnType, const Array<Type*>& parameterTypes) 
	:Member(clazz, name), procAddress(procAddress), returnType(returnType), parameterTypes(parameterTypes)  {
	//Nothing
}

const Array<Type*> Method::getParameterTypes() {
	return this->parameterTypes;
}

const Type* Method::getReturnType() {
	return this->returnType;
}

void* Method::invoke(void* pThis) {
	return Invoke<void*>(pThis, this->procAddress);
}

void* Method::invoke(void* pThis, const Array<void*>& args) {
	Array<Type*> tps = this->parameterTypes;
	Array<void*> args_in = args;

	void* ret = NULL;

	if (tps.size() == args_in.size()) {
		int argc = args_in.size();

		if (argc > 0) {
			ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * argc);

			for (int i = 0; i < argc; ++i) {
				Type* type = tps[i];
				void* obj = args_in[i];

				params[i] = ParamInfo(type->getName(), obj);
			}

			ret = Invoke(pThis, this->procAddress, params, argc);

			SafeDeleteArray(params);
		} else {
			ret = Invoke<void*>(pThis, this->procAddress);
		}
	}

	return ret;
}


/*
Method::Method():self(null){}

Method::operator const Char*()
{
	return this->getFullName().toCharArray();
}

void Method::setPackageName(String packageName)
{
	this->packageName=packageName;
}

void Method::setClassName(String className)
{
	this->className=className;
}
void Method::setName(String name)
{
	this->name=name;
}

void Method::setParameterTypes(Array<String>* parameterTypes)
{
	this->parameterTypes=parameterTypes;
}

void Method::build()
{
	String method;

	method.append(this->packageName);
	method.append(L"::");
	method.append(this->className);
	method.append(L"::");
	method.append(this->name);
	method.append(L"(");

	int len=this->parameterTypes->size();
	for(int i=0;i<len-1;i++)
	{
		method.append(this->parameterTypes->get(i));
		method.append(L",");
	}

	if(len>0)
	{
		method.append(this->parameterTypes->get(len-1));
		method.append(L")");
	}
	else
	{
		method.append(L"void)");
	}

	this->fullName=method;
}

void Method::setFullName(String fullName)
{
	this->fullName=fullName;
}

void Method::setProcAddress(FARPROC procAddress)
{
	this->procAddress=procAddress;
}

FARPROC Method::getProcAddress()
{
	return this->procAddress;
}

String Method::getFullName()
{
	if(this->fullName.equals(L""))
	{
		this->build();
	}

	return this->fullName;
}

void Method::setThis(void* base)
{
	this->self=base;
}

void* Method::getThis()
{
	return this->self;
}

void* Method::invoke()
{
	if(self==null)
	{
		Method0 method=(Method0)this->procAddress;
		return method();
	}

	return invoke(self);
}

void* Method::invoke(void* pThis)
{
	Method1 method=(Method1)this->procAddress;
	return method(pThis);
}

void* Method::invoke(void* pThis,Array<void*>& args)
{
	int argsNum=args.size()>=6?6:args.size();

	if(argsNum==1)
	{
		AgrsMethod1 method1=(AgrsMethod1)this->procAddress;
		return method1(pThis,args[0]);
	}
	else if(argsNum==2)
	{
		AgrsMethod2 method2=(AgrsMethod2)this->procAddress;
		return method2(pThis,args[0],args[1]);
	}
	else if(argsNum==3)
	{
		AgrsMethod3 method3=(AgrsMethod3)this->procAddress;
		return method3(pThis,args[0],args[1],args[2]);
	}

	return null;
}
*/