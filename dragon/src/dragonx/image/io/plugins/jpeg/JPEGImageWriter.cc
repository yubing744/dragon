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

#include <dragonx/image/io/plugins/jpeg/JPEGImageWriter.h>

Import dragon::io;
Import dragonx::image::io::plugins::jpeg;

const Type* JPEGImageWriter::TYPE = TypeOf<JPEGImageWriter>();

JPEGImageWriter::JPEGImageWriter() {

}

JPEGImageWriter::~JPEGImageWriter() {

}

typedef struct {
  struct jpeg_destination_mgr pub; /* public fields */

  OutputStream* outStream;   /* target stream */
  JOCTET * buffer;    /* start of buffer */
} my_destination_mgr;

typedef my_destination_mgr * my_dest_ptr;

#define OUTPUT_BUF_SIZE  4096 /* choose an efficiently fwrite'able size */

typedef struct my_error_mgr {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
} my_error_mgr, *my_error_mgrp;

void my_write_error_exit(j_common_ptr cinfo) {
    my_error_mgrp myerr = (my_error_mgrp)cinfo->err;

    if(myerr && myerr->setjmp_buffer){
        longjmp(myerr->setjmp_buffer, 1);
    }
}

void init_destination (j_compress_ptr cinfo) {
  my_dest_ptr dest = (my_dest_ptr) cinfo->dest;

  /* Allocate the output buffer --- it will be released when done with image */
  dest->buffer = (JOCTET *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
          OUTPUT_BUF_SIZE * sizeof(JOCTET));

  dest->pub.next_output_byte = dest->buffer;
  dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;
}

boolean empty_output_buffer (j_compress_ptr cinfo) {
  my_dest_ptr dest = (my_dest_ptr) cinfo->dest;

  OutputStream* outStream = dest->outStream;

  const byte* buffer = (const byte*)dest->buffer;
  outStream->write(buffer, OUTPUT_BUF_SIZE);

  dest->pub.next_output_byte = dest->buffer;
  dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

  return TRUE;
}

void term_destination (j_compress_ptr cinfo) {
  my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
  size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;

  OutputStream* outStream = dest->outStream;

  if (datacount > 0) {
      const byte* buffer = (const byte*)dest->buffer;
      outStream->write(buffer, datacount);
  }

  outStream->flush();
}

void jpeg_stream_dest (j_compress_ptr cinfo, OutputStream* outStream) {
  my_dest_ptr dest;

  if (cinfo->dest == NULL) {  /* first time for this JPEG object? */
    cinfo->dest = (struct jpeg_destination_mgr *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
          sizeof(my_destination_mgr));
  }

  dest = (my_dest_ptr) cinfo->dest;

  dest->pub.init_destination = init_destination;
  dest->pub.empty_output_buffer = empty_output_buffer;
  dest->pub.term_destination = term_destination;

  dest->outStream = outStream;
}

void JPEGImageWriter::write(const RenderedImage* image, OutputStream* output) throw(IOException*) {
  struct jpeg_compress_struct cinfo;
  struct my_error_mgr jerr;

  JSAMPROW row_pointer[1];  /* pointer to JSAMPLE row[s] */
  int row_stride;       /* physical row width in image buffer */

  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_write_error_exit;

  if (setjmp(jerr.setjmp_buffer)) {
      jpeg_destroy_compress(&cinfo);
      throw new IOException("error in compress jpeg from stream!");
  }

  jpeg_create_compress(&cinfo);

  jpeg_stream_dest(&cinfo, output);

  cinfo.image_width = image->getWidth();  /* image width and height, in pixels */
  cinfo.image_height = image->getHeight();

  cinfo.input_components = 3;       /* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB;   /* colorspace of input image */

  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 100, TRUE /* limit to baseline-JPEG values */);

  jpeg_start_compress(&cinfo, TRUE);


  int imageWidth = image->getWidth();
  row_stride = imageWidth * 3; /* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
      JSAMPLE* sample = (JSAMPLE*)malloc(row_stride);

      for(int i=0; i<imageWidth; i++) {
          sample[i * 3] = (JSAMPLE)image->getRed(i + 1, cinfo.next_scanline + 1);
          sample[i * 3 + 1] = (JSAMPLE)image->getGreen(i + 1, cinfo.next_scanline + 1);
          sample[i * 3 + 2] = (JSAMPLE)image->getBlue(i + 1, cinfo.next_scanline + 1);
      }

      jpeg_write_scanlines(&cinfo, &sample, 1);

      free(sample);
  }

  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
}