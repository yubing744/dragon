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

BeginPackage2(dragon, lang)

Import dragon::lang::reflect;

class ClassLoader;

class _DragonExport Class 
	extends(Type)
{
friend class dragon::lang::ClassLoader;

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

	void* newInstance();
	void* newInstance(const Array<Object*>& args);

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

/*
public:
	Class();
	Class(const type_info* typeInfo);

public:
	bool operator==(const Class<Type>& cls);
	bool operator!=(const Class<Type>& cls);

public:
	String getName();
	String getRawName();
	int getSize();
	Type* cast(Object* obj);
	
	Func_FarProc getMethodAddress(String methodName);
	Field* getField(String fieldName);
	Method* getMethod(String methodName);
	P<List<P<Method>>> lookupMethods(String keyword);
	P<Method> lookupMethod(String keyword);
	Func_FarProc lookupMethodAddress(String keyword);

	P<Map<String,P<Method>>> getMethodMap();
	P<Map<String,P<Field>>> getFieldMap();

private:
	Class(String name);
	void addField(Field* field);
	void addMethod(Method* method);
	void setName(String name);
	void mergeWith(P<Class<Object>> clazz);

public: 
	static P<Class<Type>> ForName(String name);
	static P<Class<Type>> ForName(String libPath,String name);
	static P<Class<Type>> ForName(Library* lib,String name);
	static String GetName();
	static String GetName(const Type* p);

private:
	const type_info* mpTypeInfo;
	int mSize;
	P<Constructor> constructor;
	String name;
	P<Map<String,P<Method>>> methods;
	P<Map<String,P<Field>>> fields;
*/
};

EndPackage2 //(dragon, lang)

#endif //Class_Lang_Dragon_H