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
 * Created:     2013/07/24
 **********************************************************************/


#ifndef ClassLoader_Lang_Dragon_H
#define ClassLoader_Lang_Dragon_H

#include <dragon/config.h>

#include <dragon/lang/Array.h>
#include <dragon/lang/reflect/Constructor.h>
#include <dragon/lang/reflect/Method.h>
#include <dragon/lang/reflect/Field.h>

#include <map>

BeginPackage2(dragon, lang)

class Class;
class Object;

Import std;
Import dragon::lang::reflect;

class _DragonExport ClassLoader {
public:
	static ClassLoader* getSystemClassLoader();

public:
	typedef map<const char*, Class*> ClassMap;
	typedef ClassMap::iterator Iterator;

protected:
    Class* createClass(const ClassLoader* classLoader, const char* packageName, const char* simpleName);
	void setClassConstructors(Class* clazz, const Array<Constructor*>& constructors);
	void setClassMethods(Class* clazz, const Array<Method*>& methods);
	void setClassFields(Class* clazz, const Array<Field*>& fields);

//----------------------------------
protected:
	ClassLoader();
	ClassLoader(ClassLoader* parent);
	virtual ~ClassLoader();

public:
	virtual Class* loadClass(const char* name);
	virtual ClassLoader* getParent();

protected:
	virtual Class* loadClass(const char* name, dg_boolean resolve);
	virtual Class* findLoadedClass(const char* name);
	virtual void resolveClass(Class* c);

protected:
	virtual Class* findClass(const char* name) = 0;

protected:
	ClassLoader* parent;
	ClassMap* loaded;
};//ClassLoader

EndPackage2 //(dragon, lang)

#endif //ClassLoader_Lang_Dragon_H
