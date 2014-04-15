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
 * Created:     2014/03/19
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragon/lang/System.h>
#include <com/dragon3d/util/assets/modelio/ModelIO.h>

Import dragon::lang;
Import com::dragon3d::util::assets::modelio;


TEST(Com_Dragon3d_Util_Assets_Modelio_ModelIOTest, loadObj1) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/cube_v2.obj");
    File* file = new File(base, filePath);

    GameObject* gameObject = ModelIO::load(file);
    SafeDelete(gameObject);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Com_Dragon3d_Util_Assets_Modelio_ModelIOTest, loadObj2) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/cube.obj");
    File* file = new File(base, filePath);

    GameObject* gameObject = ModelIO::load(file);
    SafeDelete(gameObject);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Com_Dragon3d_Util_Assets_Modelio_ModelIOTest, loadObj33) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/cube.obj");
    File* file = new File(base, filePath);

    GameObject* gameObject = ModelIO::load(file);
    SafeDelete(gameObject);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Com_Dragon3d_Util_Assets_Modelio_ModelIOTest, loadObj22) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/box.obj");
    File* file = new File(base, filePath);

    GameObject* gameObject = ModelIO::load(file);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Com_Dragon3d_Util_Assets_Modelio_ModelIOTest, loadObj3) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/teapot2.obj");
    File* file = new File(base, filePath);

    GameObject* gameObject = ModelIO::load(file);
    //SafeDelete(model);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Com_Dragon3d_Util_Assets_Modelio_ModelIOTest, loadObj4) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/teapot.obj");
    File* file = new File(base, filePath);

    GameObject* gameObject = ModelIO::load(file);
    //SafeDelete(model);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Com_Dragon3d_Util_Assets_Modelio_ModelIOTest, loadObj5) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/obj_data/complex.obj");
    File* file = new File(base, filePath);

    GameObject* gameObject = ModelIO::load(file);
    //SafeDelete(model);

    SafeRelease(file);
    SafeRelease(filePath);
}

TEST(Com_Dragon3d_Util_Assets_Modelio_ModelIOTest, load3DS_01) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/model_load_test/3ds_data/nokia-5700/nokia-5700-lowres.3DS");
    File* file = new File(base, filePath);

    GameObject* gameObject = ModelIO::load(file);
    //SafeDelete(model);

    SafeRelease(file);
    SafeRelease(filePath);
}

