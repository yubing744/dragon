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


#include <dragon/lang/ClassLoader.h>
#include <dragon/lang/Class.h>
#include <dragon/lang/internal/SystemClassLoader.h>
#include <dragon/lang/ClassNotFoundException.h>

Import dragon::lang;
Import dragon::lang::internal;

static ClassLoader* systemClassLoader = null;

ClassLoader* ClassLoader::getSystemClassLoader() {
	if (systemClassLoader == null) {
		systemClassLoader = new SystemClassLoader();
	}

	return systemClassLoader;
}

Class* ClassLoader::createClass(const ClassLoader* classLoader, 
		const char* packageName, const char* simpleName, size_t size) {
	return new Class(classLoader, packageName, simpleName, size);
}

void ClassLoader::setClassConstructors(Class* clazz, const Array<Constructor*>& constructors) {
	clazz->setConstructors(constructors);
}

void ClassLoader::setClassMethods(Class* clazz, const Array<Method*>& methods){
	clazz->setMethods(methods);
}

void ClassLoader::setClassFields(Class* clazz, const Array<Field*>& fields){
	clazz->setFields(fields);
}

ClassLoader::ClassLoader() {
	this->parent = null;
	this->loaded = new ClassMap();
}

ClassLoader::ClassLoader(ClassLoader* parent) {
	this->parent = parent;
	this->loaded = new ClassMap();
}


ClassLoader::~ClassLoader() {
	for(Iterator it=this->loaded->begin();it!=this->loaded->end();it++) { 
		SafeDelete(it->second);
	}

	SafeDelete(this->loaded);
}

ClassLoader* ClassLoader::getParent(){
	return this->parent;
}

Class* ClassLoader::loadClass(const char* name) {
	return this->loadClass(name, false);
}

Class* ClassLoader::loadClass(const char* name, dg_boolean resolve){
	Class* result = this->findLoadedClass(name);

	if (result == null && parent != null) {
		result = parent->loadClass(name);
	}

	if (result == null) {
		result = this->findClass(name);
		
		if (result != null) {
			this->loaded->insert(ClassMap::value_type(name, result));
		}
	}

	if (result != null && resolve) {
		this->resolveClass(result);
	}

	if (result != null) {
		return result;
	}

	throw new ClassNotFoundException(name);
}

Class* ClassLoader::findLoadedClass(const char* name){
	Iterator it = this->loaded->find(name);

	if(it != this->loaded->end()) {
		return it->second;
	} 

	return null;
}

void ClassLoader::resolveClass(Class* c) {

}
