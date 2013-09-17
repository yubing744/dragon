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

#include <dragon.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;

TEST(Dragon_Lang_Internal_platformTest, New) {
	ShowLocalLibInfo();
}

TEST(Dragon_Lang_Internal_platformTest, Split) {
	vector<string> v = Split("dragon::lang::internal", "::");
	EXPECT_EQ(3, v.size());
	EXPECT_EQ("dragon", v[0]);
	EXPECT_EQ("lang", v[1]);
	EXPECT_EQ("internal", v[2]);
}

TEST(Dragon_Lang_Internal_platformTest, Join) {
	vector<string> v = Split("dragon::lang::internal", "::");
	EXPECT_EQ(3, v.size());
	
	string results = Join(v, ".");
	EXPECT_EQ("dragon.lang.internal", results);

	string results2 = Join(v, "");
	EXPECT_EQ("dragonlanginternal", results2);
}

/*
TEST(Dragon_Lang_Internal_platformTest, GetFuncAddress_LocalLib) {
	SymTestBean_TestByte_MemberMethod setBytePtr = &SymTestBean::test;
	void* setBytePtr1 = reinterpret_cast<void*>(*(void**)(&setBytePtr));
	void* setBytePtr2 = GetFuncAddress("dragon::lang::internal::SymTestBean::test(dg_byte)");
	dg_boolean isTrue = (setBytePtr1 == setBytePtr2);
	EXPECT_EQ(dg_true, isTrue);
}
*/

//-----------------------------------------------------------
//Test Setter

TEST(Dragon_Lang_Internal_platformTest, Invoke_Getter) {
	// Way 1
	SymTestBean* tb = new SymTestBean(112);
	dg_int testVal1 = tb->getTestVal();
	EXPECT_EQ(112, testVal1);

	// Way 2
	SymTestBean_TestGetter_MemberMethod getTestVal = (SymTestBean_TestGetter_MemberMethod)&SymTestBean::getTestVal;
	dg_int testVal2 = (tb->*getTestVal)();
	EXPECT_EQ(112, testVal2);

	// Way 3
	dg_int testVal3 = bind(&SymTestBean::getTestVal, tb)(); 
	EXPECT_EQ(112, testVal3);

	// Way 4 Fail
	/*
	void* getTestValPtr1 = reinterpret_cast<void*>(*(void**)(&getTestVal));
	void* getTestValPtr2 = GetFuncAddress("dragon::lang::internal::SymTestBean::getTestVal()");
	SymTestBean_TestGetter_MemberMethod getTestValFuncPtr = *(SymTestBean_TestGetter_MemberMethod*)(&getTestValPtr1);
	dg_int testVal4 = (tb->*getTestValFuncPtr)();
	EXPECT_EQ(112, testVal4);
	*/

	// Way 5 Fail
	/*
	void* addr = GetFuncAddress("dragon::lang::internal::SymTestBean::getTestVal()");
	SymTestBean_TestGetter_MemberMethod getTestValFuncPtr = *(SymTestBean_TestGetter_MemberMethod*)(&addr);
	dg_int testVal4 = bind(getTestValFuncPtr, tb)(); 
	EXPECT_EQ(112, testVal4);
	*/

	// Way 6
	/*
	Func_FarProc getTestValFuncPtr = (Func_FarProc)GetFuncAddress("dragon::lang::internal::SymTestBean::getTestVal()");
	void* ret = Invoke((void*)tb, getTestValFuncPtr);
	dg_int testVal4 = *((dg_int*)ret);
	EXPECT_EQ(0, testVal4);
	*/

	SafeDelete(tb);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Getter_Way1) {
	SymTestBean* tb = new SymTestBean(112);
	dg_int testVal1 = tb->getTestVal();
	EXPECT_EQ(112, testVal1);
	SafeDelete(tb);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Getter_Way2) {
	SymTestBean* tb = new SymTestBean(112);
	SymTestBean_TestGetter_MemberMethod getTestVal = (SymTestBean_TestGetter_MemberMethod)&SymTestBean::getTestVal;
	dg_int testVal2 = (tb->*getTestVal)();
	EXPECT_EQ(112, testVal2);
	SafeDelete(tb);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Getter_Way3) {
	SymTestBean* tb = new SymTestBean(112);
	dg_int testVal3 = bind(&SymTestBean::getTestVal, tb)(); 
	EXPECT_EQ(112, testVal3);
	SafeDelete(tb);
}

