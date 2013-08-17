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