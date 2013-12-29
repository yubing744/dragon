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
 * Created:     2013/12/28
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragonx/imageio/ImageIO.h>

Import dragonx::imageio;

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

#include <dragonx/imageio/ImageIO.h>
#include <dragon/util/logging/Logger.h>


Import dragon::io;
Import dragon::lang;
Import dragonx::imageio;

Import dragon::util::logging;

static Logger* logger = Logger::getLogger("dragonx::imageio::ImageIOTest", DEBUG);

TEST(Dragonx_Imageio_ImageIOTest, ReadJPEG) {
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
