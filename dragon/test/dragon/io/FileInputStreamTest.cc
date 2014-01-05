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
 * Created:     2013/11/17
 **********************************************************************/

#include <gtest/gtest.h>

#include <dragon/lang/System.h>
#include <dragon/io/File.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/lang/gc/Reference.h>
#include <dragon/io/FileInputStream.h>

Import dragon::lang;
Import dragon::io;
Import dragon::util::logging;
Import dragon::lang::gc;

static Logger* logger = Logger::getLogger("dragon::io::FileInputStreamTest", INFO);

TEST(Dragon_Io_FileInputStreamTest, New) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/dragon_test/01");
    String* fullPath = base->concat(path);

    const Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->debug(utf8Path.raw());

    File* o = new File(fullPath);
    ASSERT_TRUE(o->mkdirs());

    File* newFile = new File(o, "test.txt");

    FileInputStream* fis = new FileInputStream(newFile);
    SafeDelete(fis);

    SafeDelete(o);
    
    SafeDelete(path);
    SafeDelete(fullPath);
}