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

void make_header(TGA *src, TGA *dest) {
    dest->hdr.id_len    = src->hdr.id_len;
    dest->hdr.map_t     = src->hdr.map_t;
    dest->hdr.img_t     = src->hdr.img_t;
    dest->hdr.map_first     = src->hdr.map_first;
    dest->hdr.map_entry     = src->hdr.map_entry;
    dest->hdr.map_len   = src->hdr.map_len;
    dest->hdr.x         = src->hdr.x;
    dest->hdr.y         = src->hdr.y;
    dest->hdr.width     = src->hdr.width;
    dest->hdr.height    = src->hdr.height;
    dest->hdr.depth     = src->hdr.depth;
    dest->hdr.vert          = src->hdr.vert;
    dest->hdr.horz          = src->hdr.horz;
    dest->hdr.alpha         = src->hdr.alpha;
}

int tga_stream_getc(TGA* tga) {
    InputStream* input = (InputStream*)tag->fd;
    return input->read();
}

size_t tga_stream_read(TGA* tga, void* buffer, size_t size, size_t count)
{
    return tga->freadFunc ? tga->freadFunc(tga, buffer, size, count) : fread(buffer, size, count, (FILE*)tga->fd);
}

int tga_fputc(TGA* tga, int c)
{
    return tga->fputcFunc ? tga->fputcFunc(tga, c) : fputc(c, (FILE*)tga->fd);
}

size_t tga_fwrite(TGA* tga, const void* buffer, size_t size, size_t count)
{
    return tga->fwriteFunc ? tga->fwriteFunc(tga, buffer, size, count) : fwrite(buffer, size, count, (FILE*)tga->fd);
}

void tga_fseek(TGA* tga, long offset, int origin)
{
    tga->fseekFunc ? tga->fseekFunc(tga, offset, origin) : fseek((FILE*)tga->fd, offset, origin);
}

long tga_ftell(TGA* tga)
{
    return tga->ftellFunc ? tga->ftellFunc(tga) : ftell((FILE*)tga->fd);
}

BufferedImage* TGAImageReader::read(InputStream* input) throw(IOException*) {
    TGA *in;
    TGAData *data;
    int encode;

    data = (TGAData*)malloc(sizeof(TGAData));
    if(!data) {
        TGA_ERROR((TGA*)NULL, TGA_OOM);
        return 0;
    }

    in = TGAOpenUserDef(input, );
    if (in != NULL) {
        throw new IOException("error in open tga!");
    }

    data->flags = TGA_IMAGE_ID | TGA_IMAGE_DATA | TGA_RGB;
    TGAReadImage(in, data);

    if (in->last != TGA_OK) {
        TGA_ERROR(in, in->last);
        return 0;
    }

    make_header(in, out);

    TGAWriteImage(out, data);
    if (out->last != TGA_OK) {
        TGA_ERROR(out, out->last);
        return 0;
    }

    printf("[close]\n[close]\n");
        TGAClose(in);
    TGAClose(out);

        printf("[exit] main\n");

    return EXIT_SUCCESS;  
}