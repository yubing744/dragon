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

#include <dragon/lang/System.h>

#include <dragon/io/File.h>
#include <dragon/io/FileOutputStream.h>

#include <dragonx/xml/io/XMLWriter.h>
#include <dragonx/xml/DocumentHelper.h>

#include <dragon/util/logging/Logger.h>


Import dragon::io;
Import dragon::lang;
Import dragonx::xml;
Import dragonx::xml::io;

Import dragon::util::logging;

static Logger* logger = Logger::getLogger("dragonx::xml::io::XMLWriterTest", DEBUG);

TEST(Dragonx_Xml_Io_XMLWriterTest, New) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/xml_test/save_xml_01.xml");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    try {
        Document* doc = DocumentHelper::createDocument();
       
        Element* parent = doc->NewElement("scene");
        doc->InsertFirstChild(parent);

        Element* childText0 = doc->NewElement("game-object");
        Element* childText1 = doc->NewElement("game-object");

        Node* childNode0 = parent->InsertEndChild(childText0);
        Node* childNode1 = parent->InsertAfterChild(childNode0, childText1);

        childText1->SetAttribute("name", "ddd");
        
        FileOutputStream* fos = new FileOutputStream(file, true);
        OutputFormat* format = new OutputFormat("UTF-8");

        XMLWriter* xw = new XMLWriter(fos, format);
        xw->write(doc);
        SafeDelete(xw);

        SafeDelete(format);
        SafeDelete(fos);
        
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