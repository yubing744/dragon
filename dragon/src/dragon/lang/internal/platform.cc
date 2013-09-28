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
 * Created:     2013/03/31
 **********************************************************************/

#include <string>
#include <map>

#include <dragon/lang/internal/platform.h>

Import std;
Import dragon::lang::internal;

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
//
// Some Help Func
//

// type size
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

size_t dragon::lang::internal::GetBasicTypeSize(const char* name) {
	if (!is_init_primitive_type_size_map) {
		init_primitive_type_size_map();
		is_init_primitive_type_size_map = true;
	}

	map<string, size_t>::iterator it = type_size_map.find(name);

	if (it != type_size_map.end()) {
		return it->second;
	} else {
		return sizeof(void*);
	}
}

// type category
static map<string, int> type_category_map;
static bool is_init_primitive_type_category_map = false;

static void init_primitive_type_categroy_map() {
	//c++ primitive
	type_category_map["char"] = CATEGORY_INTEGER;
	type_category_map["short"] = CATEGORY_INTEGER;
	type_category_map["int"] = CATEGORY_INTEGER;
	type_category_map["long"] = CATEGORY_INTEGER;
	type_category_map["long long"] = CATEGORY_INTEGER;
	type_category_map["float"] = CATEGORY_SSE;
	type_category_map["double"] = CATEGORY_SSE;
	type_category_map["bool"] = CATEGORY_INTEGER;

	type_category_map["unsigned short"] = CATEGORY_INTEGER;
	type_category_map["unsigned int"] = CATEGORY_INTEGER;
	type_category_map["unsigned long long"] = CATEGORY_INTEGER;

	type_category_map["size_t"] = CATEGORY_INTEGER;
	type_category_map["void*"] = CATEGORY_INTEGER;

	//dragon lib primitive
	type_category_map["dg_short"] = CATEGORY_INTEGER;
	type_category_map["dg_int"] = CATEGORY_INTEGER;
	type_category_map["dg_long"] = CATEGORY_INTEGER;
	type_category_map["dg_float"] = CATEGORY_SSE;
	type_category_map["dg_double"] = CATEGORY_SSE;
	type_category_map["dg_char"] = CATEGORY_INTEGER;
	type_category_map["dg_boolean"] = CATEGORY_INTEGER;

	type_category_map["dg_ushort"] = CATEGORY_INTEGER;
	type_category_map["dg_uint"] = CATEGORY_INTEGER;
	type_category_map["dg_ulong"] = CATEGORY_INTEGER;
}

int dragon::lang::internal::GetBasicTypeCategory(const char* name) {
	if (!is_init_primitive_type_category_map) {
		init_primitive_type_categroy_map();
		is_init_primitive_type_category_map = true;
	}

	map<string, int>::iterator it = type_category_map.find(name);

	if (it != type_category_map.end()) {
		return it->second;
	} else {
		return CATEGORY_MEMORY;
	}
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Symbol Mangling and Demangle Function
// 

// lib export class symbol test
dg_int SymTestBean::classLocationFlag = 0;

SymTestBean::SymTestBean(){
	this->testVal = 0;
}

SymTestBean::SymTestBean(dg_int testVal) {
	this->testVal = testVal;
}

SymTestBean::~SymTestBean(){}

void SymTestBean::test(dg_byte byteVal){}
void SymTestBean::test(dg_short shortVal){}
void SymTestBean::test(dg_int intVal){}
void SymTestBean::test(dg_long longVal){}
void SymTestBean::test(dg_float floatVal){}
void SymTestBean::test(dg_double doubleVal){}
void SymTestBean::test(dg_char charVal){}
void SymTestBean::test(dg_boolean booleanVal){}
void SymTestBean::test(SymTestBean* bean){}
void SymTestBean::test(){}

dg_int SymTestBean::getTestVal() {
	return this->testVal;
}

void SymTestBean::setTestVal(dg_int val) {
	this->testVal = val;
}


