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

#include <dragon/util/HashMap.h>
#include <dragonx/image/io/spi/ImageIORegistry.h>

#include <dragonx/image/io/plugins/jpeg/JPEGImageReader.h>
#include <dragonx/image/io/plugins/jpeg/JPEGImageWriter.h>

#include <dragonx/image/io/plugins/bmp/BMPImageReader.h>
#include <dragonx/image/io/plugins/bmp/BMPImageWriter.h>

#include <dragonx/image/io/plugins/png/PNGImageReader.h>
#include <dragonx/image/io/plugins/png/PNGImageWriter.h>

#include <dragonx/image/io/plugins/gif/GIFImageReader.h>
#include <dragonx/image/io/plugins/gif/GIFImageWriter.h>

#include <dragonx/image/io/plugins/tga/TGAImageReader.h>
#include <dragonx/image/io/plugins/tga/TGAImageWriter.h>

Import dragon::util;
Import dragonx::image::io::spi;

Import dragonx::image::io::plugins::jpeg;
Import dragonx::image::io::plugins::bmp;
Import dragonx::image::io::plugins::png;
Import dragonx::image::io::plugins::gif;
Import dragonx::image::io::plugins::tga;

const Type* ImageIORegistry::TYPE = TypeOf<ImageIORegistry>();

ImageIORegistry* ImageIORegistry::singleton = null;

ImageIORegistry* ImageIORegistry::getInstance() {
    if (ImageIORegistry::singleton == null) {
        ImageIORegistry::singleton = new ImageIORegistry();
    }
    
    return ImageIORegistry::singleton;
}

ImageIORegistry::ImageIORegistry() 
    :readerMap(new HashMap<String, ImageReader>()),
    writerMap(new HashMap<String, ImageWriter>()) {
    init();
}

ImageIORegistry::~ImageIORegistry() {
    SafeDelete(readerMap);
    SafeDelete(writerMap);
}

void ImageIORegistry::init() {
    // JPEG
    registerImageReader("JPEG", new JPEGImageReader());
    registerImageWriter("JPEG", new JPEGImageWriter());

    // BMP
    registerImageReader("BMP", new BMPImageReader());
    registerImageWriter("BMP", new BMPImageWriter());

    // PNG
    registerImageReader("PNG", new PNGImageReader());
    registerImageWriter("PNG", new PNGImageWriter());

    // GIF
    registerImageReader("GIF", new GIFImageReader());
    registerImageWriter("GIF", new GIFImageWriter());

    // TGA
    registerImageReader("TGA", new TGAImageReader());
    registerImageWriter("TGA", new TGAImageWriter());
}

void ImageIORegistry::registerImageReader(const String& imageType, ImageReader* reader) {
    this->readerMap->put(imageType, reader);
}

void ImageIORegistry::registerImageWriter(const String& imageType, ImageWriter* writer) {
    this->writerMap->put(imageType, writer);
}
    
const ImageReader* ImageIORegistry::getImageReader(const String& imageType) {
    return this->readerMap->get(imageType);
}

const ImageWriter* ImageIORegistry::getImageWriter(const String& imageType) {
    return this->writerMap->get(imageType);
}