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
 * Created:     2014/01/12
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragonx/xml/io/XMLReader.h>

#include <gtest/gtest.h>

#include <dragon/lang/System.h>

#include <dragon/io/File.h>
#include <dragon/io/FileInputStream.h>
#include <dragon/io/FileOutputStream.h>

#include <dragonx/audio/io/AudioIO.h>
#include <dragon/util/logging/Logger.h>


Import dragon::io;
Import dragon::lang;
Import dragonx::audio::io;

Import dragon::util::logging;

static Logger* logger = Logger::getLogger("dragonx::audio::io::AudioIOTest", DEBUG);

Import dragonx::audio::io;

TEST(Dragonx_Audio_Io_AudioIOTest, ReadWav01) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/audio_test/Alarm09.wav");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);

        AudioClip* clip = AudioIO::read(fis, "WAV");
        ASSERT_TRUE(clip != null);

        SafeDelete(fis);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);
}

TEST(Dragonx_Audio_Io_AudioIOTest, ReadMp301) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/audio_test/test_read.mp3");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);

        AudioClip* clip = AudioIO::read(fis, "MP3");
        ASSERT_TRUE(clip != null);

        SafeDelete(fis);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);
}

TEST(Dragonx_Audio_Io_AudioIOTest, ReadOgg01) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/audio_test/test_read.ogg");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);

        AudioClip* clip = AudioIO::read(fis, "OGG");
        ASSERT_TRUE(clip != null);

        SafeDelete(fis);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);
}

