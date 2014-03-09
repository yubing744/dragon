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


#include <dragonx/xml/DocumentFactory.h>

Import dragonx::xml;

DocumentFactory* DocumentFactory::singleton = null;

void DocumentFactory::releaseDocumentFactory() {
    SafeRelease(DocumentFactory::singleton);
}

DocumentFactory* DocumentFactory::getInstance() {
    if (DocumentFactory::singleton == null) {
        DocumentFactory::singleton = new DocumentFactory();
        atexit(DocumentFactory::releaseDocumentFactory);
    }

    return DocumentFactory::singleton;
}

DocumentFactory::DocumentFactory() {

}

DocumentFactory::~DocumentFactory() {

}

Document* DocumentFactory::createDocument() {
    return new Document();
}

Document* DocumentFactory::createDocument(const String& encode) {
    return new Document();
}

Document* DocumentFactory::createDocument(const Element* rootElement) {
    return new Document();
}
