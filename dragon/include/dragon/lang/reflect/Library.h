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

#ifndef Library_Reflect_Lang_Dragon_H 
#define Library_Reflect_Lang_Dragon_H

#include <dragon/config.h>

BeginPackage3(dragon, lang, reflect)

interface _DragonExport Library
{
public:
	virtual ~Library(){};

public:
	virtual void free() =0;
	virtual void load(String libPath) =0;

	virtual P<Class<Object>> getClassForName(String className) =0;
	virtual bool updateClass(Class<Object>* clazz)=0;
	virtual bool containsClass(String className) =0;
	virtual int getClassCount()=0;

	virtual FARPROC getClassProc(String methodName) =0;
	virtual P<Method> getClassMethod(String methodName) =0;
	virtual P<Array<P<Method>>> getClassMethods()=0;
	virtual int getMethodCount()=0;
};

EndPackage3//(dragon, lang, reflect)

#endif//Library_Reflect_Lang_Dragon_H