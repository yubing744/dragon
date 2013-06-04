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

#include <dragon/lang/String.h>

#include <gtest/gtest.h>

Import dragon::lang;

TEST(Dragon_Lang_String_Test, NewWithBasicChar) {
    String* str = new String("Hello World");
	EXPECT_EQ(11, str->length());

	Char ch1 = ToChar('H');
	Char ch2 = str->charAt(0);
	
	Boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(true, isEqual);

    SafeDelete(str);
}


TEST(Dragon_Lang_String_Test, NewWithChar) {
    String* str = new String(L"你好！");
	EXPECT_EQ(3, str->length());

	Char ch1 = ToChar(L'你');
	Char ch2 = str->charAt(0);

	Boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(true, isEqual);

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, NewWithString) {
    String* str = new String(L"你好！");
	EXPECT_EQ(3, str->length());

	String* str2 = new String(str);

	Char ch1 = ToChar(L'你');
	Char ch2 = str2->charAt(0);

	Boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(true, isEqual);

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, NewWithStringOffset) {
    String* str = new String(L"你好！");
	EXPECT_EQ(3, str->length());

	String* str2 = new String(str);

	Char ch1 = ToChar(L'你');
	Char ch2 = str2->charAt(0);

	Boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(true, isEqual);

    SafeDelete(str);  
    SafeDelete(str2);  
}

TEST(Dragon_Lang_String_Test, toCharArray) {
    String* str = new String(L"你好！");
	EXPECT_EQ(3, str->length());

	Array<Char> charArray = str->toCharArray();

	Char ch1 = ToChar(L'你');
	Char ch2 = charArray[0];

	Boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(true, isEqual);

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, toChars) {
    String* str = new String(L"你好！");
	EXPECT_EQ(3, str->length());

	const Char* charArray = str->toChars();

	Char ch1 = ToChar(L'你');
	Char ch2 = charArray[0];

	Boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(true, isEqual);

    SafeDelete(str);    
}


TEST(Dragon_Lang_String_Test, strEquals) {
    String* str = new String(L"你好！");
	EXPECT_EQ(3, str->length());

	const Char* charArray = str->toChars();
	String* str2 = new String(charArray);

	Boolean isEqual = (str->equals(str2));
    EXPECT_EQ(true, isEqual);

    SafeDelete(str);  
    SafeDelete(str2);  
}

