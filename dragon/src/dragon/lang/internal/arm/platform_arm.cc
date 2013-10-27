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

#ifdef _WIN32
	#include <windows.h>
#else 
	#include <dlfcn.h>
	#include <cxxabi.h>
#endif

#include <string.h>
#include <stdlib.h>

#include <string>
#include <map>

#include <dragon/lang/internal/platform.h>

Import std;
Import dragon::lang::internal;

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Method Invoke
//

ParamInfo::ParamInfo(long longVal)
  :category(CATEGORY_INTEGER), typeName("long"), size(sizeof(long))
{
	long* buf = (long*)malloc(sizeof(long));
	*buf = longVal;
    this->value = buf;
}
    
ParamInfo::ParamInfo(long long llVal)
  :category(CATEGORY_INTEGER), typeName("long long"), size(sizeof(long long))
{
	long long* buf = (long long*)malloc(sizeof(long long));
	*buf = llVal;
    this->value = buf;
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

#ifdef _WIN32

void dragon::lang::internal::Invoke(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {

}

#else

#define NCRC_COUNT 4  //The Next Core Register Count
#define SUPPORT_VFP = 1  //support VFP co-processor
#define SUPPORT_SIMD = 1 //support the Advanced SIMD Extension

void dragon::lang::internal::Invoke(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	size_t int_result[4];

	void* int_args[NCRC_COUNT];
	void** stack_args = NULL;

	size_t ic = 0;
	size_t sc = 0;

	int_args[ic++] = pthis;

	for (int i=0; i<argc; i++) {
		ParamInfo* arg = &argv[i];
		int category = arg->category;
		size_t arg_size = arg->size;
		void* value = arg->value;

		size_t word_count = ((arg_size - 1) / CPU_BYTE_LEN + 1);
		size_t t_size = word_count * CPU_BYTE_LEN;

		if (category == CATEGORY_INTEGER || category == CATEGORY_SSE) {
			if (word_count == 1) {
				value = &arg->value;
			}

			if (ic + word_count <= NCRC_COUNT - 1) {
				// if the argument required double-word alignment (8-byte), 
				// then the NSAA is rounded up to the next double-word address.
				if (word_count == 2 && ic % 2 != 0) {
					ic++;
				}

				memcpy(int_args + ic, value, t_size);
				ic += word_count;
			} else {
				stack_args = (void**)realloc(stack_args, CPU_BYTE_LEN * (sc + word_count));
				memcpy(stack_args + sc, value, t_size);
				sc += word_count;
			}
		} else if (category == CATEGORY_MEMORY) {
			stack_args = (void**)realloc(stack_args, CPU_BYTE_LEN * (sc + word_count));
			memcpy(stack_args + sc, value, t_size);
			sc += word_count;
		}
	}


	if (sc > 0) {
		__asm__ __volatile__("sub sp, %0"::"r"(sc * CPU_BYTE_LEN));

		size_t i = 0;
		while (i < sc) {
			__asm__ __volatile__("mov r0, %0"::"r"(i));
			__asm__ __volatile__("mov r1, %0"::"r"(stack_args[i]));
			__asm__ __volatile__("str r1, [sp, r0, lsl #2]");
			i++;
		}
	}

	__asm__ __volatile__("mov r4, %0"::"r"(func));
	__asm__ __volatile__("mov r0, %0"::"r"(int_args[0]));
	__asm__ __volatile__("mov r1, %0"::"r"(int_args[1]));
	__asm__ __volatile__("mov r2, %0"::"r"(int_args[2]));
	__asm__ __volatile__("mov r3, %0"::"r"(int_args[3]));
	__asm__ __volatile__("blx r4");
	__asm__ __volatile__("mov %0, r0":"=r"(int_result[0]));
	__asm__ __volatile__("mov %0, r1":"=r"(int_result[1]));
	__asm__ __volatile__("mov %0, r2":"=r"(int_result[2]));
	__asm__ __volatile__("mov %0, r3":"=r"(int_result[3]));

	if (sc > 0) {
		free(stack_args);
		__asm__ __volatile__("add sp, %0"::"r"(sc * CPU_BYTE_LEN));
	}

	if (ret->size <= CPU_BYTE_LEN) {
		ret->value = (void*)int_result[0];
	} else {
		char* buf = (char*)malloc(ret->size);
		memcpy(buf, int_result, ret->size);
	    ret->value = buf;
	}
}

#endif