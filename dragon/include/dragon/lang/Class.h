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

#ifndef Lang_Class_H
#define Lang_Class_H

#include <dragon/config.h>


#include "Object.h"
#include "ClassNotFoundException.h"
#include "reflect/reflect.h"


typedef int (__stdcall *Func_FarProc)();
typedef int (__thiscall *Func_GetClassSize)(void);

BeginPackage2(dragon,lang)

template<class Type=Object>
class Class:public Object
{
	friend class DllLibrary;
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
	Type* newInstance() throw(NoSuchMethodException);
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
	static P<Class<Type>> ForName(String name) throw(ClassNotFoundException,UnsupportedOperationException);
	static P<Class<Type>> ForName(String libPath,String name) throw(ClassNotFoundException,UnsupportedOperationException);
	static P<Class<Type>> ForName(Library* lib,String name) throw(ClassNotFoundException,UnsupportedOperationException);
	static String GetName();
	static String GetName(const Type* p);

private:
	const type_info* mpTypeInfo;
	int mSize;
	P<Constructor> constructor;
	String name;
	P<Map<String,P<Method>>> methods;
	P<Map<String,P<Field>>> fields;
};

template<class Type>
Class<Type>::Class()
{
	mpTypeInfo=&typeid(Type);
	mSize=sizeof(Type);
	this->name=L"";
	this->fields=null;
	this->methods=null;
	this->constructor=new TemplateConstructor<Type>();

	if(LM::GetInstance()->containsClass(this->getName()))
	{
		this->mergeWith(LM::GetInstance()->getClassForName(this->getName()));
	}
}

template<class Type>
Class<Type>::Class(const type_info* typeInfo)
{
	mpTypeInfo=typeInfo;
	mSize=1024;
	this->name=L"";
	this->fields=null;
	this->methods=null;
	this->constructor=new TemplateConstructor<Type>();

	if(LM::GetInstance()->containsClass(this->getName()))
	{
		this->mergeWith(LM::GetInstance()->getClassForName(this->getName()));
	}
}

template<class Type>
Class<Type>::Class(String name)
{
	mpTypeInfo=&typeid(Type);
	mSize=1024;
	this->name=name;
	this->fields=new HashMap<String,P<Field>>();
	this->methods=new HashMap<String,P<Method>>();
	this->constructor=null;
}

template<class Type>
String Class<Type>::getName()
{
	if(!this->name.equals(L""))
	{
		return this->name;
	}
	
	String temp=String::valueOf(mpTypeInfo->name());
	if(temp.startsWith(L"class "))
	{
		this->name=temp.substring(6);
	}

	return this->name;
}

template<class Type>
String Class<Type>::getRawName()
{
	return String(mpTypeInfo->raw_name());
}

template<class Type>
int Class<Type>::getSize()
{
	return mSize;
}

template<class Type>
Type* Class<Type>::cast(Object* obj)
{
	return (Type*)null;
}

template<class Type>
Type* Class<Type>::newInstance() throw(NoSuchMethodException)
{
	if(this->constructor==(P<Constructor>)null) throw NoSuchMethodException();

	Object* obj=(Object*)this->constructor->invoke();
	return (Type*)obj;
}

template<class Type>
bool Class<Type>::operator==(const Class<Type>& cls)
{
	return *mpTypeInfo==*(cls.mpTypeInfo);
}

template<class Type>
bool Class<Type>::operator!=(const Class<Type>& cls)
{
	return *mpTypeInfo!=*(cls.mpTypeInfo);
}

template<class Type>
void Class<Type>::mergeWith(P<Class<Object>> clazz)
{
	if(this->getName().equals(clazz->getName()))
	{
		this->fields=clazz->getFieldMap();
		this->methods=clazz->getMethodMap();
	}
}

template<class Type>
P<Class<Type>> Class<Type>::ForName(String libPath,String name)
	throw(ClassNotFoundException,UnsupportedOperationException)
{
	P<Library> lib=new DllLibrary(libPath);
	return Class<Type>::ForName(lib,name);
}

