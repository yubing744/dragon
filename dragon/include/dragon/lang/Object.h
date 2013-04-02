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

#ifndef Lang_Object_H
#define Lang_Object_H

#include <dragon/config.h>
#include "basic_type.h"

BeginPackage2(dragon,lang)

class String;

template<class Type>
class Class;

class _DragonExport Object
{
	template<class Type>
	friend class Class;

public:
	Object();
	virtual ~Object();

public:
	virtual Boolean equals(Object* obj);
	virtual int hashCode();
	virtual String toString();
	virtual Class<Object>* getClass();

private:
	virtual void setClass(Class<Object>* clazz);

protected:
	virtual void finalize();

protected:
	Class<Object>* clazz;
};

EndPackage2

#endif

