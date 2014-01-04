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

#include <dragonx/image/io/plugins/png/PNGImageWriter.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::image::io::plugins::png;
Import dragon::util::logging;

const Type* PNGImageWriter::TYPE = TypeOf<PNGImageWriter>();
static Logger* logger = Logger::getLogger(PNGImageWriter::TYPE, ERROR);

PNGImageWriter::PNGImageWriter() {

}

PNGImageWriter::~PNGImageWriter() {

}

void png_stream_write(png_structp ppIn, png_bytep pb, png_size_t st) {
    png_const_structp pp = ppIn;
    OutputStream *output = (OutputStream*)png_get_io_ptr(pp);  
    output->write((byte*)pb, st);
}

void png_stream_flush(png_structp ppIn) {
    png_const_structp pp = ppIn;
    OutputStream *output = (OutputStream*)png_get_io_ptr(pp);  
    output->flush();
}

void PNGImageWriter::write(const RenderedImage* image, OutputStream* output) throw(IOException*) {
    const ColorModel* colorModel = image->getColorModel();
    const byte* pData = (byte*)image->getRawData();

    int width = image->getWidth();
    int height = image->getHeight();
    int bitCount = colorModel->getBitCount();
    bool hasAlpha = colorModel->hasAlpha();

    do { 
        png_structp png_ptr; 
        png_infop info_ptr; 
        png_colorp palette; 
        png_bytep *row_pointers; 


        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); 
        if (png_ptr == NULL){ 
            throw new IOException("error in create png write struct!");
        } 

        info_ptr = png_create_info_struct(png_ptr); 
        if (info_ptr == NULL){ 
            png_destroy_write_struct(&png_ptr, NULL); 
            throw new IOException("error in create png write struct!");
        } 

        if (setjmp(png_jmpbuf(png_ptr))) { 
            png_destroy_write_struct(&png_ptr, &info_ptr); 
            throw new IOException("error in write png data to ouputstream!");
        } 

        png_set_write_fn(png_ptr, (void *)output, png_stream_write, png_stream_flush);

        if (hasAlpha) { 
            png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, 
                PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE); 
        } else { 
            png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, 
                PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE); 
        } 

    
        palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * sizeof (png_color)); 
        png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);

         
        png_write_info(png_ptr, info_ptr); 
        png_set_packing(png_ptr); 


        row_pointers = (png_bytep *)malloc(height * sizeof(png_bytep));

        if(row_pointers == NULL) { 
            png_destroy_write_struct(&png_ptr, &info_ptr); 
            throw new IOException("error malloc memery in write png!");
        } 


        if (!hasAlpha) {  
            for (int i = 0; i < (int)height; i++) { 
                row_pointers[i] = (png_bytep)pData + i * width * 3; 
            } 

            png_write_image(png_ptr, row_pointers); 
 
            free(row_pointers); 
            row_pointers = NULL; 
        } else { 
            for (int i = 0; i < (int)height; i++) { 
                row_pointers[i] = (png_bytep)pData + i * width * 4; 
            } 

            png_write_image(png_ptr, row_pointers); 

            free(row_pointers); 
            row_pointers = NULL; 
        }


        png_write_end(png_ptr, info_ptr); 

        png_free(png_ptr, palette); 
        palette = NULL; 

        png_destroy_write_struct(&png_ptr, &info_ptr);
    } while (0);
}
