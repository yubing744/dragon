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
#include <dragon/lang/StringBuffer.h>


Import dragon::lang;

TEST(Dragon_Lang_StringBuffer_Test, BasicNew) {
	StringBuffer* sb = new StringBuffer();
	SafeDelete(sb);
}

TEST(Dragon_Lang_StringBuffer_Test, BasicNewWithCapcity) {
	StringBuffer* sb = new StringBuffer(10);
	SafeDelete(sb);
}

TEST(Dragon_Lang_StringBuffer_Test, AppendString) {
	StringBuffer* sb = new StringBuffer();

	String* str2 = new String("Hello World");

	sb->append("Hello");

	String* b = new String(" ");
	sb->append(b);
	SafeDelete(b);

	sb->append("World");

	String* str = sb->toString();
	dg_boolean isEqual = (str->equals(str2));
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(str);

    SafeDelete(str2);

	SafeDelete(sb);
}

TEST(Dragon_Lang_StringBuffer_Test, AppendBoolean) {
	StringBuffer* sb = new StringBuffer();

	String* str2 = new String("This is true");

	String* a = new String("This is ");
	sb->append(a);
	SafeDelete(a);

	sb->append(true);

	String* str = sb->toString();
	dg_boolean isEqual = (str->equals(str2));
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(str);
    
    SafeDelete(str2);

	SafeDelete(sb);
}

TEST(Dragon_Lang_StringBuffer_Test, AppendInt_01) {
	StringBuffer* sb = new StringBuffer();

	String* str2 = new String("This is number 1");

	String* a = new String("This is number ");
	sb->append(a);
	SafeDelete(a);

	sb->append(1);

	String* str = sb->toString();
	dg_boolean isEqual = (str->equals(str2));
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(str);
    
    SafeDelete(str2);

	SafeDelete(sb);
}

TEST(Dragon_Lang_StringBuffer_Test, AppendInt_02) {
	StringBuffer* sb = new StringBuffer();

	String* str2 = new String("This is number 0");

	String* a = new String("This is number ");
	sb->append(a);
	SafeDelete(a);

	sb->append(0);

	String* str = sb->toString();
	dg_boolean isEqual = (str->equals(str2));
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(str);
    
    SafeDelete(str2);

	SafeDelete(sb);
}

TEST(Dragon_Lang_StringBuffer_Test, AppendInt_03) {
	StringBuffer* sb = new StringBuffer();

	String* str2 = new String("This is number -1");

	String* a = new String("This is number ");
	sb->append(a);
	SafeDelete(a);

	sb->append(-1);

	String* str = sb->toString();
	dg_boolean isEqual = (str->equals(str2));
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(str);
    
    SafeDelete(str2);

	SafeDelete(sb);
}


