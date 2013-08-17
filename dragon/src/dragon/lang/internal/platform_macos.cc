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

#include <dlfcn.h>
#include <mach/mach.h>
#include <mach-o/dyld.h>
#include <mach-o/nlist.h>
#include <mach-o/ldsyms.h>
#include <cxxabi.h>

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

const static size_t INT_ARGS_COUNT = 5;
const static size_t FLOATING_ARGS_COUNT = 8;

void dragon::lang::internal::Invoke(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	size_t int_result = NULL;
	double sse_result = 0.0;

	void* int_args[INT_ARGS_COUNT];
	void* floating_args[FLOATING_ARGS_COUNT];
	void** stack_args = NULL;

	size_t ic = 0;
	size_t fc = 0;
	size_t sc = 0;

	for (int i=0; i<argc; i++) {
		ParamInfo param = argv[i];
		int category = param.category;
		size_t size = param.size;
		void* val = param.value;

		if (category == CATEGORY_SSE) {
			if (fc < FLOATING_ARGS_COUNT) {
				floating_args[fc++] = val;
			} else {
				stack_args = (void**)realloc(stack_args, CPU_BYTE_LEN * (sc + 1));
				stack_args[sc++] = val;
			}
		} else if (category == CATEGORY_INTEGER) {
			if (ic < INT_ARGS_COUNT) {
				int_args[ic++] = val;
			} else {
				stack_args = (void**)realloc(stack_args, CPU_BYTE_LEN * (sc + 1));
				stack_args[sc++] = val;
			}
		} else if (category == CATEGORY_MEMORY) {
			size_t w_ss = size / sizeof(void*);
			stack_args = (void**)realloc(stack_args, CPU_BYTE_LEN * (sc + w_ss));
			memcpy(stack_args + sc, val, size);
			sc+=w_ss;
		}
	}


	if (sc > 0) {
		__asm__ __volatile__("subq %0, %%rsp"::"a"(sc * CPU_BYTE_LEN));

		size_t i = 0;
		while (i < sc) {
			__asm__ __volatile__("mov %0, %%rbx"::"a"(i));
			__asm__ __volatile__("mov %0, (%%rsp, %%rbx, 8)"::"a"(stack_args[i]));
			i++;
		}
	}

	if (fc > 0) {
		__asm__ __volatile__("movsd %0, %%xmm0"::"m"(floating_args[0]));
		__asm__ __volatile__("movsd %0, %%xmm1"::"m"(floating_args[1]));
		__asm__ __volatile__("movsd %0, %%xmm2"::"m"(floating_args[2]));
		__asm__ __volatile__("movsd %0, %%xmm3"::"m"(floating_args[3]));
		__asm__ __volatile__("movsd %0, %%xmm4"::"m"(floating_args[4]));
		__asm__ __volatile__("movsd %0, %%xmm5"::"m"(floating_args[5]));
		__asm__ __volatile__("movsd %0, %%xmm6"::"m"(floating_args[6]));
		__asm__ __volatile__("movsd %0, %%xmm7"::"m"(floating_args[7]));
	}

	if (ic > 0) {
		__asm__ __volatile__("mov %0, %%rsi"::"a"(int_args[0]));
		__asm__ __volatile__("mov %0, %%rdx"::"a"(int_args[1]));
		__asm__ __volatile__("mov %0, %%rcx"::"a"(int_args[2]));
		__asm__ __volatile__("mov %0, %%r8"::"a"(int_args[3]));
		__asm__ __volatile__("mov %0, %%r9"::"a"(int_args[4]));
	}

	__asm__ __volatile__("mov %0, %%rdi"::"a"(pthis));
	__asm__ __volatile__("call *%0"::"a"(func));
	__asm__ __volatile__("mov %%rax, %0":"=a"(int_result));
	__asm__ __volatile__("movsd %%xmm0, %0":"=m"(sse_result));

	if (sc > 0) {
		free(stack_args);
		__asm__ __volatile__("addq %0, %%rsp"::"a"(sc * CPU_BYTE_LEN));
	}

	if (ret->category == CATEGORY_INTEGER) {
		ret->value = cast_void<size_t>(int_result);
	} else if (ret->category == CATEGORY_SSE) {
		ret->value = cast_void<double>(sse_result);
	}
}

