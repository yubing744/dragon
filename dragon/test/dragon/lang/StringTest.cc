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

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <gtest/gtest.h>

#include <dragon.h>
#include <dragon/lang/Arrays.h>
#include <dragon/lang/String.h>


Import dragon::lang;

TEST(Dragon_Lang_String_Test, NewWithBasicChar) {
    String* str = new String("Hello World");
	EXPECT_EQ(11, str->length());

	dg_char ch1 = 'H';
	dg_char ch2 = str->charAt(0);
	
	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);
}


TEST(Dragon_Lang_String_Test, NewWithChar) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	dg_char ch1 = L'C';
	dg_char ch2 = str->charAt(0);

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, NewWithString) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	String* str2 = new String(str);

	dg_char ch1 = L'C';
	dg_char ch2 = str2->charAt(0);

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str2);
    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, NewWithStringOffset) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	String* str2 = new String(str);

	dg_char ch1 = L'C';
	dg_char ch2 = str2->charAt(0);

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);  
    SafeDelete(str2);  
}

TEST(Dragon_Lang_String_Test, toChars_01) {
    String* str = new String(L"CN China!");
    EXPECT_EQ(9, str->length());

    const dg_char* data = str->toChars();

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, toCharArray) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	Array<dg_char> charArray = str->toCharArray();

	dg_char ch1 = L'C';
	dg_char ch2 = charArray[0];

	dg_boolean isEqual = (ch1 == ch2);
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str);    
}

