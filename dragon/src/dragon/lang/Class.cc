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


#include <dragon/lang/Class.h>

#include <stdlib.h>
#include <string.h>
#include <dragon/lang/ClassLoader.h>

#include <typeinfo>

Import dragon::lang;

Class::Class(const type_info& info, size_t size) 
	:Type(info, size){
	this->classLoader = ClassLoader::getSystemClassLoader();
}

Class::Class(const ClassLoader* classLoader, 
		const char* packageName, const char* name) 
	:Type(name), classLoader(classLoader) 
{
	size_t p_size = strlen(packageName);
	char* buf = (char*)malloc(p_size + 1);
	strcpy(buf, packageName);
	this->packageName = buf;
}

Class::Class(const ClassLoader* classLoader, 
		const char* packageName, const char* name,
		const Array<Constructor*>& constructors, const Array<Method*>& methods,
		const Array<Field*>& fields) 
	:Type(name), classLoader(classLoader), constructors(constructors), methods(methods), fields(fields) 
{
	size_t p_size = strlen(packageName);
	char* buf = (char*)malloc(p_size + 1);
	strcpy(buf, packageName);
	this->packageName = buf;
}


Class::~Class() {
	SafeFree(this->packageName);

	// release Constructor
	size_t cc_size = this->constructors.size();

	if (cc_size > 0) {
		for (int i=0; i<cc_size; i++) {
			Constructor* c = this->constructors[i];
			SafeDelete(c);
		}
	}

	this->constructors.release();

	// release Method
	size_t m_size = this->methods.size();

	if (m_size > 0) {
		for (int i=0; i<m_size; i++) {
			Method* m = this->methods[i];
			SafeDelete(m);
		}
	}

	this->methods.release();
	
	// release Field
	size_t f_size = this->fields.size();

	if (f_size > 0) {
		for (int i=0; i<f_size; i++) {
			Field* f = this->fields[i];
			SafeDelete(f);
		}
	}
}

const char* Class::getPackageName() {
	return this->packageName;
}

const char* Class::getSimpleName() {
	return this->name + strlen(this->packageName) + 2;
}

Object* Class::newInstance() {
	Constructor* c = this->getConstructor();

	if (c != null) {
		return c->newInstance();
	}

	return null;
}

Object* Class::newInstance(const Array<Object*>& args) {
	Constructor* c = this->getConstructor();

	if (c != null) {
		return c->newInstance();
	}

	return null;
}



dg_boolean is_type_array_equals(Array<Type*>& pta1, Array<Type*>& pta2) {
	if (pta1.size() == pta2.size()) {
		size_t cc_size = pta1.size();
		if (cc_size == 0) {
			return dg_true;
		}

		for(int i=0; i<cc_size; i++) {
			Type* t1 = pta1[i];
			Type* t2 = pta2[i];

			if (t1!=null && t2!=null 
				&& t1->equals(t2)) {
				return dg_true;
			}
		}
	}

	return dg_false;
}

Constructor* Class::getConstructor(const Array<Type*>& parameterTypes) {
	size_t cc_size = this->constructors.size();

	Array<Type*> pt_in = parameterTypes;

	if (cc_size > 0) {
		for (int i=0; i<cc_size; i++) {
			Constructor* c = this->constructors[i];
			Array<Type*> cpt = c->getParameterTypes();

			if (is_type_array_equals(cpt, pt_in)) {
				return c;
			}
		}
	}

	return null;
}

Constructor* Class::getConstructor() {
	Array<Type*> empty_array;
	return this->getConstructor(empty_array);
}

Method* Class::getMethod(const char* methodName, const Array<Type*>& parameterTypes) {
	size_t m_size = this->methods.size();

	Array<Type*> pt_in = parameterTypes;

	if (m_size > 0) {
		for (int i=0; i<m_size; i++) {
			Method* m = this->methods[i];
			const char* m_name = m->getName();
			Array<Type*> cpt = m->getParameterTypes();

			if (strcmp(m_name, methodName)==0x0 
				&& is_type_array_equals(cpt, pt_in)) {
				return m;
			}
		}
	}

	return null;
}

Method* Class::getMethod(const char* methodName) {
	Array<Type*> empty_array;
	return this->getMethod(methodName, empty_array);
}

// ------------------------------------------------------------------
void Class::setConstructors(const Array<Constructor*>& constructors) {
	this->constructors = constructors;
}

void Class::setMethods(const Array<Method*>& methods){
	this->methods = methods;
}

void Class::setFields(const Array<Field*>& fields){
	this->fields = fields;
}


/*
Class::Class() {

	mpTypeInfo = &typeid(Type);
	mSize=sizeof(Type);
	this->name=L"";
	this->fields=null;
	this->methods=null;
	this->constructor=new TemplateConstructor<Type>();

	if(LM::GetInstance()->containsClass(this->getName())) {
		this->mergeWith(LM::GetInstance()->getClassForName(this->getName()));
	}

}
*/


/*
template<class Type>
Class<Type>::Class(const type_info* typeInfo)
{
	mpTypeInfo=typeInfo;
	mSize=1024;
	this->name=L"";
	this->fields=null;
	this->methods=null;
	this->constructor=new TemplateConstructor<Type>();

	if(LM::GetInstance()->containsClass(this->getName())) {
		this->mergeWith(LM::GetInstance()->getClassForName(this->getName()));
	}
}
*/

/*
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

*/