template<class Type>
P<Class<Type>> Class<Type>::ForName(Library* lib,String name)
	throw(ClassNotFoundException,UnsupportedOperationException)
{
	String className=name;

	if(name.startsWith(L"class "))
	{
		className=name.substring(6);
	}

	if(!lib->containsClass(className)) throw ClassNotFoundException();
	P<Class<Object>> tempClazz=lib->getClassForName(className);

	//method 1 to return a class Object
	P<Class<Object>> clazz=null;
	String GetClassText(className);
	GetClassText.append(L"::getClass(void)");
	GETCLASS getClass=(GETCLASS)tempClazz->getMethodAddress(GetClassText);

	if(getClass!=null) 
	{
		clazz=getClass();
		clazz->mergeWith(tempClazz);
		lib->updateClass(clazz);
		return clazz;
	}

	//method 2 to return a class Object
	int pos=className.lastIndexOf(L"::");
	if(pos==-1) pos=0;

	String ConstrucorText(className);
	ConstrucorText.append(L"::");
	ConstrucorText.append(className.substring(pos+1));
	ConstrucorText.append(L"(void)");
	FnConstructor fnCon=(FnConstructor)tempClazz->getMethodAddress(ConstrucorText);

	if(fnCon==null) throw UnsupportedOperationException();

	String GetClassSizeText(className);
	GetClassSizeText.append(L"::getClassSize(void)");
	GETCLASSSIZE getClassSize=(GETCLASSSIZE)tempClazz->getMethodAddress(GetClassSizeText);

	int classSize=256;

	if(getClassSize!=null) 
	{
		classSize=getClassSize();
	}

	tempClazz->mSize=classSize;
	tempClazz->name=className;
	tempClazz->constructor=new AddressConstructor(classSize,fnCon);

	return tempClazz;
}

template<class Type>
P<Class<Type>> Class<Type>::ForName(String name)
	throw(ClassNotFoundException,UnsupportedOperationException)
{
	P<Library> lib=LM::GetInstance();
	return Class<Type>::ForName(lib,name);
}

template<class Type>
String Class<Type>::GetName()
{
	const type_info* typeInfo = &typeid(Type);

	String className=String::valueOf(typeInfo->name());
	if(className.startsWith(L"class "))
	{
		className=className.substring(6);
	}

	return className;
}

template<class Type>
String Class<Type>::GetName(const Type* p)
{
	const type_info* typeInfo = &typeid(p);

	String className=String::valueOf(typeInfo->name());
	if(className.startsWith(L"class "))
	{
		className=className.substring(6);
	}

	return className;
}

template<class Type>
void Class<Type>::addMethod(Method* method)
{
	if(this->methods==(P<Map<String,P<Method>>>)null)
	{
		this->methods=new HashMap<String,P<Method>>();
	}

	this->methods->put(method->getFullName(),method);
}

template<class Type>
Func_FarProc Class<Type>::getMethodAddress(String methodName)
{
	P<Method> method=this->getMethod(methodName);

	if(method!=null)
	{
		return method->getProcAddress();
	}

	return (Func_FarProc)null;
}

template<class Type>
Method* Class<Type>::getMethod(String methodName)
{
	String fullName=this->name;

	if(!fullName.startsWith(this->name))
	{
		fullName.append(methodName);
	}
	else
	{
		fullName=methodName;
	}

	if(this->methods->containsKey(fullName))
	{
		return this->methods->get(fullName);
	}

	return null;
}

template<class Type>
Func_FarProc Class<Type>::lookupMethodAddress(String keyword)
{
	P<Method> method=this->lookupMethod(keyword);

	if(method!=null)
	{
		return method->getProcAddress();
	}

	return (Func_FarProc)null;
}

template<class Type>
P<Method> Class<Type>::lookupMethod(String keyword)
{
	P<Iterator<P<Map<String,P<Method>>::Entry>>> it=this->methods->iterator();

	while(it->hasNext())
	{
		P<Map<String,P<Method>>::Entry> entry=it->next();

		String fullName=entry->getKey();

		if(fullName.contains(keyword))
		{
			return entry->getValue();
		}
	}

	return (P<Method>)null;
}

template<class Type>
P<List<P<Method>>> Class<Type>::lookupMethods(String keyword)
{
	P<List<P<Method>>> out=new ArrayList<P<Method>>();

	P<Iterator<P<Map<String,P<Method>>::Entry>>> it=this->methods->iterator();

	while(it->hasNext())
	{
		P<Map<String,P<Method>>::Entry> entry=it->next();

		String fullName=entry->getKey();

		if(fullName.contains(keyword))
		{
			out->add(entry->getValue());
		}
	}

	return out;
}

template<class Type>
Field* Class<Type>::getField(String fieldName)
{
	if(this->fields->containsKey(fieldName))
	{
		return this->fields->get(fieldName);
	}

	return null;
}

template<class Type>
void Class<Type>::addField(Field* field)
{
	if(this->fields==(P<Map<String,P<Field>>>)null)
	{
		this->fields=new HashMap<String,P<Field>>();
	}

	this->fields->put(field->getName(),field);
}

template<class Type>
P<Map<String,P<Method>>> Class<Type>::getMethodMap()
{
	return this->methods;
}

template<class Type>
P<Map<String,P<Field>>> Class<Type>::getFieldMap()
{
	return this->fields;
}
EndPackage2

#endif