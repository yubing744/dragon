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

/*
Import dragon::lang::internal;

TEST(Dragon_Lang_Internal_SymbolManglingTest, queryPrefixSymbol) {
	EXPECT_EQ("_ZN", query_prefix_symbol());
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, queryNameEndSymbol) {
	EXPECT_EQ("E", query_name_end_symbol());
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, queryBasicTypeSymbol) {
	EXPECT_EQ("c", query_byte_symbol());
	EXPECT_EQ("s", query_short_symbol());
	EXPECT_EQ("i", query_int_symbol());
	EXPECT_EQ("x", query_long_symbol());
	EXPECT_EQ("f", query_float_symbol());
	EXPECT_EQ("d", query_double_symbol());
	EXPECT_EQ("j", query_char_symbol());
	EXPECT_EQ("b", query_boolean_symbol());
	EXPECT_EQ("v", query_void_symbol());
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, mangling_byte) {
	EXPECT_EQ("_ZN6dragon4lang8internal11SymTestBean4testEc", Mangling("dragon::lang::internal::SymTestBean::test(dg_byte)"));
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, mangling_void) {
	EXPECT_EQ("_ZN6dragon4lang8internal11SymTestBean4testEv", Mangling("dragon::lang::internal::SymTestBean::test()"));
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, mangling_CC) {
	EXPECT_EQ("_ZN6dragon4lang8internal11SymTestBeanC1Ev", Mangling("dragon::lang::internal::SymTestBean::SymTestBean()"));
}


TEST(Dragon_Lang_Internal_platformTest, Demanle) {
	char* cc = Demangle("_ZN6dragon4lang8internal11SymTestBean4testEc");
	EXPECT_STREQ("dragon::lang::internal::SymTestBean::test(char)", cc);
	free(cc);
}

TEST(Dragon_Lang_Internal_platformTest, Demanle_CC) {
	char* cc = Demangle("_ZN6dragon4lang8internal11SymTestBeanC1Ev");
	EXPECT_STREQ("dragon::lang::internal::SymTestBean::SymTestBean()", cc);
	free(cc);
}
*/