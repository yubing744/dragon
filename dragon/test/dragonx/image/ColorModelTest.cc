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
#include <dragonx/image/ColorModel.h>

Import dragonx::image;

TEST(Dragonx_Image_ColorModelTest, BitsTest) {
    uint32_t val = 0x12345600;
    byte* data = (byte*)(&val);

    uint32_t val2 = *((uint32_t*)data);
    ASSERT_EQ(0x12345600, val2);

    ASSERT_EQ(32, sizeof(uint32_t) * 8);
    ASSERT_EQ(8, sizeof(uint32_t) * 8 - 24);

    val2 >>= (sizeof(uint32_t) * 8 - 24);
    ASSERT_EQ(0x123456, val2);
}

TEST(Dragonx_Image_ColorModelTest, Pixel) {
    const ColorModel* cm = ColorModel::TYPE_24_RGB;

    uint32_t val = 0;
    byte* data = (byte*)(&val);

    cm->setPixel(data, 0x010203);
    
    EXPECT_EQ(0x010203, cm->getPixel(data));

    EXPECT_EQ(0x01, cm->getRed(data));
    EXPECT_EQ(0x02, cm->getGreen(data));
    EXPECT_EQ(0x03, cm->getBlue(data));
}

