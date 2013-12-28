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


#include <dragonx/xml/io/XMLWriter.h>
#include <dragon/io/OutputStreamWriter.h>

Import dragon::io;
Import dragonx::xml::io;


class XMLStreamWriterPrinter 
    extends(XMLPrinter) {
public:
    XMLStreamWriterPrinter(Writer* writer, bool compact, int depth);

public:
    virtual void Print(const char* format, ...);

protected:
    Writer* writer;
};

XMLStreamWriterPrinter::XMLStreamWriterPrinter(Writer* writer, bool compact, int depth ) 
    : XMLPrinter(NULL, compact, depth){
    this->writer = writer;
}

void XMLStreamWriterPrinter::XMLStreamWriterPrinter::Print(const char* format, ...) {
    va_list va;
    va_start(va, format);

    String* text = String::vformat(format, va);
    const Array<byte> data = text->getBytes("UTF-8");
    this->writer->write(text);
    SafeDelete(text);

    va_end(va);
}

XMLWriter::XMLWriter(const OutputStream* os, const OutputFormat* format) 
    :outputStream(os), outputFormat(format) {
    const String* encode = format->getEncoding();
    this->writer = new OutputStreamWriter(os, encode);
    this->printer = new XMLStreamWriterPrinter(this->writer, false, 0);
}

XMLWriter::~XMLWriter() {
    SafeDelete(this->writer);
    SafeDelete(this->printer);
}

void XMLWriter::write(const Document* doc) { 
    doc->Print(this->printer);
}
