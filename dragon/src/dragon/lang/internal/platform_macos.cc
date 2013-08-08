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

#include <dragon/lang/internal/platform.h>

Import std;
Import dragon::lang::internal;

// ----------------------------------------------------------------------------
// Some Help Func



//void* dragon::lang::internal::Invoke(void* p, Func_FarProc func, TypeInfo *argv, int argc)
//{   
	/*
	DWORD result;
	DWORD argSize,tSize,sumSize=0;
	TypeInfo arg;

	//push arg into stack
	for(int i=argc-1;i>=0;i--)
	{
		arg=argv[i];
		argSize=arg.typeSize;
		void* value=arg.pValue;

		sumSize+=argSize;
		tSize=argSize/4;

		__asm{
			mov			eax,argSize;
			sub         esp,eax;

			mov         ecx,tSize;
			mov         esi,value;
			mov         edi,esp;
			rep movs    dword ptr es:[edi],dword ptr [esi];
		}

	}

	//call object p's method func
	__asm{
			mov			ecx,p; 
			call		func;
			mov         result,eax;
	}

	if(p==null)
	{
		__asm{
			mov			eax,sumSize;
			add         esp,eax;
		}		
	}

	return (void*)result;
	*/

//	return null;
//} 



/*
platformTest_macos.cc:573
0x000000010002e8bf: mov    -0x68(%rbp),%rax                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+697
0x000000010002e8c3: movsd  -0x38(%rbp),%xmm0                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+701
0x000000010002e8c8: movsd  -0x40(%rbp),%xmm1                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+706
0x000000010002e8cd: movsd  -0x48(%rbp),%xmm2                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+711
0x000000010002e8d2: movsd  -0x50(%rbp),%xmm3                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+716
0x000000010002e8d7: movsd  -0x58(%rbp),%xmm4                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+721
0x000000010002e8dc: movsd  -0x60(%rbp),%xmm5                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+726
0x000000010002e8e1: mov    -0xc8(%rbp),%rcx                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+731
0x000000010002e8e8: mov    -0xa0(%rbp),%rdx                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+738
0x000000010002e8ef: mov    %rsp,%rsi                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+745
0x000000010002e8f2: mov    %rdx,0x18(%rsi)                                       # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+748
0x000000010002e8f6: mov    -0xa8(%rbp),%rdx                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+752
0x000000010002e8fd: mov    %rdx,0x10(%rsi)                                       # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+759
0x000000010002e901: mov    -0xb8(%rbp),%rdx                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+763
0x000000010002e908: mov    -0xb0(%rbp),%rdi                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+770
0x000000010002e90f: mov    %rdi,0x8(%rsi)                                        # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+777
0x000000010002e913: mov    %rdx,(%rsi)                                           # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+781
0x000000010002e916: mov    %rax,%rdi                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+784
0x000000010002e919: mov    %rcx,%rsi                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+787
0x000000010002e91c: callq  0x10002e4e0 <_Z22invoke_test_mixtype_074mix2ddddddmPv> # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+790
platformTest_macos.cc:574

0x000000010002dda2: mov    -0x68(%rbp),%rax                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+396
0x000000010002dda6: mov    -0x14(%rbp),%cx                                       # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+400
0x000000010002ddaa: movswl %cx,%ecx                                              # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+404
0x000000010002ddad: mov    -0x11(%rbp),%r8b                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+407
0x000000010002ddb1: movsbl %r8b,%r8d                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+411
0x000000010002ddb5: mov    -0x18(%rbp),%r9d                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+415
0x000000010002ddb9: mov    -0x20(%rbp),%r10                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+419
0x000000010002ddbd: movsd  -0x28(%rbp),%xmm0                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+423
0x000000010002ddc2: movsd  -0x30(%rbp),%xmm1                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+428
0x000000010002ddc7: movsd  -0x38(%rbp),%xmm2                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+433
0x000000010002ddcc: movsd  -0x40(%rbp),%xmm3                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+438
0x000000010002ddd1: movsd  -0x48(%rbp),%xmm4                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+443
0x000000010002ddd6: movsd  -0x50(%rbp),%xmm5                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+448
0x000000010002dddb: movsd  -0x58(%rbp),%xmm6                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+453
0x000000010002dde0: movsd  -0x60(%rbp),%xmm7                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+458
0x000000010002dde5: movsbl %r8b,%r8d                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+463
0x000000010002dde9: mov    %r8d,%edi                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+467
0x000000010002ddec: movswl %cx,%ecx                                              # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+470
0x000000010002ddef: mov    %ecx,%esi                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+473
0x000000010002ddf1: mov    %r9d,%edx                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+475
0x000000010002ddf4: mov    %r10,%rcx                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+478
0x000000010002ddf7: mov    %rax,%r8                                              # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+481
0x000000010002ddfa: callq  0x10002d570 <_Z22invoke_test_mixtype_01csimddddddddm> # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+484
platformTest_macos.cc:571
0x000000010002ddff: mov    -0x68(%rbp),%rax                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+489
0x000000010002de03: mov    -0x14(%rbp),%cx                                       # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+493
0x000000010002de07: movswl %cx,%ecx                                              # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+497
0x000000010002de0a: mov    -0x11(%rbp),%r8b                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+500
0x000000010002de0e: movsbl %r8b,%r8d                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+504
0x000000010002de12: mov    -0x18(%rbp),%r9d                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+508
0x000000010002de16: mov    -0x20(%rbp),%r10                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+512
0x000000010002de1a: movsd  -0x28(%rbp),%xmm0                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+516
0x000000010002de1f: movsd  -0x30(%rbp),%xmm1                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+521
0x000000010002de24: movsd  -0x38(%rbp),%xmm2                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+526
0x000000010002de29: movsd  -0x40(%rbp),%xmm3                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+531
0x000000010002de2e: movsd  -0x48(%rbp),%xmm4                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+536
0x000000010002de33: movsd  -0x50(%rbp),%xmm5                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+541
0x000000010002de38: movsd  -0x58(%rbp),%xmm6                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+546
0x000000010002de3d: movsd  -0x60(%rbp),%xmm7                                     # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+551
0x000000010002de42: lea    -0x68(%rbp),%r11                                      # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+556
0x000000010002de46: mov    %r11,%rbx                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+560
0x000000010002de49: movsbl %r8b,%r8d                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+563
0x000000010002de4d: mov    %r8d,%edi                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+567
0x000000010002de50: movswl %cx,%ecx                                              # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+570
0x000000010002de53: mov    %ecx,%esi                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+573
0x000000010002de55: mov    %r9d,%edx                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+575
0x000000010002de58: mov    %r10,%rcx                                             # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+578
0x000000010002de5b: mov    %rax,%r8                                              # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+581
0x000000010002de5e: mov    %rbx,%r9                                              # _ZN64Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_mixtype_Test8TestBodyEv+584
0x000000010002de61: mov    %r11,-0xc8(%rbp)    

0x000000010002da58: movsd  -0x10(%rbp),%xmm0                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+380
0x000000010002da5d: movsd  -0x18(%rbp),%xmm1                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+385
0x000000010002da62: movsd  -0x20(%rbp),%xmm2                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+390
0x000000010002da67: movsd  -0x28(%rbp),%xmm3                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+395
0x000000010002da6c: movsd  -0x30(%rbp),%xmm4                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+400
0x000000010002da71: movsd  -0x38(%rbp),%xmm5                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+405
0x000000010002da76: movsd  -0x40(%rbp),%xmm6                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+410
0x000000010002da7b: movsd  -0x48(%rbp),%xmm7                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+415
0x000000010002da80: movsd  -0x50(%rbp),%xmm8                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+420
0x000000010002da86: movsd  -0x58(%rbp),%xmm9                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+426
0x000000010002da8c: movsd  -0x60(%rbp),%xmm10                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+432
0x000000010002da92: movsd  -0x68(%rbp),%xmm11                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+438
0x000000010002da98: movsd  -0x70(%rbp),%xmm12                                    # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+444
0x000000010002da9e: movsd  %xmm8,(%rsp)                                          # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+450
0x000000010002daa4: movsd  %xmm9,0x8(%rsp)                                       # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+456
0x000000010002daab: movsd  %xmm10,0x10(%rsp)                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+463
0x000000010002dab2: movsd  %xmm11,0x18(%rsp)                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+470
0x000000010002dab9: movsd  %xmm12,0x20(%rsp)                                     # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+477
0x000000010002dac0: callq  0x10002d650 <_Z21invoke_test_double_01ddddddddddddd>  # _ZN63Dragon_Lang_Internal_platformTest_Invoke_Multi_Args_double_Test8TestBodyEv+484
platformTest_macos.cc:449

 */
