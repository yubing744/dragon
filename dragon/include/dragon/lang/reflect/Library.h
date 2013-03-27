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

#ifndef Lang_Reflect_Library_H 
#define Lang_Reflect_Library_H
#pragma once


/** 
 * Maintains all reflect operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackageReflect

interface _DragonExport Library
{
public:
	virtual ~Library(){};

public:
	virtual void free() =0;
	virtual void load(String libPath) throw(FileNotFoundException) =0;

	virtual P<Class<Object>> getClassForName(String className) =0;
	virtual bool updateClass(Class<Object>* clazz)=0;
	virtual bool containsClass(String className) =0;
	virtual int getClassCount()=0;

	virtual FARPROC getClassProc(String methodName) =0;
	virtual P<Method> getClassMethod(String methodName) =0;
	virtual P<Array<P<Method>>> getClassMethods()=0;
	virtual int getMethodCount()=0;
};

EndPackageReflect

#endif