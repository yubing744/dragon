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
 * Created:     2013/12/29
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
#include <setjmp.h>

#include <dragon/io/InputStream.h>
#include <dragonx/image/io/plugins/jpeg/JPEGImageReader.h>

Import dragon::io;
Import dragonx::image::io::plugins::jpeg;

const Type* JPEGImageReader::TYPE = TypeOf<JPEGImageReader>();

JPEGImageReader::JPEGImageReader() {

}

JPEGImageReader::~JPEGImageReader() {

}

typedef struct my_error_mgr{
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
} my_error_mgr, *my_error_mgrp;

typedef struct {
  struct jpeg_source_mgr pub;   /* public fields */

  InputStream * inStream;        /* source stream */
  JOCTET * buffer;      /* start of buffer */
  boolean start_of_file;    /* have we gotten any data yet? */
} my_stream_source_mgr;

typedef my_stream_source_mgr * my_stream_src_ptr;

#define INPUT_BUF_SIZE  4096    /* choose an efficiently fread'able size */

void my_read_error_exit(j_common_ptr cinfo) {
    my_error_mgrp myerr = (my_error_mgrp)cinfo->err;

    if(myerr && myerr->setjmp_buffer){
        longjmp(myerr->setjmp_buffer, 1);
    }
}

void init_stream_source(j_decompress_ptr cinfo) {
  my_stream_src_ptr src = (my_stream_src_ptr) cinfo->src;

  /* We reset the empty-input-file flag for each image,
   * but we don't clear the input buffer.
   * This is correct behavior for reading a series of images from one source.
   */
  src->start_of_file = TRUE;
}

boolean fill_stream_input_buffer(j_decompress_ptr cinfo) {
  my_stream_src_ptr src = (my_stream_src_ptr) cinfo->src;
  size_t nbytes;

  byte* buf = (byte*)src->buffer;
  nbytes = src->inStream->read(buf, INPUT_BUF_SIZE);

  if (nbytes <= 0) {
    if (src->start_of_file) /* Treat empty input file as fatal error */
      ERREXIT(cinfo, JERR_INPUT_EMPTY);
    WARNMS(cinfo, JWRN_JPEG_EOF);

    /* Insert a fake EOI marker */
    src->buffer[0] = (JOCTET) 0xFF;
    src->buffer[1] = (JOCTET) JPEG_EOI;

    nbytes = 2;
  }

  src->pub.next_input_byte = src->buffer;
  src->pub.bytes_in_buffer = nbytes;
  src->start_of_file = FALSE;

  return TRUE;
}

void skip_stream_input_data(j_decompress_ptr cinfo, long num_bytes) {
  struct jpeg_source_mgr * src = cinfo->src;

  /* Just a dumb implementation for now.  Could use fseek() except
   * it doesn't work on pipes.  Not clear that being smart is worth
   * any trouble anyway --- large skips are infrequent.
   */
  if (num_bytes > 0) {
    while (num_bytes > (long) src->bytes_in_buffer) {
        num_bytes -= (long) src->bytes_in_buffer;

        (void) (*src->fill_input_buffer) (cinfo); //read next data
    }

    src->next_input_byte += (size_t) num_bytes;
    src->bytes_in_buffer -= (size_t) num_bytes;
  }
}

void term_source (j_decompress_ptr cinfo) {
  /* no work necessary here */
}

void jpeg_stream_src (j_decompress_ptr cinfo, InputStream* inStream) {
  my_stream_src_ptr src;

  /* The source object and input buffer are made permanent so that a series
   * of JPEG images can be read from the same file by calling jpeg_stdio_src
   * only before the first one.  (If we discarded the buffer at the end of
   * one image, we'd likely lose the start of the next one.)
   * This makes it unsafe to use this manager and a different source
   * manager serially with the same JPEG object.  Caveat programmer.
   */
  if (cinfo->src == NULL) { /* first time for this JPEG object? */
    cinfo->src = (struct jpeg_source_mgr *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
                  sizeof(my_stream_source_mgr));
    src = (my_stream_src_ptr) cinfo->src;
    src->buffer = (JOCTET *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
                  INPUT_BUF_SIZE * sizeof(JOCTET));
  }

  src = (my_stream_src_ptr) cinfo->src;

  src->pub.init_source = init_stream_source;
  src->pub.fill_input_buffer = fill_stream_input_buffer;
  src->pub.skip_input_data = skip_stream_input_data;

  src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
  src->pub.term_source = term_source;
  src->inStream = inStream;

  src->pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
  src->pub.next_input_byte = NULL; /* until buffer loaded */
}

BufferedImage* JPEGImageReader::read(InputStream* input) throw(IOException*) {
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;

    JSAMPARRAY buffer;    /* Output row buffer */
    int row_stride;       /* physical row width in output buffer */

    do {
        cinfo.err = jpeg_std_error(&jerr.pub);
        jerr.pub.error_exit = my_read_error_exit;

        if (setjmp(jerr.setjmp_buffer)) {
            jpeg_destroy_decompress(&cinfo);
            throw new IOException("error in decompress jpeg from stream!");
        }

        jpeg_create_decompress(&cinfo);
        jpeg_stream_src(&cinfo, input);
        jpeg_read_header(&cinfo, TRUE);

        if (cinfo.jpeg_color_space != JCS_RGB) { 
            if (cinfo.jpeg_color_space == JCS_GRAYSCALE 
                || cinfo.jpeg_color_space == JCS_YCbCr) { 
                cinfo.out_color_space = JCS_RGB; 
            } 
        } else { 
            break; 
        } 

        jpeg_start_decompress(&cinfo);

        row_stride = cinfo.output_width * cinfo.output_components;
        buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

        BufferedImage* image = new BufferedImage(cinfo.output_width, cinfo.output_height, ColorModel::TYPE_24_RGB);
        const byte* dest = image->getRawData();
        byte* p = const_cast<byte*>(dest);

        while (cinfo.output_scanline < cinfo.output_height) {
            jpeg_read_scanlines(&cinfo, buffer, 1);
            memcpy(p, buffer[0], row_stride);
            p += row_stride;
        }

        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);

        return image;
    } while(0);
}
