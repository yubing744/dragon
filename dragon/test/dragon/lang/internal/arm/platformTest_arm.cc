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

TEST(Dragon_Lang_Internal_platformTest_arm, Invoke_Multi_Args_char) {
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