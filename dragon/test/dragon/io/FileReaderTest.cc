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
 * Created:     2013/12/05
 **********************************************************************/


#include <gtest/gtest.h>

#include <dragon/io/FileReader.h>
#include <dragon/io/FileWriter.h>

#include <dragon/lang/System.h>
#include <dragon/io/File.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/lang/gc/Reference.h>

Import dragon::lang;
Import dragon::io;
Import dragon::util::logging;
Import dragon::lang::gc;

static Logger* logger = Logger::getLogger("dragon::io::FileReaderTest", DEBUG);

TEST(Dragon_Io_FileReaderTest, New) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/file_reader_test/aa.txt");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    String* myWriteStr = new String(L"你好！我的号being有biter!");

    FileWriter* o = new FileWriter(file, false);
    o->append(myWriteStr);
    SafeDelete(o);


    wchar_u buf[512];

    Reader* o2 = new FileReader(file);

    int readSize = o2->read(buf, 512);
    String* myReadStr = new String(buf, 0, readSize);
    EXPECT_TRUE(myReadStr->equals(myWriteStr));

    SafeDelete(o2);

    SafeRelease(myWriteStr);
    SafeRelease(myReadStr);
    SafeDelete(file);
    SafeDelete(filePath);
}