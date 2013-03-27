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

#ifndef Lang_Reflect_Constructor_H 
#define Lang_Reflect_Constructor_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageReflect

typedef void (__thiscall *FnConstructor)(void* pThis);

interface Constructor
{
public:
	virtual void* invoke()=0;
};


template <class Type>
class TemplateConstructor:public Constructor
{
	void* invoke()
	{
		Type* type=new Type();
		return (void*)type;
	};
};

class AddressConstructor:public Constructor
{
public:
	AddressConstructor(int size,FnConstructor constructAddress)
	{
		this->classSize=size;
		this->fnCreateObject=constructAddress;
	}

public:
	void* invoke()
	{
		void* pThis=(void*)new char[classSize];
		fnCreateObject(pThis);
		return pThis;
	}

private:
	FnConstructor fnCreateObject;
	int classSize;
};

EndPackageReflect

#endif