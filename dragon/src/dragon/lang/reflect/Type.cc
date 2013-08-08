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

#include <string>
#include <map>

Import std;
Import dragon::lang::reflect;

static map<string, size_t> type_size_map;
static bool is_init_primitive_type_size_map = false;

static void init_primitive_type_size_map() {
	//c++ primitive
	type_size_map["char"] = sizeof(char);
	type_size_map["short"] = sizeof(short);
	type_size_map["int"] = sizeof(int);
	type_size_map["long"] = sizeof(long);
	type_size_map["long long"] = sizeof(long long);
	type_size_map["float"] = sizeof(float);
	type_size_map["double"] = sizeof(double);
	type_size_map["bool"] = sizeof(bool);

	type_size_map["unsigned short"] = sizeof(unsigned short);
	type_size_map["unsigned int"] = sizeof(unsigned int);
	type_size_map["unsigned long long"] = sizeof(unsigned long long);

	type_size_map["size_t"] = sizeof(size_t);
	type_size_map["void*"] = sizeof(void*);

	//dragon lib primitive
	type_size_map["dg_short"] = sizeof(dg_short);
	type_size_map["dg_int"] = sizeof(dg_int);
	type_size_map["dg_long"] = sizeof(dg_long);
	type_size_map["dg_float"] = sizeof(dg_float);
	type_size_map["dg_double"] = sizeof(dg_double);
	type_size_map["dg_char"] = sizeof(dg_char);
	type_size_map["dg_boolean"] = sizeof(dg_boolean);

	type_size_map["dg_ushort"] = sizeof(dg_ushort);
	type_size_map["dg_uint"] = sizeof(dg_uint);
	type_size_map["dg_ulong"] = sizeof(dg_ulong);
}

Type::Type(const char* name) {
	size_t n_size = strlen(name);
	char* buf = (char*)malloc(n_size + 1);
	strcpy(buf, name);
	this->name = buf;
}

Type::Type(const char* name, int offset, size_t count) {
	char* buf = (char*)malloc(count + 1);
	memcpy(buf, name + offset, count);
	buf[count] = '\0';
	this->name = buf;
}

Type::~Type() {
	SafeFree(this->name);
}

const char* Type::getName() {
	return this->name;
}

size_t Type::getSize() {
	map<string, size_t>::iterator it = type_size_map.find(this->name);

	if (it != type_size_map.end()) {
		return it->second;
	} else {
		return sizeof(void*);
	}
}

dg_boolean Type::equals(const Type* type) {
	if (strcmp(this->name, type->name) == 0x0) {
		return dg_true;
	}

	return dg_false;
}