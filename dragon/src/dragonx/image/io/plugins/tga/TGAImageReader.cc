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
 * Created:     2014/01/01
 **********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <tga.h>



#include <dragonx/image/io/plugins/tga/TGAImageReader.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::image::io::plugins::tga;
Import dragon::util::logging;

const Type* TGAImageReader::TYPE = TypeOf<TGAImageReader>();
static Logger* logger = Logger::getLogger(TGAImageReader::TYPE, ERROR);

TGAImageReader::TGAImageReader() {

}

TGAImageReader::~TGAImageReader() {

}

typedef struct _InputStreamFile {
    InputStream* input;
    long current;
} InputStreamFile;

int tga_input_stream_getc(TGA* tga) {
    InputStreamFile* isf = (InputStreamFile*)tga->fd;
    InputStream* input = (InputStream*)isf->input;

    int rt = input->read();
    isf->current++;
    return rt;
}

size_t tga_input_stream_read(TGA* tga, void* buffer, size_t size, size_t count) {
    InputStreamFile* isf = (InputStreamFile*)tga->fd;
    InputStream* input = (InputStream*)isf->input;

    int rt = input->read((byte*)buffer, size, 0, size);
    isf->current += size;
    return rt;
}

void tga_input_stream_seek(TGA* tga, long offset, int origin) {
    InputStreamFile* isf = (InputStreamFile*)tga->fd;
    InputStream* input = (InputStream*)isf->input;

    int count = offset - isf->current;

    byte* buffer = (byte*)malloc(count);
    input->read(buffer, count, 0, count);
    free(buffer);

    isf->current += count;
}

long tga_input_stream_tell(TGA* tga) {
    InputStreamFile* isf = (InputStreamFile*)tga->fd;
    return isf->current;
}

void copy_colormap32bit_8bit_data(BufferedImage* image, TGA* tga, TGAData* data) {
    int width = tga->hdr.width;
    int height = tga->hdr.height;

    tbyte* colorMap = data->cmap;

    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            int index = data->img_data[i * width + j];
            tbyte* color = &colorMap[index * 3];

            image->setRed(j, i, color[0]);
            image->setGreen(j, i, color[1]);
            image->setBlue(j, i, color[2]);
        }
    }
}

void copy_colormap32bit_16bit_data(BufferedImage* image, TGA* tga, TGAData* data) {
    int width = tga->hdr.width;
    int height = tga->hdr.height;

    tbyte* colorMap = data->cmap;

    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            int index = data->img_data[i * width * 2 + j] + data->img_data[i * width * 2 + j + 1] * 256;
            tbyte* color = &colorMap[index * 3];

            image->setRed(j, i, color[0]);
            image->setGreen(j, i, color[1]);
            image->setBlue(j, i, color[2]);
        }
    }
}

BufferedImage* TGAImageReader::read(InputStream* input) throw(IOException*) {
    TGA *in;
    TGAData *data;

    // malloc buffer
    data = (TGAData*)malloc(sizeof(TGAData));
    if(!data) {
        throw new IOException("error in malloc tag data!");
    }

    // open tag stream
    InputStreamFile isf;
    isf.input = input;
    isf.current = 0;

    in = TGAOpenUserDef(&isf, tga_input_stream_getc, tga_input_stream_read, 
        NULL, NULL, 
        tga_input_stream_seek, tga_input_stream_tell);
    if (in == NULL) {
        throw new IOException("error in open tga to read!");
    }

    // read tag data
    data->flags = TGA_IMAGE_ID | TGA_IMAGE_DATA | TGA_RGB;
    TGAReadImage(in, data);
    if (in->last != TGA_OK) {
        throw new IOException("error in read tga data!");
    }

    BufferedImage* image = null;

    if (in->hdr.depth == 8) {
        if (TGA_IS_MAPPED(in)) {
            image = new BufferedImage(in->hdr.width, in->hdr.height, ColorModel::TYPE_24_RGB);
            copy_colormap32bit_8bit_data(const_cast<BufferedImage*>(image), in, data);
        } else {
            throw new IOException("not support tga color depth 8!");
        }
    } else if (in->hdr.depth == 16) {
        if (TGA_IS_MAPPED(in)) {
            image = new BufferedImage(in->hdr.width, in->hdr.height, ColorModel::TYPE_24_RGB);
            copy_colormap32bit_16bit_data(const_cast<BufferedImage*>(image), in, data);
        } else {
            throw new IOException("not support tga color depth 16!");
        }
    } else if (in->hdr.depth == 24) {
        image = new BufferedImage(in->hdr.width, in->hdr.height, ColorModel::TYPE_24_RGB);
        byte* dest = const_cast<byte*>(image->getRawData());
        memcpy(dest, data->img_data, in->hdr.width * in->hdr.height * 3);
    } else if (in->hdr.depth == 32) {
        image = new BufferedImage(in->hdr.width, in->hdr.height, ColorModel::TYPE_32_RGBA);
        byte* dest = const_cast<byte*>(image->getRawData());
        memcpy(dest, data->img_data, in->hdr.width * in->hdr.height * 4);
    } else {
        throw new IOException("not support tga color depth!");
    }

    SafeFree(data->cmap);
    SafeFree(data->img_data);
    free(data);

    TGAClose(in);

    return image;
}