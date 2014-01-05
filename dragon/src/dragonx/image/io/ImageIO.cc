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


#include <dragonx/image/io/ImageIO.h>

Import dragonx::image::io;

const Type* ImageIO::TYPE = TypeOf<ImageIO>();

ImageIORegistry* ImageIO::theRegistry = ImageIORegistry::getInstance();


ImageIO::ImageIO() {

}

ImageIO::~ImageIO() {

}

BufferedImage* ImageIO::read(const InputStream* input, const String& formatType) throw(IOException*) {
    ImageReader* reader = const_cast<ImageReader*>(theRegistry->getImageReader(formatType));

    if (reader != null) {
        return reader->read(const_cast<InputStream*>(input));
    } else {
        throw new IOException("not found support reader!");
    }
}

void ImageIO::write(const RenderedImage* image, const String& formatType, const OutputStream* output) throw(IOException*) {
    ImageWriter* writer = const_cast<ImageWriter*>(theRegistry->getImageWriter(formatType));

    if (writer != null) {
        writer->write(image, const_cast<OutputStream*>(output));
    } else {
        throw new IOException("not found support writer!");
    }
}
