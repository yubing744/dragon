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
 * Created:     2013/12/30
 **********************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <png.h>
#include <zlib.h>

#include <dragonx/image/io/plugins/png/PNGImageReader.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::image::io::plugins::png;
Import dragon::util::logging;

const Type* PNGImageReader::TYPE = TypeOf<PNGImageReader>();
static Logger* logger = Logger::getLogger(PNGImageReader::TYPE, ERROR);

PNGImageReader::PNGImageReader() {

}

PNGImageReader::~PNGImageReader() {

}

#define RGB_PREMULTIPLY_APLHA(vr, vg, vb, va) \ 
    (unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \ 
    ((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \ 
    ((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \ 
    ((unsigned)(unsigned char)(va) << 24)) 

#ifndef png_jmpbuf
#  define png_jmpbuf(png_ptr) ((png_ptr)->png_jmpbuf)
#endif

void png_read_callback(png_structp png_ptr, png_bytep data, png_size_t length) { 
    InputStream* input = (InputStream*)png_get_io_ptr(png_ptr); 
    input->read((byte*)data, length);
} 

BufferedImage* PNGImageReader::read(InputStream* input) throw(IOException*) {
    png_structp png_ptr;
    png_infop info_ptr;

    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;

    bool hasAlpha = false;
    bool preMulti = false;


    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
       throw new IOException("error in create png read struct ptr!");
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
       png_destroy_read_struct(&png_ptr, NULL, NULL);
       throw new IOException("error in create png info struct ptr!");
    }


    if (setjmp(png_jmpbuf(png_ptr))) {
       png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
       throw new IOException("error in read png!");
    }

    // set png read callback
    png_set_read_fn(png_ptr, input, png_read_callback); 

    png_read_info(png_ptr, info_ptr); 

    width = png_get_image_width(png_ptr, info_ptr); 
    height = png_get_image_height(png_ptr, info_ptr);

    int bitsPerComponent = png_get_bit_depth(png_ptr, info_ptr); 
    color_type = png_get_color_type(png_ptr, info_ptr); 


    if (color_type == PNG_COLOR_TYPE_PALETTE) { 
        png_set_palette_to_rgb(png_ptr); 
    } 

    if (color_type == PNG_COLOR_TYPE_GRAY && bitsPerComponent < 8) { 
        png_set_expand_gray_1_2_4_to_8(png_ptr); 
    } 

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) { 
        png_set_tRNS_to_alpha(png_ptr); 
    }   

    // reduce images with 16-bit samples to 8 bits 
    if (bitsPerComponent == 16) { 
        png_set_strip_16(png_ptr);             
    }  

    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) { 
        png_set_gray_to_rgb(png_ptr); 
    } 

    bitsPerComponent = 8; 
    png_uint_32 rowbytes;

    png_bytep* row_pointers = (png_bytep*)malloc( sizeof(png_bytep) * height); 
         
    png_read_update_info(png_ptr, info_ptr);

    rowbytes = png_get_rowbytes(png_ptr, info_ptr); 
    png_uint_32 channel = rowbytes / width; 

    BufferedImage* image = null;

    if (channel == 4) {
        image = new BufferedImage(width, height, ColorModel::TYPE_32_RGBA);
    } else if (channel == 3) {
        image = new BufferedImage(width, height, ColorModel::TYPE_24_RGB);
    } else {
        throw new IOException("not support color chanel!");
    }

    png_byte* pData = (png_byte*)(const_cast<byte*>(image->getRawData()));

    for (unsigned short i = 0; i < height; ++i) { 
        row_pointers[i] = pData + i * rowbytes; 
    } 

    png_read_image(png_ptr, row_pointers); 
    png_read_end(png_ptr, NULL); 


    if (channel == 4) { 
        hasAlpha = true; 

        unsigned int *tmp = (unsigned int *)pData; 

        for(unsigned short i = 0; i < height; i++) { 
            for(unsigned int j = 0; j < rowbytes; j += 4) { 
                *tmp++ = RGB_PREMULTIPLY_APLHA( row_pointers[i][j], row_pointers[i][j + 1],  
                                                  row_pointers[i][j + 2], row_pointers[i][j + 3] ); 
            } 
        } 

        preMulti = true; 
    } 

    SafeFree(row_pointers); 
    
    if (png_ptr) { 
        png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0); 
    } 

    return image; 
}   

