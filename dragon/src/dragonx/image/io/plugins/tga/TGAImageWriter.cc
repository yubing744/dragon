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

#include <dragonx/image/io/plugins/tga/TGAImageWriter.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::image::io::plugins::tga;
Import dragon::util::logging;

const Type* TGAImageWriter::TYPE = TypeOf<TGAImageWriter>();
static Logger* logger = Logger::getLogger(TGAImageWriter::TYPE, ERROR);

TGAImageWriter::TGAImageWriter() {

}

TGAImageWriter::~TGAImageWriter() {

}

typedef struct _OutputStreamFile {
    OutputStream* output;
    long current;
} OutputStreamFile;

int tga_output_stream_putc(TGA* tga, int c) {
    OutputStreamFile* osf = (OutputStreamFile*)tga->fd;
    OutputStream* output = (OutputStream*)osf->output;

    output->write(c);
    osf->current++;

    return 1;
}

size_t tga_output_stream_write(TGA* tga, const void* buffer, size_t size, size_t count) {
    OutputStreamFile* osf = (OutputStreamFile*)tga->fd;
    OutputStream* output = (OutputStream*)osf->output;

    int n = count;
    int wc = 0;

    byte* ptr = (byte*)buffer;

    while((n--) > 0) {
        output->write(ptr, size, 0, size);
        osf->current += size;
        ptr += size;
    }

    return count;
}

void tga_output_stream_seek(TGA* tga, long offset, int origin) {
    OutputStreamFile* osf = (OutputStreamFile*)tga->fd;
    OutputStream* output = (OutputStream*)osf->output;

    int count = offset - osf->current;

    byte* buffer = (byte*)malloc(count);
    memset(buffer, 0, count);

    output->write((byte*)buffer, count, 0, count);
    osf->current += count;
}

long tga_output_stream_tell(TGA* tga) {
    OutputStreamFile* osf = (OutputStreamFile*)tga->fd;
    return osf->current;
}

void init_tga_header(TGA *dest, const RenderedImage* image) {
    const ColorModel* colorModel = image->getColorModel();

    dest->hdr.id_len = 0;//src->hdr.id_len;
    dest->hdr.map_t = 0;//src->hdr.map_t;
    dest->hdr.img_t = 2;//src->hdr.img_t; // 2 = rgb, 3 = b&w
    dest->hdr.map_first = 0;//src->hdr.map_first;
    dest->hdr.map_entry = 0;//src->hdr.map_entry;
    dest->hdr.map_len = 0;//src->hdr.map_len;
    dest->hdr.x = 0;
    dest->hdr.y = 0;
    dest->hdr.width = image->getWidth();
    dest->hdr.height = image->getHeight();
    dest->hdr.depth = colorModel->getBitCount();//src->hdr.depth;
    dest->hdr.vert = 0;
    dest->hdr.horz = 0;
    dest->hdr.alpha = colorModel->hasAlpha() ? 1 : 0;//src->hdr.alpha;
}

void TGAImageWriter::write(const RenderedImage* image, OutputStream* output) throw(IOException*) {
    const ColorModel* colorModel = image->getColorModel();
    const byte* pData = (byte*)image->getRawData();

    int width = image->getWidth();
    int height = image->getHeight();
    int bitCount = colorModel->getBitCount();
    bool hasAlpha = colorModel->hasAlpha();

    TGA *out;
    TGAData *data;

    // malloc data
    data = (TGAData*)malloc(sizeof(TGAData));
    if(!data) {
        throw new IOException("error in malloc tag data!");
    }

    // open tag
    OutputStreamFile osf;
    osf.output = output;
    osf.current = 0;

    out = TGAOpenUserDef(&osf, NULL, NULL, 
        tga_output_stream_putc, tga_output_stream_write,
        tga_output_stream_seek, tga_output_stream_tell);
    if (!out) {
        throw new IOException("error in open tag data to write!");
    }
    
    // set data
    init_tga_header(out, image);
    data->cmap = NULL;
    data->img_data = (tbyte*)const_cast<byte*>(pData);
    data->flags |= TGA_IMAGE_DATA;

    // write tag
    data->flags |= TGA_RLE_ENCODE;
    TGAWriteImage(out, data);
    if (out->last != TGA_OK) {
        throw new IOException("error in write tag data!");
    }

    TGAClose(out);
}