/*
TEST(Dragon_Lang_Internal_platformTest, Invoke_Getter_Way6_My01) {
	SymTestBean* tb = new SymTestBean(112);
	SymTestBean_TestGetter_MemberMethod getTestVal = (SymTestBean_TestGetter_MemberMethod)&SymTestBean::getTestVal;
	void* getTestValPtr1 = reinterpret_cast<void*>(*(void**)(&getTestVal));
	void* getTestValPtr2 = GetFuncAddress("dragon::lang::internal::SymTestBean::getTestVal()");

	dg_int ret1 = tb->getTestVal();
	dg_int ret2 = (tb->*getTestVal)();
	dg_int ret3 = Invoke<dg_int>((void*)tb, getTestValPtr2);

	dg_boolean isTrue = (getTestValPtr1 == getTestValPtr2);
	EXPECT_EQ(dg_true, isTrue);

	EXPECT_EQ(112, ret1);
	EXPECT_EQ(112, ret2);
	EXPECT_EQ(112, ret3);

	SafeDelete(tb);
}
*/

/*
TEST(Dragon_Lang_Internal_platformTest, Invoke_Getter_Way7) {
	SymTestBean* tb = new SymTestBean(112);

	void* getTestValPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::getTestVal()");
	SymTestBean_TestGetter_MemberMethod2 stm = void_cast<SymTestBean_TestGetter_MemberMethod2>(getTestValPtr);
	dg_int ret4 = stm((void*)tb);

	EXPECT_EQ(112, ret4);
	SafeDelete(tb);
}
*/

//--------------------------------------------------------------
// Test Setter
// 
TEST(Dragon_Lang_Internal_platformTest, Invoke_Setter_Way1) {
	SymTestBean* tb = new SymTestBean(112);
	tb->setTestVal(888);

	dg_int ret1 = tb->getTestVal();
	EXPECT_EQ(888, ret1);

	SafeDelete(tb);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Setter_Way2) {
	SymTestBean* tb = new SymTestBean(112);
	SymTestBean_TestSetter_MemberMethod setTestVal = (SymTestBean_TestSetter_MemberMethod)&SymTestBean::setTestVal;
	(tb->*setTestVal)(888);

	dg_int ret1 = tb->getTestVal();
	EXPECT_EQ(888, ret1);

	SafeDelete(tb);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Setter_Way3) {
	SymTestBean* tb = new SymTestBean(112);

	bind(&SymTestBean::setTestVal, tb)(888); 

	dg_int ret1 = tb->getTestVal();
	EXPECT_EQ(888, ret1);

	SafeDelete(tb);
}

/*
TEST(Dragon_Lang_Internal_platformTest, Invoke_Setter_Way4) {
	SymTestBean* tb = new SymTestBean(112);

	void* setTestValPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::setTestVal(dg_int)");
	Invoke<dg_int, void>((void*)tb, setTestValPtr, 888);

	dg_int ret1 = tb->getTestVal();
	EXPECT_EQ(888, ret1);

	SafeDelete(tb);
}
*/

//--------------------------------------------------------------
// Test Constructor
// 
TEST(Dragon_Lang_Internal_platformTest, Invoke_Constructor_Way1) {
	SymTestBean* tb = new SymTestBean();

	tb->setTestVal(888);
	dg_int ret1 = tb->getTestVal();
	EXPECT_EQ(888, ret1);

	SafeDelete(tb);
}

