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
 * Created:     2013/07/13
 **********************************************************************/

#include <gtest/gtest.h>
#include <typeinfo>

#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;


// ----------------------------------------------------------------------
// mix invoke test
//
/* 
void* invoke_test_mixtype_dd_05(void* pthis, char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return cast_void<double>(a);
}

#define INT_ARGS_COUNT 5
#define FLOATING_ARGS_COUNT 8

void InvokeTest(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
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

void* InvokeTest(void* pthis, void* func, ParamInfo *argv, int argc) {
	ReturnInfo ret("void*");
	InvokeTest(pthis, func, &ret, argv, argc);
	return ret.getValue<void*>();
}


TEST(Dragon_Lang_Internal_platformTest_x64, Invoke_Multi_Args_mixtype_22) {
	char a1 = 1;
	short b1 = 2;
	int c1 = 3;
	size_t d1 = 4;

	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	size_t m1 = 13;

    void* pthis = (void*)(&m1);
    void* dd1 = invoke_test_mixtype_dd_05(pthis, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);

    ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 13); 
    params[0] = ParamInfo(a1);
    params[1] = ParamInfo(b1);
    params[2] = ParamInfo(c1);
    params[3] = ParamInfo(d1);

    params[4] = ParamInfo(e1);
    params[5] = ParamInfo(f1);
    params[6] = ParamInfo(g1);
    params[7] = ParamInfo(h1);
    params[8] = ParamInfo(i1);
    params[9] = ParamInfo(j1);
    params[10] = ParamInfo(k1);
    params[11] = ParamInfo(l1);

    params[12] = ParamInfo(m1);

	void* dd2 = InvokeTest(pthis, (void*)(&invoke_test_mixtype_dd_05), params, 13);

	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

	SafeFree(params);
}

//------------------------------------------------------------
// double invoke test
// 
void* invoke_test_double_invoke_01(void* pthis, double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1, double k1, double l1, double m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return cast_void<double>(a);
}

TEST(Dragon_Lang_Internal_platformTest_x64, Invoke_Multi_Args_double_invoke) {
	void* pthis = (void*)(8888);

	double a1 = 1;
	double b1 = 2;
	double c1 = 3;
	double d1 = 4;
	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;

	void* dd1 = invoke_test_double_invoke_01(pthis, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 13); 
    params[0] = ParamInfo(a1);
    params[1] = ParamInfo(b1);
    params[2] = ParamInfo(c1);
    params[3] = ParamInfo(d1);
    params[4] = ParamInfo(e1);
    params[5] = ParamInfo(f1);
    params[6] = ParamInfo(g1);
    params[7] = ParamInfo(h1);
    params[8] = ParamInfo(i1);
    params[9] = ParamInfo(j1);
    params[10] = ParamInfo(k1);
    params[11] = ParamInfo(l1);
    params[12] = ParamInfo(m1);

	void* dd2 = InvokeTest(pthis, (void*)(&invoke_test_double_invoke_01), params, 13);

	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

	SafeFree(params);

}
*/