void* dragon::lang::internal::Invoke(void* pthis, void* func, ParamInfo *argv, int argc) {
	ReturnInfo ret("void*");
	Invoke(pthis, func, &ret, argv, argc);
	return ret.getValue<void*>();
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

static int LibAdressFlag = 0;

const char* find_image_path_by_name(const char* name);

const char* dragon::lang::internal::GetLocalLibPath() {
	Dl_info info;
	dladdr(NULL, &info);
	return info.dli_fname;
}

const char* dragon::lang::internal::GetDragonLibPath() {
	const char* local_lib_path = find_image_path_by_name("libdragon.dylib");
	return local_lib_path;
}

void dragon::lang::internal::ShowLocalLibInfo() {
	Dl_info info;

	// 1. get static var's address
	dladdr((void*)(&SymTestBean::classLocationFlag), &info);
	printf("lib dli_fname: %s\n", info.dli_fname);
	printf("lib dli_sname: %s\n", info.dli_sname);

	// 2. get member method's address
	SymTestBean_TestByte_MemberMethod setBytePtr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&setBytePtr)), &info);
	void* handle = dlopen(info.dli_fname, RTLD_NOW);

	void* setBytePtr2 = dlsym(handle, "_ZN6dragon4lang8internal11SymTestBean4testEc");
	void* setBytePtr1 = reinterpret_cast<void*>(*(void**)(&setBytePtr));

	printf("the two address %d %d\n", setBytePtr1, setBytePtr2);
	dlclose(handle);
}

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// SymbolMangling Implements 
//

static map<string, string> symbol_code_map;
static bool is_symbol_code_map_init = false;

string query_prefix_symbol() {
	Dl_info info;
	dladdr((void*)(&SymTestBean::classLocationFlag), &info);
	string symbol(info.dli_sname);

	size_t p1 = symbol.find("6dragon");
	if (p1 != string::npos) {
		return symbol.substr(0, p1);
	}
	
	return string();	
}

string query_name_end_symbol() {
	Dl_info info;
	dladdr((void*)(&SymTestBean::classLocationFlag), &info);
	string symbol(info.dli_sname);

	string flag("classLocationFlag");
	size_t p1 = symbol.find(flag);
	if (p1 != string::npos) {
		size_t begin = p1 + flag.length();
		return symbol.substr(begin, symbol.length() - begin);
	}
	
	return string();	
}

string parse_basic_type_symbol(const char* sname) {
	string flag("test");
	string symbol(sname);

	size_t p1 = symbol.find(flag);
	if (p1 != string::npos) {
		size_t begin = p1 + flag.length() + 1;
		return symbol.substr(begin, symbol.length() - begin);
	}
	
	return string();	
}

string query_byte_symbol(){
	Dl_info info;
	SymTestBean_TestByte_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}

string query_short_symbol(){
	Dl_info info;
	SymTestBean_TestShort_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}

string query_int_symbol(){
	Dl_info info;
	SymTestBean_TestInt_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}

string query_long_symbol(){
	Dl_info info;
	SymTestBean_TestLong_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}

string query_float_symbol(){
	Dl_info info;
	SymTestBean_TestFloat_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}

string query_double_symbol(){
	Dl_info info;
	SymTestBean_TestDouble_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}

string query_char_symbol(){
	Dl_info info;
	SymTestBean_TestChar_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}

string query_boolean_symbol(){
	Dl_info info;
	SymTestBean_TestBoolean_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}

string query_void_symbol(){
	Dl_info info;
	SymTestBean_TestVoid_MemberMethod method_ptr = &SymTestBean::test;
	dladdr(reinterpret_cast<void*>(*(void**)(&method_ptr)), &info);

	return parse_basic_type_symbol(info.dli_sname);
}


void mangling_init(){
	symbol_code_map.clear();

	symbol_code_map["prefix"] =  query_prefix_symbol();
	symbol_code_map["name_end"] = query_name_end_symbol();

	symbol_code_map["dg_byte"] = query_byte_symbol();
	symbol_code_map["byte"] = symbol_code_map["dg_byte"];

	symbol_code_map["dg_short"] = query_short_symbol();
	symbol_code_map["short"] = symbol_code_map["dg_short"];

	symbol_code_map["dg_int"] = query_int_symbol();
	symbol_code_map["int"] = symbol_code_map["dg_int"];

	symbol_code_map["dg_long"] = query_long_symbol();
	symbol_code_map["long"] = symbol_code_map["dg_long"];

	symbol_code_map["dg_float"] = query_float_symbol();
	symbol_code_map["float"] = symbol_code_map["dg_float"];

	symbol_code_map["dg_double"] = query_double_symbol();
	symbol_code_map["double"] = symbol_code_map["dg_double"];

	symbol_code_map["dg_char"] = query_char_symbol();
	symbol_code_map["char"] = symbol_code_map["dg_char"];

	symbol_code_map["dg_boolean"] = query_boolean_symbol();
	symbol_code_map["bool"] = symbol_code_map["dg_boolean"];

	symbol_code_map["dg_void"] = query_void_symbol();
	symbol_code_map["void"] = symbol_code_map["dg_void"];
	symbol_code_map[""] = symbol_code_map["dg_void"];
}

///////////////////////////////////////////////////////////