/*
TEST(Dragon_Lang_Internal_platformTest, Invoke_Constructor_Way2) {
	void* defaultConstructorPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::SymTestBean()");
	void* tb_mem = malloc(100);
	SymTestBean* tb = (SymTestBean*)Invoke<void*>(tb_mem, defaultConstructorPtr);

	tb->setTestVal(888);
	dg_int ret1 = tb->getTestVal();
	EXPECT_EQ(888, ret1);

	SafeDelete(tb);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Constructor_Way3) {
	void* tb_mem = malloc(100);

	void* defaultConstructorPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::SymTestBean()");
	void* tb = Invoke<void*>(tb_mem, defaultConstructorPtr);

	void* setTestValPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::setTestVal(dg_int)");
	Invoke<dg_int, void>(tb, setTestValPtr, 888);

	void* getTestValPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::getTestVal()");
	dg_int ret1 = Invoke<dg_int>(tb, getTestValPtr);

	EXPECT_EQ(888, ret1);

	free(tb_mem);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Constructor_Way3_With_Low_Mem) {
	//void* tb_mem = malloc(2);
	void* tb_mem = malloc(2000);

	void* defaultConstructorPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::SymTestBean()");
	void* tb = Invoke<void*>(tb_mem, defaultConstructorPtr);

	void* setTestValPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::setTestVal(dg_int)");
	Invoke<dg_int, void>(tb, setTestValPtr, 888);

	void* getTestValPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::getTestVal()");
	dg_int ret1 = Invoke<dg_int>(tb, getTestValPtr);

	EXPECT_EQ(888, ret1);

	free(tb_mem);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Class_With_Multi_Args) {
	void* tb_mem = malloc(2000);

	void* defaultConstructorPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::SymTestBean()");
	void* tb = Invoke<void*>(tb_mem, defaultConstructorPtr);

	void* setTestValPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::setTestVal(dg_int)");
	
	ParamInfo* param = new ParamInfo(888);
	Invoke(tb, setTestValPtr, param, 1);

	void* getTestValPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::getTestVal()");
	dg_int ret1 = Invoke<dg_int>(tb, getTestValPtr);

	EXPECT_EQ(888, ret1);

	free(tb_mem);
	SafeDelete(param);
}
*/


/*
TEST(Dragon_Lang_Internal_platformTest, Invoke_Class_Size_Check1) {
	void* tb_mem = malloc(2000);

	void* defaultConstructorPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::SymTestBean()");
	void* tb = Invoke<void*>(tb_mem, defaultConstructorPtr);

	free(tb_mem);
}
*/

class SymTestBean2{
public:
	SymTestBean2():data1(100){
		dg_int a = 1 + 3;
		this->data1=a;
	}

private:
	dg_int data1;
	dg_int data2[1024];
};

TEST(Dragon_Lang_Internal_platformTest, Invoke_Class_Size_Check2) {
	SymTestBean2* stb = new SymTestBean2();
	dg_int size = sizeof(*stb);
	SafeDelete(stb);
}

