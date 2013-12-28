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


#ifndef XMLWriter_Io_Xml_Dragonx_H
#define XMLWriter_Io_Xml_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/OutputStream.h>
#include <dragon/io/Writer.h>

#include <dragonx/xml/Node.h>
#include <dragonx/xml/Text.h>
#include <dragonx/xml/Element.h>
#include <dragonx/xml/Document.h>
#include <dragonx/xml/Attribute.h>

#include <dragonx/xml/io/OutputFormat.h>

BeginPackage3(dragonx, xml, io)

Import tinyxml2;
Import dragon::io;
Import dragon::lang;
Import dragonx::xml;

class_ XMLWriter extends(Object) {
public:
    XMLWriter(const OutputStream* os, const OutputFormat* format);
    virtual ~XMLWriter();

public:
    void write(const Document* doc);

protected:
    const OutputStream* outputStream;
    const OutputFormat* outputFormat;

protected:
    Writer* writer;
    XMLPrinter* printer;
};//XMLWriter

EndPackage3 //(dragonx, xml, io)

#endif //XMLWriter_Io_Xml_Dragonx_H
