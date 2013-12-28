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

#include <dragonx/xml/io/XMLReader.h>
#include <dragonx/xml/DocumentHelper.h>

#include <dragon/util/logging/Logger.h>


Import dragon::io;
Import dragon::lang;
Import dragonx::xml;
Import dragonx::xml::io;

Import dragon::util::logging;

static Logger* logger = Logger::getLogger("dragonx::xml::io::XMLReaderTest", DEBUG);

TEST(Dragonx_Xml_Io_XMLReaderTest, New) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/xml_test/read_xml_01.xml");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        FileInputStream* fis = new FileInputStream(file);

        XMLReader* xr = new XMLReader();
        Document* doc = xr->read(fis, "UTF-8");
        SafeDelete(xr);

        SafeDelete(fis);
        
        Element* root = doc->RootElement();
        ASSERT_TRUE(root != null);

        ASSERT_STREQ("scene", root->Name());

        SafeDelete(doc);
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