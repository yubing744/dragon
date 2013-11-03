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
 * Created:     2013/11/02
 **********************************************************************/


#include <gtest/gtest.h>

#include <dragon/lang/System.h>
#include <dragon/io/File.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/lang/gc/Reference.h>

Import dragon::lang;
Import dragon::io;
Import dragon::util::logging;
Import dragon::lang::gc;

static Logger* logger = Logger::getLogger("dragon::io::FileTest", DEBUG);

TEST(Dragon_Io_FileTest, New) {
    File* o = new File();
    SafeDelete(o);
}

TEST(Dragon_Io_FileTest, NewWithPath) {
    File* o = new File("/var/www");
    SafeDelete(o);
}

TEST(Dragon_Io_FileTest, NewWithWcharPath) {
    File* o = new File(L"/var/www");
    SafeDelete(o);
}

TEST(Dragon_Io_FileTest, NewWithAnatherPath) {
    String* path = new String(L"/var/www");
    File* o = new File(path);
    SafeDelete(o);
    SafeDelete(path);
}

// exists
TEST(Dragon_Io_FileTest, Exists01) {
    String* path = new String(L"/ksjfdlksjdflsk/sdfsddf");
    File* o = new File(path);
    ASSERT_FALSE(o->exists());
    SafeDelete(o);
    SafeDelete(path);
}

TEST(Dragon_Io_FileTest, Exists02) {
    String* path = new String(L"/etc");
    File* o = new File(path);
    ASSERT_TRUE(o->exists());
    SafeDelete(o);
    SafeDelete(path);
}

TEST(Dragon_Io_FileTest, Exists03) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截图");
    File* o = new File(path);
    ASSERT_TRUE(o->exists());
    SafeDelete(o);
    SafeDelete(path);
}

TEST(Dragon_Io_FileTest, Exists04) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截2");
    File* o = new File(path);
    ASSERT_FALSE(o->exists());
    SafeDelete(o);
    SafeDelete(path);
}

// isDirectory
TEST(Dragon_Io_FileTest, isDirectory01) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截2");
    File* o = new File(path);
    ASSERT_FALSE(o->isDirectory());
    SafeDelete(o);
    SafeDelete(path);
}

TEST(Dragon_Io_FileTest, isDirectory02) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截图");
    File* o = new File(path);
    ASSERT_TRUE(o->isDirectory());
    SafeDelete(o);
    SafeDelete(path);
}

TEST(Dragon_Io_FileTest, isDirectory03) {
    String* path = new String(L"/etc");
    File* o = new File(path);
    ASSERT_TRUE(o->isDirectory());
    SafeDelete(o);
    SafeDelete(path);
}

// isFile
TEST(Dragon_Io_FileTest, isFile01) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截2");
    File* o = new File(path);
    ASSERT_FALSE(o->isFile());
    SafeDelete(o);
    SafeDelete(path);
}

// mkdir
TEST(Dragon_Io_FileTest, mkdir01) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截3");
    File* o = new File(path);
    ASSERT_TRUE(o->mkdir());
    SafeDelete(o);
    SafeDelete(path);
}

TEST(Dragon_Io_FileTest, mkdir02) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截3/abc2/bcdsdf/sdfsdf2");
    File* o = new File(path);
    ASSERT_FALSE(o->mkdir());
    SafeDelete(o);
    SafeDelete(path);
}

// mkdirs
TEST(Dragon_Io_FileTest, mkdirs01) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截3/abc/bcdsdf/sdfsdf");
    File* o = new File(path);
    ASSERT_TRUE(o->mkdirs());
    SafeDelete(o);
    SafeDelete(path);
}

/* isHidden
TEST(Dragon_Io_FileTest, isHidden01) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截3/abc/bcdsdf/sdfsdf");
    File* o = new File(path);
    ASSERT_FALSE(o->isHidden());
    SafeDelete(o);
    SafeDelete(path);
}
*/

// canExecute
TEST(Dragon_Io_FileTest, canExecute01) {
    String* path = new String(L"/Users/yubing/Dropbox/屏幕截3/abc/bcdsdf/sdfsdf");
    File* o = new File(path);
    ASSERT_TRUE(o->canExecute());
    SafeDelete(o);
    SafeDelete(path);
}

TEST(Dragon_Io_FileTest, canExecute02) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/Dropbox/屏幕截3/abc/bcdsdf/sdfsdf");
    String* fullPath = base->concat(path);

    Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->info(utf8Path);

    File* o = new File(fullPath);
    ASSERT_TRUE(o->canExecute());
    SafeDelete(o);

    SafeDelete(path);
    SafeDelete(fullPath);
}


TEST(Dragon_Io_FileTest, delete01) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/dragon_test/01");
    String* fullPath = base->concat(path);

    const Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->info(utf8Path);

    File* o = new File(fullPath);
    ASSERT_TRUE(o->mkdirs());
    ASSERT_TRUE(o->del());
    SafeDelete(o);

    SafeDelete(path);
    SafeDelete(fullPath);
}

