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
 * Created:     2014/03/18
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragon/lang/Float.h>

Import dragon::lang;

TEST(Dragon_Lang_FloatTest, New) {
    Float* o = new Float(0.0f);
    SafeDelete(o);
}

TEST(Dragon_Lang_FloatTest, parseFloat1) {
    try {
        Float* val = Float::parseFloat("0");
        SafeRelease(val);
    } catch(NumberFormatException* e) {
        SafeRelease(e);
        FAIL();
    }
}

TEST(Dragon_Lang_FloatTest, parseFloat2) {
    try {
        Float* val = Float::parseFloat("0.0");
        SafeRelease(val);
    } catch(NumberFormatException* e) {
        SafeRelease(e);
        FAIL();
    }
}

TEST(Dragon_Lang_FloatTest, parseFloat3) {
    try {
        Float* val = Float::parseFloat("0.0f");
        SafeRelease(val);
    } catch(NumberFormatException* e) {
        SafeRelease(e);
        FAIL();
    }
}

TEST(Dragon_Lang_FloatTest, parseFloat4) {
    try {
        Float* val = Float::parseFloat("d.0f");
        SafeRelease(val);
    } catch(NumberFormatException* e) {
        SafeRelease(e);
        FAIL();
    }
}

TEST(Dragon_Lang_FloatTest, parseFloat5) {
    try {
        Float* val = Float::parseFloat("d.df");
        SafeRelease(val);
        FAIL();
    } catch(NumberFormatException* e) {
        SafeRelease(e);
    }
}