//---------------------------------------------------------------
// int test
void* invoke_test01() {
	int a = 1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test02(int a1) {
	int a = a1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test03(int a1, int b1) {
	int a = a1 + b1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test04(int a1, int b1, int c1) {
	int a = a1 + b1 + c1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test05(int a1, int b1, int c1, int d1) {
	int a = a1 + b1 + c1 + d1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test06(int a1, int b1, int c1, int d1, int e1) {
	int a = a1 + b1 + c1 + d1 + e1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test07(int a1, int b1, int c1, int d1, int e1, int f1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test08(int a1, int b1, int c1, int d1, int e1, int f1, int g1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test09(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test10(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test11(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1, int j1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test12(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1, int j1, int k1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test13(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1, int j1, int k1, int l1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test14(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1, int j1, int k1, int l1, int m1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	int* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args) {
	int a1 = 1;
	int b1 = 2;
	int c1 = 3;
	int d1 = 4;
	int e1 = 5;
	int f1 = 6;
	int g1 = 7;
	int h1 = 8;
	int i1 = 9;
	int j1 = 10;
	int k1 = 11;
	int l1 = 12;
	int m1 = 13;

	invoke_test01();
	invoke_test02(a1);
	invoke_test03(a1, b1);
	invoke_test04(a1, b1, c1);
	invoke_test05(a1, b1, c1, d1);
	invoke_test06(a1, b1, c1, d1, e1);
	invoke_test07(a1, b1, c1, d1, e1, f1);
	invoke_test08(a1, b1, c1, d1, e1, f1, g1);
	invoke_test09(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test10(a1, b1, c1, d1, e1, f1, g1, h1, i1);
	invoke_test11(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1);
	invoke_test12(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1);
	invoke_test13(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1);
	invoke_test14(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}

//----------------------------------------------------------
// short test
void* invoke_test_short_01(short a1, short b1, short c1, short d1, short e1, short f1, short g1, short h1, short i1, short j1, short k1, short l1, short m1) {
	short a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	short* pa = &a;
	return (void*)pa;
}

void* invoke_test_short_02(short a1, short b1, short c1, short d1, short e1, short f1, short g1, short h1) {
	short a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	short* pa = &a;
	return (void*)pa;
}

void* invoke_test_short_03(short a1, short b1, short c1, short d1, short e1, short f1) {
	short a = a1 + b1 + c1 + d1 + e1 + f1;
	short* pa = &a;
	return (void*)pa;
}

void* invoke_test_short_04(short a1, short b1, short c1, short d1) {
	short a = a1 + b1 + c1 + d1;
	short* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_short) {
	short a1 = 1;
	short b1 = 2;
	short c1 = 3;
	short d1 = 4;
	short e1 = 5;
	short f1 = 6;
	short g1 = 7;
	short h1 = 8;
	short i1 = 9;
	short j1 = 10;
	short k1 = 11;
	short l1 = 12;
	short m1 = 13;

	invoke_test_short_04(a1, b1, c1, d1);
	invoke_test_short_03(a1, b1, c1, d1, e1, f1);
	invoke_test_short_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_short_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}


//----------------------------------------------------------
// size_t test
void* invoke_test_size_t_01(size_t a1, size_t b1, size_t c1, size_t d1, size_t e1, size_t f1, size_t g1, size_t h1, size_t i1, size_t j1, size_t k1, size_t l1, size_t m1) {
	size_t a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	size_t* pa = &a;
	return (void*)pa;
}

void* invoke_test_size_t_02(size_t a1, size_t b1, size_t c1, size_t d1, size_t e1, size_t f1, size_t g1, size_t h1) {
	size_t a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	size_t* pa = &a;
	return (void*)pa;
}

void* invoke_test_size_t_03(size_t a1, size_t b1, size_t c1, size_t d1, size_t e1, size_t f1) {
	size_t a = a1 + b1 + c1 + d1 + e1 + f1;
	size_t* pa = &a;
	return (void*)pa;
}

void* invoke_test_size_t_04(size_t a1, size_t b1, size_t c1, size_t d1) {
	size_t a = a1 + b1 + c1 + d1;
	size_t* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_size_t) {
	size_t a1 = 1;
	size_t b1 = 2;
	size_t c1 = 3;
	size_t d1 = 4;
	size_t e1 = 5;
	size_t f1 = 6;
	size_t g1 = 7;
	size_t h1 = 8;
	size_t i1 = 9;
	size_t j1 = 10;
	size_t k1 = 11;
	size_t l1 = 12;
	size_t m1 = 13;

	invoke_test_size_t_04(a1, b1, c1, d1);
	invoke_test_size_t_03(a1, b1, c1, d1, e1, f1);
	invoke_test_size_t_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_size_t_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}

//----------------------------------------------------------
// char test
void* invoke_test_char_01(char a1, char b1, char c1, char d1, char e1, char f1, char g1, char h1, char i1, char j1, char k1, char l1, char m1) {
	char a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	char* pa = &a;
	return (void*)pa;
}

void* invoke_test_char_02(char a1, char b1, char c1, char d1, char e1, char f1, char g1, char h1) {
	char a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	char* pa = &a;
	return (void*)pa;
}

void* invoke_test_char_03(char a1, char b1, char c1, char d1, char e1, char f1) {
	char a = a1 + b1 + c1 + d1 + e1 + f1;
	char* pa = &a;
	return (void*)pa;
}

void* invoke_test_char_04(char a1, char b1, char c1, char d1) {
	char a = a1 + b1 + c1 + d1;
	char* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_char) {
	char a1 = 1;
	char b1 = 2;
	char c1 = 3;
	char d1 = 4;
	char e1 = 5;
	char f1 = 6;
	char g1 = 7;
	char h1 = 8;
	char i1 = 9;
	char j1 = 10;
	char k1 = 11;
	char l1 = 12;
	char m1 = 13;

	invoke_test_char_04(a1, b1, c1, d1);
	invoke_test_char_03(a1, b1, c1, d1, e1, f1);
	invoke_test_char_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_char_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}

//----------------------------------------------------------
// float test
void* invoke_test_float_01(float a1, float b1, float c1, float d1, float e1, float f1, float g1, float h1, float i1, float j1, float k1, float l1, float m1) {
	float a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	float* pa = &a;
	return (void*)pa;
}

void* invoke_test_float_02(float a1, float b1, float c1, float d1, float e1, float f1, float g1, float h1) {
	float a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	float* pa = &a;
	return (void*)pa;
}

void* invoke_test_float_03(float a1, float b1, float c1, float d1, float e1, float f1) {
	float a = a1 + b1 + c1 + d1 + e1 + f1;
	float* pa = &a;
	return (void*)pa;
}

void* invoke_test_float_04(float a1, float b1, float c1, float d1) {
	float a = a1 + b1 + c1 + d1;
	float* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_float) {
	float a1 = 1;
	float b1 = 2;
	float c1 = 3;
	float d1 = 4;
	float e1 = 5;
	float f1 = 6;
	float g1 = 7;
	float h1 = 8;
	float i1 = 9;
	float j1 = 10;
	float k1 = 11;
	float l1 = 12;
	float m1 = 13;

	invoke_test_float_04(a1, b1, c1, d1);
	invoke_test_float_03(a1, b1, c1, d1, e1, f1);
	invoke_test_float_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_float_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}

//----------------------------------------------------------
// double test
void* invoke_test_double_01(double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1, double k1, double l1, double m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_double_02(double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_double_03(double a1, double b1, double c1, double d1, double e1, double f1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_double_04(double a1, double b1, double c1, double d1) {
	double a = a1 + b1 + c1 + d1;
	double* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_double) {
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

	invoke_test_double_04(a1, b1, c1, d1);
	invoke_test_double_03(a1, b1, c1, d1, e1, f1);
	invoke_test_double_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_double_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}


//----------------------------------------------------------
// mix type test
void* invoke_test_mixtype_01(char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_mixtype_02(char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_mixtype_03(char a1, short b1, int c1, size_t d1, double e1, double f1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_mixtype_04(char a1, short b1, int c1, size_t d1) {
	size_t a = a1 + b1 + c1 + d1;
	size_t* pa = &a;
	return (void*)pa;
}

void* invoke_test_mixtype_05(char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1, void* p1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	double* pa = &a;
	return (void*)pa;
}

struct mix {
	char a1;
	short b1;
	int c1;
	size_t d1;
	double e1;
	double f1;
};

void* invoke_test_mixtype_06(mix m, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1, void* p1) {
	int aa = 1 + 2;
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
		+ m1 + aa;
	double* pa = &a;
	return (void*)pa;
}

struct mix2 {
  char a1;
  short b1;
  int c1;
  size_t d1;
  double e1;
  double f1;
};

void* invoke_test_mixtype_07(mix2 m, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1, void* p1) {
	int aa = 1 + 2;
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
		+ m1 + aa;
	double* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_mixtype) {
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

	int max_l = sizeof(long);
	int max_ll = sizeof(long long);
	int max_void_p = sizeof(void*);

	mix m;
	mix2 m2;

	memset(&m, 0, sizeof(mix));
	memset(&m2, 0, sizeof(mix2));

	invoke_test_mixtype_04(a1, b1, c1, d1);
	invoke_test_mixtype_03(a1, b1, c1, d1, e1, f1);
	invoke_test_mixtype_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_mixtype_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
	invoke_test_mixtype_05(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, (void*)(&m1));
	invoke_test_mixtype_06(m, g1, h1, i1, j1, k1, l1, m1, (void*)(&m1));
	invoke_test_mixtype_07(m2, g1, h1, i1, j1, k1, l1, m1, (void*)(&m1));
}

