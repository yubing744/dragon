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
 * Created:     2014/03/16
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragon/io/File.h>
#include <dragon/lang/System.h>
#include <dragon/util/Scanner.h>
#include <dragon/util/logging/Logger.h>

Import dragon::io;
Import dragon::util;
Import dragon::lang;
Import dragon::util::logging;

static Logger* logger = Logger::getLogger("ScannerTest", DEBUG);

TEST(Dragon_Util_ScannerTest, New) {
    File* file = new File(".");
    String* path = file->getAbsolutePath();
    char* utf8Path = path->toUTF8String();
    logger->debug("absolute path: %s", utf8Path);
    SafeFree(utf8Path);
    SafeRelease(path);
    SafeRelease(file);
}

TEST(Dragon_Util_ScannerTest, New2) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/cube.obj");
    File* file = new File(base, filePath);

    Scanner* scanner = new Scanner(file);
    SafeDelete(scanner);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Dragon_Util_ScannerTest, New3) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/cube.obj");
    File* file = new File(base, filePath);
    ASSERT_TRUE(file->exists());

    Scanner* scanner = new Scanner(file);

    ASSERT_TRUE(scanner->hasNext());
    
    String* str = scanner->next();
    char* utf8Str = str->toUTF8String();
    ASSERT_STREQ("v", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);    

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);  

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("-1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str); 

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("v", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str); 

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);    

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("-1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);  

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("-1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);


    SafeDelete(scanner);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Dragon_Util_ScannerTest, New4) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/cube.obj");
    File* file = new File(base, filePath);
    ASSERT_TRUE(file->exists());

    Scanner* scanner = new Scanner(file);

    ASSERT_TRUE(scanner->hasNext());
    
    String* str = scanner->next();
    char* utf8Str = str->toUTF8String();
    ASSERT_STREQ("v", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);

    // 1.000000
    ASSERT_TRUE(scanner->hasNextFloat());
    float a1 = scanner->nextFloat();
    ASSERT_FLOAT_EQ(1.000000f, a1);
  
    /*
    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);  

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("-1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str); 

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("v", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str); 

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);    

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("-1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);  

    str = scanner->next();
    utf8Str = str->toUTF8String();
    ASSERT_STREQ("-1.000000", utf8Str);
    SafeFree(utf8Str);
    SafeRelease(str);
    */

    SafeDelete(scanner);

    SafeRelease(file);
    SafeRelease(filePath);
}

