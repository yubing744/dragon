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

#include <cxxabi.h>

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#include <errno.h>

#include <string.h>
#include <stdlib.h>

#include <sys/time.h>

#include <string>
#include <map>

#include <dragon/lang/internal/platform_posix.h>

Import std;
Import dragon::lang::internal;

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Some Help Func
//

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

static int LibAdressFlag = 0;

const char* dragon::lang::internal::GetLocalLibPath() {
	Dl_info info;
	dladdr(NULL, &info);
	return info.dli_fname;
}

const char* dragon::lang::internal::GetDragonLibPath() {
	Dl_info info;
	dladdr((void*)(&SymTestBean::classLocationFlag), &info);
	return info.dli_fname;
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


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Time
// 

/**
 * get the system time
 * 
 * @return [description]
 */
dg_long dragon::lang::internal::GetSystemTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((dg_long) tv.tv_sec) * 1000000 + tv.tv_usec;
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Lock
// 

/**
 * init a mutex object
 * 
 * @return [description]
 */
void* dragon::lang::internal::InitMutex() {
	pthread_mutex_t* pmutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(pmutex, &attr);

    return pmutex;
}

/**
 *  lock the mutex
 * 
 * @return [description]
 */
void dragon::lang::internal::LockMutex(void* mutex) {
	pthread_mutex_t* pmutex = (pthread_mutex_t*)mutex;
	pthread_mutex_lock(pmutex);
}

/**
 *  try lock the mutex
 * 
 * @return [description]
 */
bool dragon::lang::internal::TryLockMutex(void* mutex) {
	pthread_mutex_t* pmutex = (pthread_mutex_t*)mutex;

	int result = pthread_mutex_trylock(pmutex);
    // Return false if the lock is busy and locking failed.
    if (result == EBUSY) {
      	return false;
    }

    return true;
}

/**
 *  unlock the mutex
 * 
 * @return [description]
 */
void dragon::lang::internal::UnlockMutex(void* mutex) {
	pthread_mutex_t* pmutex = (pthread_mutex_t*)mutex;
	pthread_mutex_unlock(pmutex);
}

/**
 * free mutex object
 * 
 * @return [description]
 */
void dragon::lang::internal::FreeMutex(void* mutex) {
	pthread_mutex_t* pmutex = (pthread_mutex_t*)mutex;
	pthread_mutex_destroy(pmutex);

	SafeFree(pmutex);
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Thread
// 

// mine thread handle
typedef struct ThreadHandle{
  	pthread_t thread;
};

// thread entry func
typedef void*(*ThreadEntryFunc)(void*);

void* dragon::lang::internal::CreateThread(int stackSize, void* target, void* entryFunc) {
	struct ThreadHandle* handle = (struct ThreadHandle*)malloc(sizeof(struct ThreadHandle*));

 	pthread_attr_t* attr_ptr = NULL;
	pthread_attr_t attr;

  	if (stackSize > 0) {
    	pthread_attr_init(&attr);
    	pthread_attr_setstacksize(&attr, static_cast<size_t>(stackSize));
    	attr_ptr = &attr;
  	}

  	ThreadEntryFunc func = void_cast<ThreadEntryFunc>(entryFunc);
  	int ret = pthread_create(&handle->thread, attr_ptr, func, target);

  	if (ret != 0) {
  		printf("can't create thread: %s\n", strerror(ret));
  		return NULL;
  	}

  	return handle;
}

void dragon::lang::internal::JoinThread(void* threadHandle) {
	struct ThreadHandle* handle = (struct ThreadHandle*)threadHandle;

	pthread_join(handle->thread, NULL);
}

void dragon::lang::internal::YieldThread() {
	sched_yield();
}

void dragon::lang::internal::CloseThread(void* threadHandle) {
	struct ThreadHandle* handle = (struct ThreadHandle*)threadHandle;
  	SafeFree(handle);	
}

void dragon::lang::internal::SleepThread(long millisecs) {
    struct timespec time;

    time.tv_sec = millisecs / 1000;
    time.tv_nsec = (millisecs % 1000) * 1000000;

    nanosleep(&time, NULL);
}