TEST(Dragon_Io_FileTest, lenght01) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/dragon_test/01");
    String* fullPath = base->concat(path);

    const Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->info(utf8Path);

    File* o = new File(fullPath);
    ASSERT_TRUE(o->mkdirs());
    ASSERT_TRUE(o->length() > 0);
    SafeDelete(o);

    SafeDelete(path);
    SafeDelete(fullPath);
}

TEST(Dragon_Io_FileTest, getName01) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/dragon_test/01");
    String* fullPath = base->concat(path);

    const Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->info(utf8Path.raw());

    File* o = new File(fullPath);
    ASSERT_TRUE(o->mkdirs());

    String* name = o->getName();
    const Array<char> utf8Name = name->getBytes("UTF-8");
    EXPECT_STREQ("01", utf8Name);

    SafeDelete(o);

    SafeDelete(name);

    SafeDelete(path);
    SafeDelete(fullPath);
}

TEST(Dragon_Io_FileTest, getParent01) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/dragon_test/01");
    String* fullPath = base->concat(path);

    const Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->info(utf8Path.raw());

    File* o = new File(fullPath);
    ASSERT_TRUE(o->mkdirs());

    String* parentPath = o->getParent();
    String* rpath = parentPath->substring(base->length());
    const Array<char> utf8Name = rpath->getBytes("UTF-8");
    EXPECT_STREQ("/dragon_test", utf8Name);

    SafeDelete(o);

    SafeDelete(rpath);
    SafeDelete(parentPath);
    
    SafeDelete(path);
    SafeDelete(fullPath);
}

// list files
TEST(Dragon_Io_FileTest, list01) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/dragon_test/list_files");
    String* fullPath = base->concat(path);

    const Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->info(utf8Path.raw());

    File* o = new File(fullPath);
    ASSERT_TRUE(o->mkdirs());

    for (int i=0; i<5; i++) {
        String* tmpName = String::format("test%d", i);

        File* file = new File(o, tmpName);
        file->mkdir();

        SafeDelete(file);
        SafeDelete(tmpName);
    }

    Array<String*> fileNames = o->list();
    EXPECT_EQ(5, fileNames.length());

    for (int i=0; i<fileNames.length(); i++) {
        String* name = fileNames[i];
        SafeDelete(name);
    }

    fileNames.release();

    SafeDelete(o);
    
    SafeDelete(path);
    SafeDelete(fullPath);
}

// list files
// 
// 
class MyFileNameFilter implements(FilenameFilter) {
public:
    virtual bool accept(const File* dir, const String* name) const {
        if (name->endsWith("2")) {
            return true;
        }

        return false;
    }
};

TEST(Dragon_Io_FileTest, listWithFilter01) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/dragon_test/list_files");
    String* fullPath = base->concat(path);

    const Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->info(utf8Path.raw());

    File* o = new File(fullPath);
    ASSERT_TRUE(o->mkdirs());

    for (int i=0; i<5; i++) {
        String* tmpName = String::format("test%d", i);

        File* file = new File(o, tmpName);
        file->mkdir();

        SafeDelete(file);
        SafeDelete(tmpName);
    }

    MyFileNameFilter* filter = new MyFileNameFilter();

    Array<String*> fileNames = o->list(filter);
    EXPECT_EQ(1, fileNames.length());

    for (int i=0; i<fileNames.length(); i++) {
        String* name = fileNames[i];

        const Array<char> utf8Name = name->getBytes("UTF-8");
        logger->info("release fileName: %s", utf8Name.raw());

        SafeDelete(name);
    }

    fileNames.release();

    SafeDelete(filter);

    SafeDelete(o);
    
    SafeDelete(path);
    SafeDelete(fullPath);
}

// list files
// 
// 
class MyFileFilter implements(FileFilter) {
public:
    virtual bool accept(const File* file) const {
        Ref<String> name = file->getName();

        if (name->endsWith("2")) {
            return true;
        }

        return false;
    }
};

TEST(Dragon_Io_FileTest, listWithFileFilter01) {
    const String* base = System::getProperty("HOME");
    String* path = new String(L"/dragon_test/list_files");
    String* fullPath = base->concat(path);

    const Array<char> utf8Path = fullPath->getBytes("UTF-8");
    logger->info(utf8Path.raw());

    File* o = new File(fullPath);
    ASSERT_TRUE(o->mkdirs());

    for (int i=0; i<5; i++) {
        String* tmpName = String::format("test%d", i);

        File* file = new File(o, tmpName);
        file->mkdir();

        SafeDelete(file);
        SafeDelete(tmpName);
    }

    MyFileFilter* filter = new MyFileFilter();

    Array<File*> files = o->listFiles(filter);
    EXPECT_EQ(1, files.length());

    for (int i=0; i<files.length(); i++) {
        File* file = files[i];
        SafeDelete(file);
    }

    files.release();

    SafeDelete(filter);

    SafeDelete(o);
    
    SafeDelete(path);
    SafeDelete(fullPath);
}


