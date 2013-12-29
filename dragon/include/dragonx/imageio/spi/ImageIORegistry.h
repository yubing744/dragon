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
 * Created:     2013/12/28
 **********************************************************************/


#ifndef ImageIORegistry_Spi_Imageio_Dragonx_H
#define ImageIORegistry_Spi_Imageio_Dragonx_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>

#include <dragon/util/Map.h>

#include <dragonx/imageio/ImageReader.h>
#include <dragonx/imageio/ImageWriter.h>

BeginPackage3(dragonx, imageio, spi)

Import dragon::util;
Import dragon::lang;
Import dragonx::imageio;


class_ ImageIORegistry extends(Object) {
public:
    static const Type* TYPE;
   
private:
    static ImageIORegistry* singleton;
public:
    static ImageIORegistry* getInstance();

protected:
    ImageIORegistry();
    virtual ~ImageIORegistry();

protected:
    void init();

public:
    void registerImageReader(const String& imageType, ImageReader* reader);
    void registerImageWriter(const String& imageType, ImageWriter* writer);
    
    const ImageReader* getImageReader(const String& imageType);
    const ImageWriter* getImageWriter(const String& imageType);

protected:
    Map<String, ImageReader>* readerMap;
    Map<String, ImageWriter>* writerMap;
};//ImageIORegistry

EndPackage3 //(dragonx, imageio, spi)

#endif //ImageIORegistry_Spi_Imageio_Dragonx_H
