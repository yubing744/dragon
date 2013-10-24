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
void* invoke_test_mixtype_dd_05(void* pthis, char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return cast_void(a);
}

#ifdef _WIN32

#include <windows.h>

void InvokeTest(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	DWORD result = 0;
	double sse_result = 0.0;

	size_t sum_size = 0;

	// push param to the statck
	for(int i=argc-1; i>=0; i--){
		ParamInfo arg = argv[i];
		size_t arg_size = arg.size;
		void* value = arg.value;

		size_t word_count = ((arg_size - 1) / CPU_BYTE_LEN + 1);
		size_t t_size = word_count * CPU_BYTE_LEN;
		sum_size += t_size;

		if (word_count == 1) {
			value = &arg.value;
		}

		__asm {
			sub         esp, t_size;

			mov         ecx, word_count;
			mov         esi, value;
			mov         edi, esp;
			rep movs    dword ptr es:[edi], dword ptr [esi];
		}
	}

	sum_size += sizeof(void*);

	__asm {
		mov eax, pthis;
		push eax;
	}

	//call object p's method func
	__asm {
		call		func;
		mov         result, eax;
		fstp        sse_result;
	}

	// restore the statck
	__asm {
		mov			eax, sum_size;
		add         esp, eax;
	}		
 
	if (ret->category == CATEGORY_INTEGER) {
		ret->value = (void*)result;
	} else if (ret->category == CATEGORY_SSE) {
		ret->setValue(sse_result);
	}
}

#else 

void InvokeTest(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	size_t result = 0;
	double sse_result = 0.0;

	//throw "not implements";
	size_t sum_size = 0;

	

	// push param to the statck
	for(int i=argc-1; i>=0; i--){
		ParamInfo* arg = &argv[i];
		size_t arg_size = arg->size;
		void* value = arg->value;

		size_t word_count = ((arg_size - 1) / CPU_BYTE_LEN + 1);
		size_t t_size = word_count * CPU_BYTE_LEN;
		sum_size += t_size;

		__asm__ __volatile__("sub %0, %%esp"::"a"(t_size));

		if (word_count == 1) {
			__asm__ __volatile__("mov %0, (%%esp)"::"a"(value));
		} else {
			__asm__ __volatile__("mov %0, %%eax"::"a"(value));
			__asm__ __volatile__("fldl (%eax)");
			__asm__ __volatile__("fstpl (%esp)");
		}		
	}

	sum_size += CPU_BYTE_LEN;
	__asm__ __volatile__("sub %0, %%esp"::"a"(CPU_BYTE_LEN));
	__asm__ __volatile__("mov %0, (%%esp)"::"a"(pthis));

	//call object p's method func
	//__asm__ __volatile__("mov %0, %%ecx"::"a"(pthis));
	__asm__ __volatile__("call *%0"::"a"(func));
	__asm__ __volatile__("mov %%eax, %0":"=a"(result));
	__asm__ __volatile__("fstpl (%0)"::"a"(&sse_result));


	//restore stack
	__asm__ __volatile__("add %0, %%esp"::"a"(sum_size));
	

	if (ret->size <= CPU_BYTE_LEN) {
		ret->value = (void*)result;
	} else {
		ret->setValue(sse_result);
	}
}

#endif	

void* InvokeTest(void* pthis, void* func, ParamInfo *argv, int argc) {
	ReturnInfo ret("void*");
	InvokeTest(pthis, func, &ret, argv, argc);
	return ret.getValue<void*>();
}

#ifdef _WIN32

