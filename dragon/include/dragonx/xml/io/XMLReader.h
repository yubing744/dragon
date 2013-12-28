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


#ifndef XMLReader_Io_Xml_Dragonx_H
#define XMLReader_Io_Xml_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

#include <dragon/io/Reader.h>
#include <dragon/io/InputStream.h>

#include <dragonx/xml/Document.h>

BeginPackage3(dragonx, xml, io)

Import dragon::io;
Import dragon::lang;
Import dragonx::xml;


class_ XMLReader extends(Object) {
public:
    XMLReader();
    virtual ~XMLReader();

public:
    Document* read(const Reader* reader);
    Document* read(const InputStream* is, const String& charset);

};//XMLReader

EndPackage3 //(dragonx, xml, io)

#endif //XMLReader_Io_Xml_Dragonx_H