const static size_t INT_ARGS_COUNT = 5;
const static size_t FLOATING_ARGS_COUNT = 8;

void* dragon::lang::internal::Invoke(void* pthis, void* func, ParamInfo *argv, int argc) {
	void* result = NULL;

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

		if (category == 1) {
			if (fc < FLOATING_ARGS_COUNT) {
				floating_args[fc++] = val;
			} else {
				stack_args = (void**)realloc(stack_args, sizeof(void*) * (sc + 1));
				stack_args[sc++] = val;
			}
		} else if (category == 0 || category == 3) {
			if (ic < INT_ARGS_COUNT) {
				int_args[ic++] = val;
			} else {
				stack_args = (void**)realloc(stack_args, sizeof(void*) * (sc + 1));
				stack_args[sc++] = val;
			}
		} else if (category == 2) {
			size_t w_ss = size / sizeof(void*);
			stack_args = (void**)realloc(stack_args, sizeof(void*) * (sc + w_ss));
			memcpy(stack_args + sc, val, size);
			sc+=w_ss;
		}
	}


	if (sc > 0) {
		__asm__ __volatile__("subq %0, %%rsp"::"a"(sc * sizeof(void*)));
		
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
	__asm__ __volatile__("mov %%rax, %0":"=a"(result));


	if (sc > 0) {
		free(stack_args);
		__asm__ __volatile__("addq %0, %%rsp"::"a"(sc * sizeof(void*)));
	}

	return result;
}

//void* dragon::lang::internal::InvokeV(void* p, Func_FarProc func, ...)
//{
	/*DWORD result;

	va_list ap;
	va_start(ap,func);

	__asm{
		mov			ebx,esp;
		sub         esp,0x100;

		mov         ecx,0x40;
		mov         esi,ap;
		mov         edi,esp;
		rep movs    dword ptr es:[edi],dword ptr [esi];

		mov			ecx,p; 
		call		func;
		mov         result,eax;

		mov			esp,ebx;
	}

	return (void*)result;
	*/

//	int result = func();
//	return (void*)result;
//}


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
	//Dl_info info;
	//dladdr((void*)(&LibAdressFlag), &info);
	//return info.dli_fname;
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

//--------------------------------------------------------------------
//  SymbolMangling Implements 
//--------------------------------------------------------------------

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


