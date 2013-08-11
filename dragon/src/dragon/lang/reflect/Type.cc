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
 * Created:     2013/08/04
 **********************************************************************/


#include <dragon/lang/reflect/Type.h>

#include <stdlib.h>
#include <string.h>

#include <dragon/lang/internal/platform.h>

Import std;
Import dragon::lang::reflect;
Import dragon::lang::internal;

Type::Type(const char* name) {
	size_t n_size = strlen(name);
	char* buf = (char*)malloc(n_size + 1);
	strcpy(buf, name);
	this->name = buf;

	this->size = GetBasicTypeSize(name);
}

Type::Type(const char* name, int offset, size_t count) {
	char* buf = (char*)malloc(count + 1);
	memcpy(buf, name + offset, count);
	buf[count] = '\0';
	this->name = buf;

	this->size = GetBasicTypeSize(name);
}

Type::~Type() {
	SafeFree(this->name);
}

const char* Type::getName() {
	return this->name;
}

size_t Type::getSize() {
	return this->size;
}

dg_boolean Type::equals(const Type* type) {
	if (strcmp(this->name, type->name) == 0x0) {
		return dg_true;
	}

	return dg_false;
}