void mangling_sub_name(vector<string>& sb, string& sig) {
	char buf[100];
	size_t len = sig.length();
	sprintf(buf, "%d", len);

	sb.push_back(buf);
	sb.push_back(sig);
}

void mangling_clear_name(vector<string>& sb, string& sig) {
	string flag("::");
	size_t p1 = sig.find(flag);

	if (p1 != string::npos) {
		string name_left_sig = sig.substr(0, p1);
		mangling_sub_name(sb, name_left_sig);

		string name_right_sig = sig.substr(p1 + flag.length(), sig.length() - p1);
		mangling_clear_name(sb, name_right_sig);
	} else {
		mangling_sub_name(sb, sig);
	}
}

void mangling_template_args(vector<string>& sb, string& sig) {

}

string trim_all_blank(string& sig) {
	return sig;
}

size_t find_match_next_pair_pos(string& str, size_t pos, char a1, char a2) {
	int count = 1;

	for(size_t i=pos; i<str.length();i++) {
		char ch = str[i];

		if (ch == a1) {
			count++;
		} else if (ch == a2) {
			count--;
		}

		if (count == 0) {
			return i;
		}
	}

	return -1;
}

void mangling_name(vector<string>& sb, string& sig) {
	size_t p1 = sig.find("<");

	if (p1 != string::npos) {
		size_t p2 = find_match_next_pair_pos(sig, p1, '<', '>');

		string name_left_sig = sig.substr(0, p1);
		mangling_clear_name(sb, name_left_sig);

		if (p2 != string::npos && p2 > p1) {
			string template_sig = sig.substr(p1, p2 - p1);
			mangling_template_args(sb, template_sig);

			string name_right_sig = sig.substr(p2, sig.length() - p2);
			mangling_name(sb, name_right_sig);
		} else {
			sb.push_back("(error: the template args '<' and '>' not match)");
		}
	} else {
		mangling_clear_name(sb, sig);
	}
}

void mangling_arg(vector<string>& sb, string& sig) {
	map<string, string>::iterator it = symbol_code_map.find(sig);

	if (it != symbol_code_map.end()) {
		sb.push_back(it->second);
	} else {
		sb.push_back("(error: not support type " + sig + ")");
	}
}

void mangling_args(vector<string>& sb, string& sig) {
	size_t p1 = sig.find(",");

	if (p1 != string::npos) {
		string arg_left_sig = sig.substr(0, p1);
		mangling_arg(sb, arg_left_sig);

		string arg_right_sig = sig.substr(p1, sig.length() - p1);
		mangling_args(sb, arg_right_sig);
	} else {
		mangling_arg(sb, sig);
	}
}

void mangling_end_name(vector<string>& sb) {
	sb.push_back(symbol_code_map["name_end"]);
}

void mangling_check_special_name(vector<string>& sb){
	if (sb.size() >= 4) {
		string class_name = sb[sb.size() -3];
		string func_name = sb[sb.size() - 1];

		if (class_name == func_name) {
			sb[sb.size() - 2] = "C";
			sb[sb.size() - 1] = "1";
		}
	}
}

string dragon::lang::internal::Mangling(const char* fun_signature) {
	vector<string> sb;

	string sig(fun_signature);

	if (!is_symbol_code_map_init) {
		mangling_init();
		is_symbol_code_map_init = true;
	}

	sig = trim_all_blank(sig);

	sb.push_back(symbol_code_map["prefix"]);

	size_t p1 = sig.find("(");

	if (p1 != string::npos) {
		string nameSig = sig.substr(0, p1);
		mangling_name(sb, nameSig);
		mangling_check_special_name(sb);
		mangling_end_name(sb);

		size_t p2 = sig.find(")", p1);

		if (p1 != string::npos && p2 > p1) {
			string paramSig = sig.substr(p1 + 1, p2 - p1 - 1);
			mangling_args(sb, paramSig);
		} else {
			sb.push_back("(error: the '(' and ')' not match)");
		}
	} else {
		mangling_name(sb, sig);
		mangling_end_name(sb);
	}


	return Join(sb, "");
}

char* dragon::lang::internal::Demangle(const char* symbol) {
	int status=0;
	return abi::__cxa_demangle(symbol, 0, 0, &status);
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Library export Function
// 

void* dragon::lang::internal::GetFuncAddress(const char* libPath, const char* signature) {
	string symbol = Mangling(signature);

	void* handle = dlopen(libPath, RTLD_NOW);
	void* addr = dlsym(handle, symbol.c_str());
	dlclose(handle);

	return addr;	
}

void* dragon::lang::internal::GetFuncAddress(const char* signature) {
	Dl_info info;
	dladdr((void*)(&SymTestBean::classLocationFlag), &info);
	return GetFuncAddress(info.dli_fname, signature);
}


