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

void TGAImageWriter::write(const RenderedImage* image, OutputStream* output) throw(IOException*) {
    TGA *in, *out;
    TGAData *data;
    int encode;

    if(argc < 3) {
        printf("Not enough arguments supplied!\n");
        return 0;
    }
    
    data = (TGAData*)malloc(sizeof(TGAData));
    if(!data) {
        TGA_ERROR((TGA*)NULL, TGA_OOM);
        return 0;
    }

        in = TGAOpen(argv[1], "r");
    printf("[open] name=%s, mode=%s\n", argv[1], "r");

    out = TGAOpen(argv[2], "w");
        printf("[open] name=%s, mode=%s\n", argv[2], "w");
    

    data->flags = TGA_IMAGE_ID | TGA_IMAGE_DATA | TGA_RGB;
    TGAReadImage(in, data);
    if (in->last != TGA_OK) {
        TGA_ERROR(in, in->last);
        return 0;
    }

    make_header(in, out);

    data->flags |= TGA_RLE_ENCODE;
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
