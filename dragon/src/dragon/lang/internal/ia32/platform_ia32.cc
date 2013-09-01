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

#include <windows.h>
#include <Dbghelp.h>

#pragma comment(lib,"Dbghelp.lib")


#include <string>
#include <map>

#include <dragon/lang/internal/platform.h>

Import std;
Import dragon::lang::internal;


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Invoke
//

ParamInfo::ParamInfo(long longVal)
  :category(CATEGORY_INTEGER), typeName("long"), size(sizeof(long))
{
    this->value = cast_void<long>(longVal);
}

ParamInfo::ParamInfo(long long llVal)
  :category(CATEGORY_INTEGER), typeName("long long"), size(sizeof(long long))
{
    this->value = cast_void<long long>(llVal);
}

ParamInfo::ParamInfo(double doubleVal)
    :category(CATEGORY_SSE), typeName("double"), size(sizeof(double))
{
	double* buf = (double*)malloc(sizeof(double));
	*buf = doubleVal;
    this->value = buf;
}

ParamInfo::~ParamInfo(){
	if (this->size > CPU_BYTE_LEN) {
		//SafeFree(this->value);
	}
}

void ReturnInfo::setValue(double doubleVal) {
	double* buf = (double*)malloc(sizeof(double));
	*buf = doubleVal;
    this->value = buf;
}

const static size_t INT_ARGS_COUNT = 5;
const static size_t FLOATING_ARGS_COUNT = 8;

#ifdef _WIN32

void dragon::lang::internal::Invoke(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	DWORD result = 0;
	double sse_result = 0.0;

	size_t sum_size = 0;

	// push param to the statck
	for(int i=argc-1; i>=0; i--){
		ParamInfo* arg = &argv[i];
		size_t arg_size = arg->size;
		void* value = arg->value;

		size_t word_count = ((arg_size - 1) / CPU_BYTE_LEN + 1);
		size_t t_size = word_count * CPU_BYTE_LEN;
		sum_size += t_size;

		if (word_count == 1) {
			value = &arg->value;
		}

		__asm {
			sub         esp, t_size;

			mov         ecx, word_count;
			mov         esi, value;
			mov         edi, esp;
			rep movs    dword ptr es:[edi], dword ptr [esi];
		}
	}

	//call object p's method func
	__asm {
		mov			ecx, pthis; 
		call		func;
		mov         result, eax;
		fstp        sse_result;
	}

	if (ret->category == CATEGORY_INTEGER) {
		ret->value = (void*)result;
	} else if (ret->category == CATEGORY_SSE) {
		ret->setValue(sse_result);
	}
}

#else

void dragon::lang::internal::Invoke(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	DWORD result = 0;
	double sse_result = 0.0;

	size_t sum_size = 0;

	// push param to the statck
	for(int i=argc-1; i>=0; i--){
		ParamInfo* arg = &argv[i];
		size_t arg_size = arg->size;
		void* value = arg->value;

		size_t word_count = ((arg_size - 1) / CPU_BYTE_LEN + 1);
		size_t t_size = word_count * CPU_BYTE_LEN;
		sum_size += t_size;

		if (word_count == 1) {
			value = &arg->value;
		}

		__asm__ __volatile__("sub %0, %%rsp"::"a"(t_size));

		size_t i = 0;
		while (i < word_count) {
			__asm__ __volatile__("mov %0, %%ebx"::"a"(i));
			__asm__ __volatile__("mov %0, (%%esp, %%ebx, 4)"::"a"(value[i]));
			i++;
		}
	}

	//call object p's method func
	__asm__ __volatile__("mov %0, %%ecx"::"a"(pthis));
	__asm__ __volatile__("call *%0"::"a"(func));
	__asm__ __volatile__("mov %%eax, %0":"=a"(result));
	__asm__ __volatile__("movsd %%xmm0, %0":"=m"(sse_result));


	if (ret->category == CATEGORY_INTEGER) {
		ret->value = (void*)result;
	} else if (ret->category == CATEGORY_SSE) {
		ret->setValue(sse_result);
	}
}

#endif