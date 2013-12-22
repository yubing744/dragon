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

#ifndef Class_Lang_Dragon_H
#define Class_Lang_Dragon_H

#include <dragon/config.h>

#include <dragon/lang/Array.h>

#include <dragon/lang/reflect/Type.h>
#include <dragon/lang/reflect/Constructor.h>
#include <dragon/lang/reflect/Method.h>
#include <dragon/lang/reflect/Field.h>

#include <typeinfo>

BeginPackage2(dragon, lang)

Import std;
Import dragon::lang::reflect;

class Object;
class ClassLoader;

class _DragonExport Class 
	extends(Type)
{
friend class dragon::lang::ClassLoader;

public:
	Class(const type_info& info, size_t size);
	
protected:
	Class(const ClassLoader* classLoader, 
		const char* packageName, const char* name);

	Class(const ClassLoader* classLoader, 
		const char* packageName, const char* name,
		const Array<Constructor*>& constructors, const Array<Method*>& methods,
		const Array<Field*>& fields);
public:
	virtual ~Class();

public:
	const char* getPackageName();
	const char* getSimpleName();

	Object* newInstance();
	Object* newInstance(const Array<Object*>& args);

	Constructor* getConstructor();
	Constructor* getConstructor(const Array<Type*>& parameterTypes);

	Method* getMethod(const char* methodName);
	Method* getMethod(const char* methodName, const Array<Type*>& parameterTypes);

protected:
	void setConstructors(const Array<Constructor*>& constructors);
	void setMethods(const Array<Method*>& methods);
	void setFields(const Array<Field*>& fields);

protected:
	char* packageName;
	Array<Constructor*> constructors;
	Array<Method*> methods;
	Array<Field*> fields;
	const ClassLoader* classLoader;
};


template <typename E, int N>
inline int Lenth(E (&arr)[N]){
    return N;
}     

inline int Lenth(void* p) {
	int* pSize = (int*)p;
	pSize--;
	return *pSize;
}

template<class Type>
inline bool InstanceOf(Object* pObj) {
	Type* pType = dynamic_cast<Type*>(pObj);
	return pType ? true : false;
}

template<class Type>
void* PloyCast(Type* p) {
	void* pObj = dynamic_cast<void*>(p);
	if(pObj==null) pObj=p;
	return pObj;
}

template<class T>
inline Class* ClassOf() {
    return new Class(typeid(T), sizeof(T));
}

template<class T>
inline Class* ClassOf(T type) {
    return new Class(typeid(type), sizeof(type));
}

template<class T>
inline Class* ClassOf(T* type) {
    return new Class(typeid(*type), sizeof(*type));
}

EndPackage2 //(dragon, lang)

#endif //Class_Lang_Dragon_H