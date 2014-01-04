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
 * Created:     2013/12/24
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragonx/xml/io/XMLReader.h>

#include <gtest/gtest.h>

#include <dragon/lang/System.h>

#include <dragon/io/File.h>
#include <dragon/io/FileInputStream.h>
#include <dragon/io/FileOutputStream.h>

#include <dragonx/image/io/ImageIO.h>
#include <dragon/util/logging/Logger.h>


Import dragon::io;
Import dragon::lang;
Import dragonx::image::io;

Import dragon::util::logging;

static Logger* logger = Logger::getLogger("dragonx::image::io::ImageIOTest", DEBUG);

TEST(Dragonx_Image_IO_ImageIOTest, ReadJPEG) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/read_jpeg_01.jpg");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);

        BufferedImage* image = ImageIO::read(fis, "JPEG");
        ASSERT_TRUE(image != null);

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

TEST(Dragonx_Image_IO_ImageIOTest, WriteJPEG) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/write_jpeg_01.jpg");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileOutputStream* fos = new FileOutputStream(file);

        BufferedImage* image = new BufferedImage(64, 64, ColorModel::TYPE_24_RGB);
        
        image->setPixel(31, 31, 0xffffff);
        image->setPixel(32, 31, 0x0000ff);
        image->setPixel(33, 31, 0x00ff00);
        image->setPixel(34, 31, 0xff0000);

        image->setPixel(31, 32, 0xffffff);
        image->setPixel(32, 32, 0x0000ff);
        image->setPixel(33, 32, 0x00ff00);
        image->setPixel(34, 32, 0xff0000);

        image->setPixel(31, 33, 0xffffff);
        image->setPixel(32, 33, 0x0000ff);
        image->setPixel(33, 33, 0x00ff00);
        image->setPixel(34, 33, 0xff0000);
 
        image->setPixel(31, 34, 0xffffff);
        image->setPixel(32, 34, 0x0000ff);
        image->setPixel(33, 34, 0x00ff00);
        image->setPixel(34, 34, 0xff0000);

        ImageIO::write(image, "JPEG", fos);

        SafeDelete(fos);
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

TEST(Dragonx_Image_IO_ImageIOTest, ReadBMP) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/read_bmp_01.bmp");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);

        BufferedImage* image = ImageIO::read(fis, "BMP");
        ASSERT_TRUE(image != null);

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

TEST(Dragonx_Image_IO_ImageIOTest, WriteBMP) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/write_bmp_01.bmp");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileOutputStream* fos = new FileOutputStream(file);

        BufferedImage* image = new BufferedImage(64, 64, ColorModel::TYPE_24_RGB);
        ImageIO::write(image, "BMP", fos);

        SafeDelete(fos);
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


TEST(Dragonx_Image_IO_ImageIOTest, ReadBMPAndWriteBMP) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/read_bmp_01.bmp");
    String* outputPath = new String(L"/dragon_test/image_test/write_bmp_02.bmp");

    File* file = new File(base, filePath);
    File* outFile = new File(base, outputPath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);
        FileOutputStream* fos = new FileOutputStream(outFile);

        BufferedImage* image = ImageIO::read(fis, "BMP");
        ASSERT_TRUE(image != null);

        ImageIO::write(image, "BMP", fos);

        SafeDelete(fis);
        SafeDelete(fos);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);

    SafeDelete(outFile);
    SafeDelete(outputPath);
}

TEST(Dragonx_Image_IO_ImageIOTest, ReadJPEGAndWriteJPEG) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/read_jpeg_01.jpg");
    String* outputPath = new String(L"/dragon_test/image_test/write_jpeg_03.jpg");

    File* file = new File(base, filePath);
    File* outFile = new File(base, outputPath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);
        FileOutputStream* fos = new FileOutputStream(outFile);

        BufferedImage* image = ImageIO::read(fis, "JPEG");
        ASSERT_TRUE(image != null);

        ImageIO::write(image, "JPEG", fos);

        SafeDelete(fis);
        SafeDelete(fos);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);

    SafeDelete(outFile);
    SafeDelete(outputPath);
}

TEST(Dragonx_Image_IO_ImageIOTest, ReadJPEGAndWriteBMP) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/read_jpeg_01.jpg");
    String* outputPath = new String(L"/dragon_test/image_test/write_bmp_03.bmp");

    File* file = new File(base, filePath);
    File* outFile = new File(base, outputPath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);
        FileOutputStream* fos = new FileOutputStream(outFile);

        BufferedImage* image = ImageIO::read(fis, "JPEG");
        ASSERT_TRUE(image != null);

        ImageIO::write(image, "BMP", fos);

        SafeDelete(fis);
        SafeDelete(fos);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);

    SafeDelete(outFile);
    SafeDelete(outputPath);
}

TEST(Dragonx_Image_IO_ImageIOTest, ReadBMPAndWriteJPEG) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/read_bmp_01.bmp");
    String* outputPath = new String(L"/dragon_test/image_test/write_jpeg_04.jpg");

    File* file = new File(base, filePath);
    File* outFile = new File(base, outputPath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);
        FileOutputStream* fos = new FileOutputStream(outFile);

        BufferedImage* image = ImageIO::read(fis, "BMP");
        ASSERT_TRUE(image != null);

        ImageIO::write(image, "JPEG", fos);

        SafeDelete(fis);
        SafeDelete(fos);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);

    SafeDelete(outFile);
    SafeDelete(outputPath);
}

TEST(Dragonx_Image_IO_ImageIOTest, ReadPNGAndWritePNG) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/read_png_01.png");
    String* outputPath = new String(L"/dragon_test/image_test/write_png_01.png");

    File* file = new File(base, filePath);
    File* outFile = new File(base, outputPath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);
        FileOutputStream* fos = new FileOutputStream(outFile);

        BufferedImage* image = ImageIO::read(fis, "PNG");
        ASSERT_TRUE(image != null);

        ImageIO::write(image, "PNG", fos);

        SafeDelete(fis);
        SafeDelete(fos);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);

    SafeDelete(outFile);
    SafeDelete(outputPath);
}


TEST(Dragonx_Image_IO_ImageIOTest, ReadGIFAndWriteGIF) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/image_test/read_gif_01.gif");
    String* outputPath = new String(L"/dragon_test/image_test/write_gif_01.gif");

    File* file = new File(base, filePath);
    File* outFile = new File(base, outputPath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);
        FileOutputStream* fos = new FileOutputStream(outFile);

        BufferedImage* image = ImageIO::read(fis, "GIF");
        ASSERT_TRUE(image != null);

        ImageIO::write(image, "GIF", fos);

        SafeDelete(fis);
        SafeDelete(fos);
    } catch (Exception* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeDelete(file);
    SafeDelete(filePath);

    SafeDelete(outFile);
    SafeDelete(outputPath);
}


