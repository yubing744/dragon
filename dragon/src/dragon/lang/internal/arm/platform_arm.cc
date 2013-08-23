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

#include <string.h>
#include <stdlib.h>

#include <string>
#include <map>

#include <dragon/lang/internal/platform.h>

Import std;
Import dragon::lang::internal;

#define INT_ARGS_COUNT 5
#define FLOATING_ARGS_COUNT 8

void dragon::lang::internal::Invoke(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	//__asm__ __volatile__("mov r0, r1");

	/*
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
	*/
}