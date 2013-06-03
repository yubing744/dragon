/* convert.h - Internal header for converters.

   Copyright (C) 1999 Tom Tromey

   The Gnome Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The Gnome Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the Gnome Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifndef CONVERT_H
#define CONVERT_H

#ifdef UNICODE_USE_SYSTEM_ICONV
#  include <iconv.h>
#else
/* This is harmless as it is completely ignored by the code when the
   above condition is false.  */
typedef void *iconv_t;
#endif /* UNICODE_USE_SYSTEM_ICONV */

struct unicode_encoding_t;

typedef struct unicode_iconv_s
{
  /* Converter for source character set.  */
  struct unicode_encoding_t *from;

  /* Converter private data.  */
  void *from_data;

  /* Converter for destination character set.  */
  struct unicode_encoding_t *to;

  /* Converter private data.  */
  void *to_data;

  /* Buffer used to store intermediate results.  */
  unicode_char_t *buffer;

  /* Number of valid characters in buffer.  */
  size_t valid;

  /* Total number of character slots in buffer.  */
  size_t size;
} unicode_iconv_s;

typedef struct unicode_iconv_i
{
  /* Type of converter.  */
  enum {
    unicode_iconv_type_native,
    unicode_iconv_type_ours
  } type;

  union
  {
    iconv_t native;		/* Used in `native' case.  */
    unicode_iconv_s ours;	/* Used in `our' case.  */
  } u;
} unicode_iconv_i;

/* Possible results of a read.  */
enum unicode_read_result
{
  /* Read was ok, consumed at least one byte or produced at least one
     character.  */
  unicode_read_ok,

  /* Input is incomplete, nothing was consumed or produced.
     This could be okay, if you have more text to pass through, but it's
     an error if you've provided all the input text you've got.  */
  unicode_read_incomplete,

  /* Invalid sequence.  */
  unicode_read_error
};

enum unicode_write_result
{
  /* Write was ok.  */
  unicode_write_ok,

  /* Write needs more room.  */
  unicode_write_more_room
};

typedef struct unicode_encoding_t
{
  /* NULL terminated array of names of elements.  */
  char **names;

  /* Initialize private data.  NULL means no init necessary.  Return 0
     on error.  */
  int (*init) (void **privp);

  /* Destroy private data.  NULL means no destroy necessary.  */
  void (*destroy) (void **privp);

  /* Put output buffer into initial shift state.  If NULL, this
     encoding doesn't use a shift state.  Returns error indicator like
     iconv(); see man page.  */
  int (*reset) (void *priv, char **outbuf, size_t *outbytesleft);

  /* Read some bytes and convert into an array of UCS4 characters.

     On entry, there are *INBYTESLEFT bytes of text at *INBUF to
     be converted, and *OUTCHARSLEFT characters available at *OUTBUF
     to hold the results.
  
     On exit, *INBYTESLEFT and *INBUF indicate the input bytes still not
     consumed.  *OUTCHARSLEFT and *OUTBUF indicate the output buffer
     space still not filled.  (By exclusion, these indicate which input
     bytes were consumed, and which output characters were produced.)

     Return one of the unicode_read_ values.  */
  enum unicode_read_result
    (*read) (void *priv,
             const char     **inbuf,  size_t *inbytesleft,
             unicode_char_t **outbuf, size_t *outcharsleft);

  /* Convert an array of UCS4 characters to output bytes.

     On entry, there are *INCHARSLEFT UCS4 characters available at
     *INBUF, and *OUTBYTESLEFT bytes available to store output at
     *OUTBUF.

     On exit, *INCHARSLEFT and *INBUF indicate the number of unicode
     characters left unconverted (because there was insufficient room in
     the output buffer to hold their converted forms), and *OUTBYTESLEFT
     and *OUTBUF indicate the unused portion of the output buffer.

     Return one of the unicode_write_ values.  */
  enum unicode_write_result
    (*write) (void *priv,
              unicode_char_t **inbuf,  size_t *incharsleft,
              char           **outbuf, size_t *outbytesleft);

  /* Link.  */
  struct unicode_encoding_t *next;
} unicode_encoding_t;

void unicode_register_encoding (unicode_encoding_t *vec);

extern unicode_encoding_t unicode_utf8_encoding;
extern unicode_encoding_t unicode_ascii_encoding;
extern unicode_encoding_t unicode_latin1_encoding;
extern unicode_encoding_t unicode_ucs4_big_encoding;
extern unicode_encoding_t unicode_ucs4_little_encoding;
extern unicode_encoding_t unicode_ucs4_native_encoding;
extern unicode_encoding_t unicode_ucs2_big_encoding;
extern unicode_encoding_t unicode_ucs2_little_encoding;
extern unicode_encoding_t unicode_ucs2_native_encoding;
extern unicode_encoding_t unicode_java_utf8_encoding;

extern unicode_encoding_t unicode_iso8859_2_encoding;
extern unicode_encoding_t unicode_iso8859_3_encoding;
extern unicode_encoding_t unicode_iso8859_4_encoding;
extern unicode_encoding_t unicode_iso8859_5_encoding;
extern unicode_encoding_t unicode_iso8859_6_encoding;
extern unicode_encoding_t unicode_iso8859_7_encoding;
extern unicode_encoding_t unicode_iso8859_8_encoding;
extern unicode_encoding_t unicode_iso8859_9_encoding;
extern unicode_encoding_t unicode_iso8859_10_encoding;
extern unicode_encoding_t unicode_iso8859_14_encoding;
extern unicode_encoding_t unicode_iso8859_15_encoding;
extern unicode_encoding_t unicode_windows_1252_encoding;
extern unicode_encoding_t unicode_koi8_r_encoding;
extern unicode_encoding_t unicode_koi8_u_encoding;
extern unicode_encoding_t unicode_tis_620_encoding;
extern unicode_encoding_t unicode_armscii_8_encoding;
extern unicode_encoding_t unicode_georgian_academy_encoding;
extern unicode_encoding_t unicode_georgian_ps_encoding;
extern unicode_encoding_t unicode_sjis_encoding;
extern unicode_encoding_t unicode_cp932_encoding;

#endif /* CONVERT_H */
