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
 * Created:     2014/01/01
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragonx/image/BufferedImage.h>

Import dragonx::image;

TEST(Dragonx_Image_BufferedImageTest, New) {
    BufferedImage* image = new BufferedImage(8, 8, ColorModel::TYPE_24_RGB);

    image->setPixel(4, 4, 0x123456);

    EXPECT_EQ(0x123456, image->getPixel(4, 4));

    EXPECT_EQ(0x12, image->getRed(4, 4));
    EXPECT_EQ(0x34, image->getGreen(4, 4));
    EXPECT_EQ(0x56, image->getBlue(4, 4));

    SafeDelete(image);
}