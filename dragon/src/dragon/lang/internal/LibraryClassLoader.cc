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
 * Created:     2013/07/26
 **********************************************************************/


#include <dragon/lang/internal/LibraryClassLoader.h>
#include <dragon/lang/Class.h>
#include <dragon/lang/internal/platform.h>

#include <stdlib.h>

Import dragon::lang;
Import dragon::lang::reflect;
Import dragon::lang::internal;

LibraryClassLoader::LibraryClassLoader(){
	this->librarys = new LibraryList();
}

LibraryClassLoader::LibraryClassLoader(const char* libPath) {
	this->load(libPath);	
}

LibraryClassLoader::~LibraryClassLoader() {
	while (!this->librarys->empty()){
		Library* lib = this->librarys->back();
		this->librarys->pop_back();
		SafeDelete(lib);
	}

	SafeDelete(this->librarys);
}

void LibraryClassLoader::load(const char* libPath) {
	Library* lib = new Library(libPath);
	lib->resolve();
	this->librarys->push_back(lib);
}

const char* next_param_token(const char* str, int offset, size_t len) {
	int kk_count = 0;

	for(int i=offset; i<offset + len; i++) {
		char ch = str[i];
		if (ch == '<') {
			kk_count++;
		} else if (ch == '>') {
			kk_count--;
		} else if (ch == ',') {
			if (kk_count == 0) {
				return str + i;
			}
		}
	}

	return NULL;
}

Array<Type*> make_param_types(const char* sign, const char* className, const char* methodName) {
	size_t sign_len = strlen(sign);

	int offset = strlen(className) + strlen(methodName) + 3;
	size_t len = sign_len;

	Type** types = NULL;
	int t_count = 0;

	const char* token = NULL;

	do {
		len = sign_len - offset;
		token = next_param_token(sign, offset, len);

		if (token != NULL) {
			len = token - sign - offset;
		} else {
			len = len - 1;
		}

		Type* type = null;

		if (len != 0) {
			type = new Type(sign, offset, len);
		} else {
			break;
		}

		types = (Type**)realloc(types, sizeof(Type*)*(t_count+0x1));
		types[t_count++] = type;

		offset = offset + len + 2;
	} while(token != NULL);

	if (t_count == 1 && strcmp("void", types[0]->getName()) == 0x0) {
		SafeDelete(types[0]);
		SafeFree(types);

		return Array<Type*>();
	} else {
		return Array<Type*>(types, t_count);
	}
}

dg_boolean is_constructor(Class* clazz, Library::ExportSymbol* es) {
	const char* name = clazz->getName();
	const char* simpleName = clazz->getSimpleName();

	char* sign = Demangle(es->symbol);

	size_t len = strlen(simpleName);
	int offset = strlen(name) + 2;

	dg_boolean ret = dg_false;

	char* bb = sign + offset;
	if (offset + len <= strlen(sign) 
		&& memcmp(sign + offset, simpleName, len)==0x0
		&& bb[len] == '(') {
		ret = true;
	}

	free(sign);

	return ret;
}


Constructor* make_constructor(Class* clazz, Library::ExportSymbol* es) {
	const char* name = clazz->getName();
	const char* simpleName = clazz->getSimpleName();

	char* sign = Demangle(es->symbol);
	Array<Type*> parameterTypes = make_param_types(sign, name, simpleName);
	
	free(sign);

	return new Constructor(clazz, simpleName, es->address, parameterTypes);
}

dg_boolean is_method(Class* clazz, const char* methodName, Library::ExportSymbol* es) {
	const char* name = clazz->getName();

	char* sign = Demangle(es->symbol);
	size_t sign_size = strlen(sign);

	size_t len = strlen(methodName);
	int offset = strlen(name) + 2;

	dg_boolean ret = dg_false;

	char* bb = sign + offset;
	if (offset + len <= sign_size
		&& memcmp(sign + offset, methodName, len)==0x0
		&& bb[len] == '(') {
		ret = true;
	}

	free(sign);

	return ret;
}

Method* make_method(Class* clazz, const char* methodName, Library::ExportSymbol* es) {
	const char* name = clazz->getName();

	char* sign = Demangle(es->symbol);

	Array<Type*> parameterTypes = make_param_types(sign, name, methodName);
	
	free(sign);

	return new Method(clazz, methodName, es->address, parameterTypes);
}

Class* LibraryClassLoader::defineClass(const char* name, Library::NameSpace* ns) {
	const ClassLoader* classLoader = this;
	
	char* simpleName = new char[strlen(ns->name) + 1];
	strcpy(simpleName, ns->name);

	size_t p_size = strlen(name) - strlen(simpleName) - 2;
	char* packageName = new char[p_size + 1];
	memcpy(packageName, name, p_size);
	packageName[p_size] = '\0';
	delete[] simpleName;

	Class* clazz = createClass(this, packageName, name);
	delete[] packageName;

	Constructor** constructors = NULL;
	size_t cc_count = 0;

	Method** methods = NULL;
	size_t m_count = 0;

	Field** fields = NULL;
	size_t f_count = 0;

	size_t es_size = ns->symbolCount;

	for (int i=0; i<es_size; i++) {
		Library::ExportSymbol* es = &ns->symbols[i];

		if (is_constructor(clazz, es)) {
			Constructor* c = make_constructor(clazz, es);
			constructors = (Constructor**)realloc(constructors, sizeof(Constructor*)*(cc_count+0x1));
			constructors[cc_count++] = c;
		}
	}

	Library::NameSpace* p = ns->spaces;

	while(p != NULL) {
		es_size = p->symbolCount;

		for (int i=0; i<es_size; i++) {
			Library::ExportSymbol* es = &p->symbols[i];

			if (is_method(clazz, p->name, es)) {
				Method* m = make_method(clazz, p->name, es);
				methods = (Method**)realloc(methods, sizeof(Method*)*(m_count+0x1));
				methods[m_count++] = m;
			}
		}

		p = p->next;
	}

	setClassConstructors(clazz, Array<Constructor*>(constructors, cc_count));
	setClassMethods(clazz, Array<Method*>(methods, m_count));

	return clazz;
}

Class* LibraryClassLoader::findClass(const char* name){
	for (Iterator it = this->librarys->begin() ; it != this->librarys->end(); ++it) {
		Library* lib = *it;
		Library::NameSpace* ns = lib->findClassDefine(name);

		if (ns != NULL) {
			return this->defineClass(name, ns);
		}
	}

	return null;
}