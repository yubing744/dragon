/* utf8conv.c - Converter for Utf-8.

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


#include <config.h>

#include <stdlib.h>

#include "unicode.h"
#include "convert.h"
#include "utf8.h"

static int
utf8_std_init (void **privp)
{
  *privp = (void *) 1;
  return 1;
}

static int
utf8_java_init (void **privp)
{
  *privp = (void *) 0;
  return 1;
}

static enum unicode_read_result
utf8_read (void *arg,
	   const char **inbuf,  size_t *inbytesleft,
	   unicode_char_t **outbuf, size_t *outcharsleft)
{
  while (*inbytesleft > 0 && *outcharsleft > 0)
    {
      int i, mask = 0, len;
      unsigned char c = (unsigned char) **inbuf;

      UTF8_COMPUTE (c, mask, len);
      if (len == -1)
	return unicode_read_error;

      if (*inbytesleft < (unsigned int) len)
	return unicode_read_incomplete;

      UTF8_GET (**outbuf, *inbuf, i, mask, len);
      if (**outbuf == (unicode_char_t) -1)
	return unicode_read_error;

      *inbuf += len;
      *inbytesleft -= len;

      ++*outbuf;
      --*outcharsleft;
    }

  return unicode_read_ok;
}

static enum unicode_write_result
utf8_write (void *arg, 
	    unicode_char_t **inbuf,  size_t *incharsleft,
	    char **outbuf, size_t *outbytesleft)
{
  int is_std = (int) arg;

  while (*incharsleft > 0 && *outbytesleft > 0)
    {
      size_t len = 0;
      int first;
      int i;

      unicode_char_t c = **inbuf;

      if (c < 0x80 && (is_std || c > 0))
	{
	  first = 0;
	  len = 1;
	}
      else if (c < 0x800)
	{
	  first = 0xc0;
	  len = 2;
	}
      else if (c < 0x10000)
	{
	  first = 0xe0;
	  len = 3;
	}
      else if (c < 0x200000)
	{
	  first = 0xf0;
	  len = 4;
	}
      else if (c < 0x4000000)
	{
	  first = 0xf8;
	  len = 5;
	}
      else
	{
	  first = 0xfc;
	  len = 6;
	}

      if (*outbytesleft < len)
	return unicode_write_more_room;

      for (i = len - 1; i > 0; --i)
	{
	  (*outbuf)[i] = (c & 0x3f) | 0x80;
	  c >>= 6;
	}
      (*outbuf)[0] = c | first;

      *outbuf += len;
      *outbytesleft -= len;

      ++*inbuf;
      --*incharsleft;
    }

  return unicode_write_ok;
}

/* The encoding descriptor for UTF8.  */
static char *un[] = { "UTF-8", NULL };
unicode_encoding_t unicode_utf8_encoding =
{
  un,
  utf8_std_init,		/* Init.  */
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  utf8_read,
  utf8_write,
  NULL
};

/* The encoding descriptor for Java-style UTF8.  */
static char *jn[] = { "Java-Utf-8", NULL };
unicode_encoding_t unicode_java_utf8_encoding =
{
  jn,
  utf8_java_init,		/* Init.  */
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  utf8_read,
  utf8_write,
  NULL
};
