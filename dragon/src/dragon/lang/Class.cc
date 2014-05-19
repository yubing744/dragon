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
		const char* packageName, const char* name, size_t size) 
	:Type(name, size), classLoader(classLoader) 
{
	size_t p_size = strlen(packageName);
	char* buf = (char*)malloc(p_size + 1);
	strcpy(buf, packageName);
	this->packageName = buf;
}

Class::Class(const ClassLoader* classLoader, 
		const char* packageName, const char* name, size_t size,
		const Array<Constructor*>& constructors, const Array<Method*>& methods,
		const Array<Field*>& fields) 
	:Type(name, size), classLoader(classLoader), constructors(constructors), methods(methods), fields(fields) 
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

	//REDO this->constructors.release();

	// release Method
	size_t m_size = this->methods.size();

	if (m_size > 0) {
		for (int i=0; i<m_size; i++) {
			Method* m = this->methods[i];
			SafeDelete(m);
		}
	}

	//REDO this->methods.release();
	
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