TEST(Dragon_Lang_String_Test, toChars) {
    String* str = new String(L"CN China!");
	EXPECT_EQ(9, str->length());

	const dg_char* charArray = str->toChars();

	dg_char ch1 = L'C';
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

// Test String Encoding
static dg_byte utf8_data[] = {
    0x41, 
    0x42, 
    0xe4, 0xbd, 0xa0,
    0xe5, 0xa5, 0xbd, 
    0x41, 
    0x42
};
static dg_int utf8_data_size = sizeof(utf8_data) / sizeof(dg_byte);

static dg_byte ucs2_big_data[] = {
    0x00, 0x41, 
    0x00, 0x42, 
    0x4f, 0x60, 
    0x59, 0x7d, 
    0x00, 0x41, 
    0x00, 0x42
};
static dg_int ucs2_big_data_size = sizeof(ucs2_big_data) / sizeof(dg_byte);

static dg_byte ucs2_little_data[] = {
    0x41, 0x00, 
    0x42, 0x00, 
    0x60, 0x4f, 
    0x7d, 0x59, 
    0x41, 0x00, 
    0x42, 0x00
};
static dg_int ucs2_little_data_size = sizeof(ucs2_little_data) / sizeof(dg_byte);

static dg_byte ucs4_big_data[] = {
    0x00, 0x00, 0x00, 0x41, 
    0x00, 0x00, 0x00, 0x42, 
    0x00, 0x00, 0x4f, 0x60, 
    0x00, 0x00, 0x59, 0x7d, 
    0x00, 0x00, 0x00, 0x41, 
    0x00, 0x00, 0x00, 0x42
};
static dg_int ucs4_big_data_size = sizeof(ucs4_big_data) / sizeof(dg_byte);

static dg_byte ucs4_little_data[] = {
    0x41, 0x00, 0x00, 0x00,
    0x42, 0x00, 0x00, 0x00,
    0x60, 0x4f, 0x00, 0x00,
    0x7d, 0x59, 0x00, 0x00,
    0x41, 0x00, 0x00, 0x00,
    0x42, 0x00, 0x00, 0x00
};
static dg_int ucs4_little_data_size = sizeof(ucs4_little_data) / sizeof(dg_byte);

TEST(Dragon_Lang_String_Test, NewWithBytes) {
    String* str1 = new String(Array<dg_byte>(utf8_data, utf8_data_size), 0, utf8_data_size, "UTF-8");

    dg_boolean isEqual = str1->charAt(0) == 'A';
    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(str1);
}

TEST(Dragon_Lang_String_Test, getBytes) {
    String* str1 = new String(Array<dg_byte>(utf8_data, utf8_data_size), 0, utf8_data_size, "UTF-8");
    Array<dg_byte> bytes = str1->getBytes("UTF-8");

    const dg_byte* data = bytes.raw();
    ASSERT_TRUE(data != NULL);

    for (dg_int i=0; i<utf8_data_size; i++) {
        dg_byte src_byte = utf8_data[i];
        dg_byte out_byte = data[i];

        EXPECT_EQ(src_byte, out_byte) << "src_byte and out_byte at index" << i;
    }

    SafeDelete(str1);
}

TEST(Dragon_Lang_String_Test, convertBytesFromUTF8ToUCS4_little) {
    String* str1 = new String(Array<dg_byte>(utf8_data, utf8_data_size), 0, utf8_data_size, "UTF-8");
    Array<dg_byte> bytes = str1->getBytes("UCS4-little");

    const dg_byte* data = bytes.raw();
    ASSERT_TRUE(data != NULL);

    for (dg_int i=0; i<ucs4_little_data_size; i++) {
        dg_byte src_byte = ucs4_little_data[i];
        dg_byte out_byte = data[i];

        EXPECT_EQ(src_byte, out_byte) << "src_byte and out_byte at index" << i;
    }

    SafeDelete(str1);
}

TEST(Dragon_Lang_String_Test, convertBytesFromUTF8ToUCS4_big) {
    String* str1 = new String(Array<dg_byte>(utf8_data, utf8_data_size), 0, utf8_data_size, "UTF-8");
    Array<dg_byte> bytes = str1->getBytes("UCS4-big");

    const dg_byte* data = bytes.raw();
    ASSERT_TRUE(data != NULL);

    for (dg_int i=0; i<ucs4_big_data_size; i++) {
        dg_byte src_byte = ucs4_big_data[i];
        dg_byte out_byte = data[i];

        EXPECT_EQ(src_byte, out_byte) << "src_byte and out_byte at index" << i;
    }

    SafeDelete(str1);
}

TEST(Dragon_Lang_String_Test, convertBytesFromUTF8ToUCS2_little) {
    String* str1 = new String(Array<dg_byte>(utf8_data, utf8_data_size), 0, utf8_data_size, "UTF-8");
    Array<dg_byte> bytes = str1->getBytes("UCS2-little");

    const dg_byte* data = bytes.raw();
    ASSERT_TRUE(data != NULL);

    for (dg_int i=0; i<ucs2_little_data_size; i++) {
        dg_byte src_byte = ucs2_little_data[i];
        dg_byte out_byte = data[i];

        EXPECT_EQ(src_byte, out_byte) << "src_byte and out_byte at index" << i;
    }

    SafeDelete(str1);
}

TEST(Dragon_Lang_String_Test, convertBytesFromUTF8ToUCS2_big) {
    String* str1 = new String(Array<dg_byte>(utf8_data, utf8_data_size), 0, utf8_data_size, "UTF-8");
    Array<dg_byte> bytes = str1->getBytes("UCS2-big");

    const dg_byte* data = bytes.raw();
    ASSERT_TRUE(data != NULL);

    for (dg_int i=0; i<ucs2_big_data_size; i++) {
        dg_byte src_byte = ucs2_big_data[i];
        dg_byte out_byte = data[i];

        EXPECT_EQ(src_byte, out_byte) << "src_byte and out_byte at index" << i;
    }

    SafeDelete(str1);
}

TEST(Dragon_Lang_String_Test, convertBytesFromUTF8ToUCS2_big_FOR_WCHAR) {
    String* str1 = new String(L"AB你好AB");

    Array<dg_byte> bytes = str1->getBytes("UCS2-big");

    const dg_byte* data = bytes.raw();
    ASSERT_TRUE(data != NULL);

    for (dg_int i=0; i<ucs2_big_data_size; i++) {
        dg_byte src_byte = ucs2_big_data[i];
        dg_byte out_byte = data[i];

        EXPECT_EQ(src_byte, out_byte) << "src_byte and out_byte at index" << i;
    }

    SafeDelete(str1);
}

TEST(Dragon_Lang_String_Test, compareTo01) {
    String* str1 = new String("");
    String* str2 = new String("");

    dg_int b = str1->compareTo(str2);

    EXPECT_EQ(0, b);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareTo02) {
    String* str1 = new String("a");
    String* str2 = new String("a");

    dg_int b = str1->compareTo(str2);

    EXPECT_EQ(0, b);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareTo03) {
    String* str1 = new String("ab");
    String* str2 = new String("ab");

    dg_int b = str1->compareTo(str2);

    EXPECT_EQ(dg_true, b == 0);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareTo04) {
    String* str1 = new String("");
    String* str2 = new String("a");

    dg_int b = str1->compareTo(str2);

    EXPECT_EQ(dg_true, b < 0);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareTo05) {
    String* str1 = new String("a");
    String* str2 = new String("");

    dg_int b = str1->compareTo(str2);

    EXPECT_EQ(dg_true, b > 0);

    SafeDelete(str1);
    SafeDelete(str2);
}


TEST(Dragon_Lang_String_Test, compareTo06) {
    String* str1 = new String("ab");
    String* str2 = new String("ac");

    dg_int b = str1->compareTo(str2);

    EXPECT_EQ(dg_true, b < 0);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareTo07) {
    String* str1 = new String("ad");
    String* str2 = new String("ac");

    dg_int b = str1->compareTo(str2);

    EXPECT_EQ(dg_true, b > 0);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareToIgnoreCase01) {
    String* str1 = new String("");
    String* str2 = new String("");

    dg_int b = str1->compareToIgnoreCase(str2);

    EXPECT_EQ(0, b);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareToIgnoreCase02) {
    String* str1 = new String("a");
    String* str2 = new String("a");

    dg_int b = str1->compareToIgnoreCase(str2);

    EXPECT_EQ(0, b);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareToIgnoreCase03) {
    String* str1 = new String("Ab");
    String* str2 = new String("aB");

    dg_int b = str1->compareToIgnoreCase(str2);

    EXPECT_EQ(dg_true, b == 0);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareToIgnoreCase04) {
    String* str1 = new String("");
    String* str2 = new String("a");

    dg_int b = str1->compareToIgnoreCase(str2);

    EXPECT_EQ(dg_true, b < 0);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareToIgnoreCase05) {
    String* str1 = new String("a");
    String* str2 = new String("");

    dg_int b = str1->compareToIgnoreCase(str2);

    EXPECT_EQ(dg_true, b > 0);

    SafeDelete(str1);
    SafeDelete(str2);
}


TEST(Dragon_Lang_String_Test, compareToIgnoreCase06) {
    String* str1 = new String("aB");
    String* str2 = new String("ac");

    dg_int b = str1->compareTo(str2);

    EXPECT_EQ(dg_true, b < 0);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, compareToIgnoreCase07) {
    String* str1 = new String("AD");
    String* str2 = new String("ac");

    dg_int b = str1->compareToIgnoreCase(str2);

    EXPECT_EQ(dg_true, b > 0);

    SafeDelete(str1);
    SafeDelete(str2);
}


TEST(Dragon_Lang_String_Test, hashCode) {
    String* str1 = new String("ab");
    String* str2 = new String("ab");

    dg_int b1 = str1->hashCode();
    dg_int b2 = str2->hashCode();

    EXPECT_EQ(dg_true, b1 == b2);

    SafeDelete(str1);
    SafeDelete(str2);
}

TEST(Dragon_Lang_String_Test, concat) {
    String* result = new String("abab");
    String* str1 = new String("ab");
    String* str2 = new String("ab");

    String* ret = str1->concat(str2);
    dg_boolean isEqual = ret->equals(result);

    EXPECT_EQ(dg_true, isEqual);

    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(str2);

    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, trim) {
    String* result = new String("abab");
    String* str1 = new String("  abab");

    String* ret = str1->trim();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, trim02) {
    String* result = new String("abab");
    String* str1 = new String("  abab  ");

    String* ret = str1->trim();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, trim03) {
    String* result = new String("abab");
    String* str1 = new String("abab  ");

    String* ret = str1->trim();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, trim04) {
    String* result = new String("abab");
    String* str1 = new String("abab\t");

    String* ret = str1->trim();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}


TEST(Dragon_Lang_String_Test, trim05) {
    String* result = new String("abab");
    String* str1 = new String("abab");

    String* ret = str1->trim();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, toUpperCase) {
    String* result = new String("ABAB");
    String* str1 = new String("abab");

    String* ret = str1->toUpperCase();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, toUpperCase02) {
    String* result = new String("ABAB");
    String* str1 = new String("abaB");

    String* ret = str1->toUpperCase();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}


TEST(Dragon_Lang_String_Test, toLowerCase) {
    String* result = new String("abab");
    String* str1 = new String("ABAB");

    String* ret = str1->toLowerCase();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, toLowerCase02) {
    String* result = new String("abab");
    String* str1 = new String("abaB");

    String* ret = str1->toLowerCase();
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, replaceAll) {
    String* result = new String("Hello Baby, my Baby");
    String* str1 = new String("Hello World, my World");
    String* str2 = new String("World");
    String* str3 = new String("Baby");

    String* ret = str1->replaceAll(str2, str3);
    ASSERT_EQ(dg_true, ret!=null);
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str3);
    SafeDelete(str2);
    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, toStringInteger) {
    String* result = new String("1234");

    String* ret = String::valueOf(1234);
    ASSERT_EQ(dg_true, ret!=null);
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, format) {
    String* result = new String("abc , he he");
    String* str1 = new String("%s , he he");

    String* ret = String::format(str1, "abc");
    ASSERT_EQ(dg_true, ret!=null);
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(str1);
    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, format02) {
    String* result = new String("abc , he he");

    String* ret = String::format("%s , he he", "abc");
    ASSERT_EQ(dg_true, ret!=null);
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);

    SafeDelete(result);
}

TEST(Dragon_Lang_String_Test, format03) {
    String* result = new String("abc32");

    String* ret = String::format("%s%d", "abc", 32);
    ASSERT_EQ(dg_true, ret!=null);
    dg_boolean isEqual = ret->equals(result);
    EXPECT_EQ(dg_true, isEqual);
    SafeDelete(ret);
    
    SafeDelete(result);
}


