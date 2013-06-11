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

#include <gtest/gtest.h>

#include <dragon/lang/String.h>
#include <dragon/lang/basic_type.h>


Import dragon::lang;

TEST(Dragon_Lang_String_Test, NewWithBasicChar) {
    String* str = new String("Hello World");
	EXPECT_EQ(11, str->length());

	dg_char ch1 = ToChar('H');
	dg_char ch2 = str->charAt(0);
	
	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);
}


TEST(Dragon_Lang_String_Test, NewWithChar) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	dg_char ch1 = ToChar(L'C');
	dg_char ch2 = str->charAt(0);

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, NewWithString) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	String* str2 = new String(str);

	dg_char ch1 = ToChar(L'C');
	dg_char ch2 = str2->charAt(0);

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, NewWithStringOffset) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	String* str2 = new String(str);

	dg_char ch1 = ToChar(L'C');
	dg_char ch2 = str2->charAt(0);

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);  
    SafeDelete(str2);  
}

TEST(Dragon_Lang_String_Test, toCharArray) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	Array<dg_char> charArray = str->toCharArray();

	dg_char ch1 = ToChar(L'C');
	dg_char ch2 = charArray[0];

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, toChars) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	const dg_char* charArray = str->toChars();

	dg_char ch1 = ToChar(L'C');
	dg_char ch2 = charArray[0];

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);    
}


TEST(Dragon_Lang_String_Test, strEquals) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	const dg_char* charArray = str->toChars();
	String* str2 = new String(charArray);

	dg_boolean isEqual = (str->equals(str2));
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);  
    SafeDelete(str2);  
}


TEST(Dragon_Lang_String_Test, startsWith_empty_str) {
    String* str1 = new String(L"CN China!");
	String* str2 = new String(L"");

	dg_boolean isEqual = str1->startsWith(str2);
    EXPECT_EQ(true, isEqual);

    SafeDelete(str1);  
    SafeDelete(str2);  
}

TEST(Dragon_Lang_String_Test, startsWith_normal) {
    String* str1 = new String(L"CN China!");
	String* str2 = new String(L"CN");

	dg_boolean isEqual = str1->startsWith(str2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str1);  
    SafeDelete(str2);  
}

TEST(Dragon_Lang_String_Test, startsWith_full_match) {
    String* str1 = new String(L"CN China!");
	String* str2 = new String(L"CN China!");

	dg_boolean isEqual = str1->startsWith(str2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str1);  
    SafeDelete(str2);  
}

TEST(Dragon_Lang_String_Test, startsWith_more_lenth_than) {
    String* str1 = new String(L"CN China!");
	String* str2 = new String(L"CN China!DD");

	dg_boolean isEqual = str1->startsWith(str2);
    EXPECT_EQ(dg_false, isEqual);

    SafeDelete(str1);  
    SafeDelete(str2);  
}

TEST(Dragon_Lang_String_Test, startsWith_with_toffet) {
    String* str1 = new String(L"I'm a CN China!");
	String* str2 = new String(L"CN Chi");

	dg_boolean isEqual = str1->startsWith(str2, 6);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str1);  
    SafeDelete(str2);  
}

TEST(Dragon_Lang_String_Test, endsWith) {
    String* str1 = new String(L"I'm a CN China!");
	String* str2 = new String(L"China!");

	dg_boolean isEqual = str1->endsWith(str2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str1);  
    SafeDelete(str2);  
}