void InvokeMethod(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	size_t result = 0;
	double sse_result = 0.0;

	size_t sum_size = 0;

	// push param to the statck
	for(int i=argc-1; i>=0; i--){
		ParamInfo arg = argv[i];
		size_t arg_size = arg.size;
		void* value = arg.value;

		size_t word_count = ((arg_size - 1) / CPU_BYTE_LEN + 1);
		size_t t_size = word_count * CPU_BYTE_LEN;
		sum_size += t_size;

		if (word_count == 1) {
			value = &arg.value;
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

	// restore the statck
	__asm {
		mov			eax, sum_size;
		add         esp, eax;
	}		
 
	if (ret->category == CATEGORY_INTEGER) {
		ret->value = (void*)result;
	} else if (ret->category == CATEGORY_SSE) {
		ret->value = cast_void<double>(sse_result);
	}
}

#else 
void InvokeMethod(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	throw "not implements";
}
#endif

TEST(Dragon_Lang_Internal_platformTest_ia32, Invoke_Multi_Args_mixtype_22) {
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

TEST(Dragon_Lang_Internal_platformTest_ia32, Invoke_Multi_Args_double_invoke) {
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
double invoke_test_double_ret_invoke_01(void* pthis, double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1, double k1, double l1, double m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return a;
}

TEST(Dragon_Lang_Internal_platformTest_ia32, Invoke_Multi_Args_double_ret_invoke) {
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


/*
Invokde short 

dragon/test/dragon/lang/internal/platformTest.cc:482
0x08064fcb: movw   $0xc,-0x24(%ebp)                                              # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+75
dragon/test/dragon/lang/internal/platformTest.cc:483
0x08064fd1: movw   $0xd,-0x26(%ebp)                                              # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+81
dragon/test/dragon/lang/internal/platformTest.cc:484
dragon/test/dragon/lang/internal/platformTest.cc:485
0x08064fd7: movswl -0x14(%ebp),%ebx                                              # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+87
0x08064fdb: movswl -0x12(%ebp),%ecx                                              # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+91
0x08064fdf: movswl -0x10(%ebp),%edx                                              # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+95
0x08064fe3: movswl -0xe(%ebp),%eax                                               # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+99
0x08064fe7: mov    %ebx,0xc(%esp)                                                # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+103
0x08064feb: mov    %ecx,0x8(%esp)                                                # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+107
0x08064fef: mov    %edx,0x4(%esp)                                                # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+111
0x08064ff3: mov    %eax,(%esp)                                                   # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_short_Test8TestBodyEv+115
0x08064ff6: call   0x8064f32 <_Z20invoke_test_short_04ssss> 
*/

/*

Invoke size_t

dragon/test/dragon/lang/internal/platformTest.cc:528
0x0806521b: movl   $0xa,-0x28(%ebp)                                              # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+69
dragon/test/dragon/lang/internal/platformTest.cc:529
0x08065222: movl   $0xb,-0x2c(%ebp)                                              # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+76
dragon/test/dragon/lang/internal/platformTest.cc:530
0x08065229: movl   $0xc,-0x30(%ebp)                                              # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+83
dragon/test/dragon/lang/internal/platformTest.cc:531
0x08065230: movl   $0xd,-0x34(%ebp)                                              # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+90
dragon/test/dragon/lang/internal/platformTest.cc:532
dragon/test/dragon/lang/internal/platformTest.cc:533
0x08065237: mov    -0x10(%ebp),%eax                                              # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+97
0x0806523a: mov    %eax,0xc(%esp)                                                # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+100
0x0806523e: mov    -0xc(%ebp),%eax                                               # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+104
0x08065241: mov    %eax,0x8(%esp)                                                # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+107
0x08065245: mov    -0x8(%ebp),%eax                                               # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+111
0x08065248: mov    %eax,0x4(%esp)                                                # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+114
0x0806524c: mov    -0x4(%ebp),%eax                                               # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+118
0x0806524f: mov    %eax,(%esp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_size_t_Test8TestBodyEv+121
0x08065252: call   0x80651b3 <_Z21invoke_test_size_t_04jjjj>  
*/

/*
char test

0x08065581: movb   $0xa,-0x16(%ebp)                                              # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+45
dragon/test/dragon/lang/internal/platformTest.cc:576
0x08065585: movb   $0xb,-0x17(%ebp)                                              # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+49
dragon/test/dragon/lang/internal/platformTest.cc:577
0x08065589: movb   $0xc,-0x18(%ebp)                                              # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+53
dragon/test/dragon/lang/internal/platformTest.cc:578
0x0806558d: movb   $0xd,-0x19(%ebp)                                              # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+57
dragon/test/dragon/lang/internal/platformTest.cc:579
dragon/test/dragon/lang/internal/platformTest.cc:580
0x08065591: movsbl -0x10(%ebp),%ebx                                              # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+61
0x08065595: movsbl -0xf(%ebp),%ecx                                               # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+65
0x08065599: movsbl -0xe(%ebp),%edx                                               # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+69
0x0806559d: movsbl -0xd(%ebp),%eax                                               # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+73
0x080655a1: mov    %ebx,0xc(%esp)                                                # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+77
0x080655a5: mov    %ecx,0x8(%esp)                                                # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+81
0x080655a9: mov    %edx,0x4(%esp)                                                # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+85
0x080655ad: mov    %eax,(%esp)                                                   # _ZN61Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_char_Test8TestBodyEv+89
0x080655b0: call   0x806550c <_Z19invoke_test_char_04cccc>
*/

/*
float test

dragon/test/dragon/lang/internal/platformTest.cc:627
0x080657f2: mov    -0x10(%ebp),%eax                                              # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+110
0x080657f5: mov    %eax,0xc(%esp)                                                # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+113
0x080657f9: mov    -0xc(%ebp),%eax                                               # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+117
0x080657fc: mov    %eax,0x8(%esp)                                                # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+120
0x08065800: mov    -0x8(%ebp),%eax                                               # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+124
0x08065803: mov    %eax,0x4(%esp)                                                # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+127
0x08065807: mov    -0x4(%ebp),%eax                                               # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+131
0x0806580a: mov    %eax,(%esp)                                                   # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+134
0x0806580d: call   0x8065764 <_Z20invoke_test_float_04ffff>                      # _ZN62Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_float_Test8TestBodyEv+137
dragon/test/dragon/lang/internal/platformTest.cc:628

*/


/*

double test

dragon/test/dragon/lang/internal/platformTest.cc:677
0x08065c02: fldl   -0x68(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+260
0x08065c05: fstpl  0x60(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+263
0x08065c09: fldl   -0x60(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+267
0x08065c0c: fstpl  0x58(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+270
0x08065c10: fldl   -0x58(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+274
0x08065c13: fstpl  0x50(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+277
0x08065c17: fldl   -0x50(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+281
0x08065c1a: fstpl  0x48(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+284
0x08065c1e: fldl   -0x48(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+288
0x08065c21: fstpl  0x40(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+291
0x08065c25: fldl   -0x40(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+295
0x08065c28: fstpl  0x38(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+298
0x08065c2c: fldl   -0x38(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+302
0x08065c2f: fstpl  0x30(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+305
0x08065c33: fldl   -0x30(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+309
0x08065c36: fstpl  0x28(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+312
0x08065c3a: fldl   -0x28(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+316
0x08065c3d: fstpl  0x20(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+319
0x08065c41: fldl   -0x20(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+323
0x08065c44: fstpl  0x18(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+326
0x08065c48: fldl   -0x18(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+330
0x08065c4b: fstpl  0x10(%esp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+333
0x08065c4f: fldl   -0x10(%ebp)                                                   # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+337
0x08065c52: fstpl  0x8(%esp)                                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+340
0x08065c56: fldl   -0x8(%ebp)                                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+344
0x08065c59: fstpl  (%esp)                                                        # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+347
0x08065c5c: call   0x80658dd <_Z21invoke_test_double_01ddddddddddddd>            # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+350
dragon/test/dragon/lang/internal/platformTest.cc:678
0x08065c61: leave                                                                # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+355
0x08065c62: ret                                                                  # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+356

*/