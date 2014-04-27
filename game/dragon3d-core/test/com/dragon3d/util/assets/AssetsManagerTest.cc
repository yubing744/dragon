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
 * Created:     2014/04/27
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragon/lang/System.h>
#include <dragon/io/File.h>
#include <com/dragon3d/util/assets/AssetsManager.h>

Import dragon::io;
Import dragon::lang;
Import com::dragon3d::util::assets;

/*
TEST(Com_Dragon3d_Util_Assets_AssetsManagerTest, getResources) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/");
    File* file = new File(base, filePath);

    //List<Resource>* reses = AssetsManager::getInstance()->getResources("/dragon_test/model_load_test/", true);
    //ASSERT_TRUE(reses != null);

    SafeRelease(file);
    SafeRelease(filePath);
}
*/
