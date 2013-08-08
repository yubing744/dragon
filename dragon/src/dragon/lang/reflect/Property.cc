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
 * Created:     2013/07/25
 **********************************************************************/

#include <dragon/lang/reflect/Property.h>

#include <ctype.h>
#include <string>

Import std;
Import dragon::lang::reflect; 

static char* build_setter_method_name(const char* name) {
	string prefix("set");
	string prop_name(name);

	if (prop_name.length() > 0) {
		char initial = prop_name[0];
		prop_name[0] = toupper(initial);
	}

	string setter_name = prefix + prop_name;
	return setter_name.c_str();
}

static char* build_getter_method_name(const char* name) {
	string prefix("get");
	string prop_name(name);

	if (prop_name.length() > 0) {
		char initial = prop_name[0];
		prop_name[0] = toupper(initial);
	}

	string setter_name = prefix + prop_name;
	return setter_name.c_str();
}

Property::Property(const Class* clazz, const char* name, const Class* type)
	:Field(clazz, name, type)
{
	
	this->setter = clazz->getDeclaredMethod(build_setter_method_name(name), type);
	this->getter = clazz->getDeclaredMethod(build_getter_method_name(name));
}

Method* Property::getGetter() {
	return this->getter;
}

Method* Property::getSetter() {
	return this->setter;
}