//------------------------------------------------------------
// mix struct invoke test
// 
/* Can not support this
struct mix3 {
  double a1;
  double b1;
  double c1;
  double d1;
  double e1;
  double f1;
};

void* invoke_test_mixtype_struct_invoke_07(void* pthis, mix3 m, double g1, double h1, 
	double i1, double j1, double k1, double l1, double m1) {
	double a = m.a1 
		+ m.b1 
		+ m.c1 
		+ m.d1 
		+ m.e1 
		+ m.f1 
		+ g1 
		+ h1 
		+ i1 
		+ j1 
		+ k1 
		+ l1 
  		+ m1;
	return cast_void<double>(a);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_mix_struct_invoke_01) {
	void* pthis = (void*)(8888);

	double a1 = 1;
	double b1 = 2;
	double c1 = 3;
	double d1 = 4;
	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;


	mix3 m;

	m.a1 = a1;
	m.b1 = b1;
	m.c1 = c1;
	m.d1 = d1;
	m.e1 = e1;
	m.f1 = f1;

	mix3* addr = &m;
	void* dd1 = invoke_test_mixtype_struct_invoke_07(pthis, m, g1, h1, i1, j1, k1, l1, m1);

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 8); 
    params[0] = ParamInfo(m);
    params[1] = ParamInfo(g1);
    params[2] = ParamInfo(h1);
    params[3] = ParamInfo(i1);
    params[4] = ParamInfo(j1);
    params[5] = ParamInfo(k1);
    params[6] = ParamInfo(l1);
    params[7] = ParamInfo(m1);

    size_t sc = 0;
    size_t w_ss = params[0].size / sizeof(void*);
    mix3* mm3 = (mix3*)params[0].value;
    void* val = params[0].value;

    void* mm4 = (void*)malloc(params[0].size);
    memcpy(mm4, val, params[0].size);

	void** stack_args = (void**)realloc(NULL, sizeof(void*) * (sc + w_ss));
	memcpy(stack_args + sc, val, params[0].size);
	mix3* mm5 = (mix3*)stack_args;

	void* dd2 = InvokeTest(pthis, (void*)(&invoke_test_mixtype_struct_invoke_07), params, 8);

	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

}


//------------------------------------------------------------
// mix struct invoke test 02
// 

struct mix4 {
  char a1;
  char b1;
  char c1;
  char d1;
  char e1;
  int f1;
};

void* invoke_test_mixtype_struct_invoke_08(void* pthis, mix4 m, double g1, double h1, 
	double i1, double j1, double k1, double l1, double m1) {
	double a = m.a1 
		+ m.b1 
		+ m.c1 
		+ m.d1 
		+ m.e1 
		+ m.f1 
		+ g1 
		+ h1 
		+ i1 
		+ j1 
		+ k1 
		+ l1 
  		+ m1;
	return cast_void<double>(a);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_mix_struct_invoke_02) {
	void* pthis = (void*)(8888);

	char a1 = 1;
	char b1 = 2;
	char c1 = 3;
	char d1 = 4;
	char e1 = 5;
	int f1 = 600000;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;


	mix4 m;

	size_t size_mix4 = sizeof(mix4);
	size_t size_f1 = sizeof(m.f1);
	void* ddd1 = (void*)&m.d1;
	void* dde1 = (void*)&m.e1;
	void* ddf1 = (void*)&m.f1;

	m.a1 = a1;
	m.b1 = b1;
	m.c1 = c1;
	m.d1 = d1;
	m.e1 = e1;
	m.f1 = f1;

	void* dd1 = invoke_test_mixtype_struct_invoke_08(pthis, m, g1, h1, i1, j1, k1, l1, m1);

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 8); 
    params[0] = ParamInfo(m);
    params[1] = ParamInfo(g1);
    params[2] = ParamInfo(h1);
    params[3] = ParamInfo(i1);
    params[4] = ParamInfo(j1);
    params[5] = ParamInfo(k1);
    params[6] = ParamInfo(l1);
    params[7] = ParamInfo(m1);

	void* dd2 = InvokeTest(pthis, (void*)(&invoke_test_mixtype_struct_invoke_08), params, 8);

	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);
}
*/


//------------------------------------------------------------
// double return invoke test
// 
/*
double invoke_test_double_ret_invoke_01(void* pthis, double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1, double k1, double l1, double m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return a;
}

TEST(Dragon_Lang_Internal_platformTest_x64, Invoke_Multi_Args_double_ret_invoke) {
	void* pthis = (void*)(8888);

	double a1 = 1;
	double b1 = 2;
	double c1 = 3;
	double d1 = 4;
	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;

	double dd1 = invoke_test_double_ret_invoke_01(pthis, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);

	ReturnInfo* ret = new ReturnInfo("double");

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 13); 
    params[0] = ParamInfo(a1);
    params[1] = ParamInfo(b1);
    params[2] = ParamInfo(c1);
    params[3] = ParamInfo(d1);
    params[4] = ParamInfo(e1);
    params[5] = ParamInfo(f1);
    params[6] = ParamInfo(g1);
    params[7] = ParamInfo(h1);
    params[8] = ParamInfo(i1);
    params[9] = ParamInfo(j1);
    params[10] = ParamInfo(k1);
    params[11] = ParamInfo(l1);
    params[12] = ParamInfo(m1);

	InvokeTest(pthis, (void*)(&invoke_test_double_ret_invoke_01), ret, params, 13);

	double dd2 = ret->getValue<double>();
	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

	SafeDelete(ret);
	SafeFree(params);
}
*/
