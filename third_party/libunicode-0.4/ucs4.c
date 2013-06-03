/* ucs4.c - Translate to/from UCS4.

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

static int
ucs4_big_init (void **privp)
{
  *privp = (void *) 1;
  return 1;
}

static int
ucs4_little_init (void **privp)
{
  *privp = (void *) 0;
  return 1;
}

static int
ucs4_native_init (void **privp)
{
  int val = 1;
  char *p = (char *) &val;
  *privp = (void *) ! *p;
  return 1;
}

static enum unicode_read_result
ucs4_read (void *bigep, const char **inbuf, size_t *inbytesleft,
	   unicode_char_t **outbuf, size_t *outcharsleft)
{
  int bigendian = (int) bigep;
  int i;

  while (*inbytesleft > 0 && *outcharsleft > 0)
    {
      unicode_char_t ch = 0;

      if (*inbytesleft < 4)
	return unicode_read_incomplete;

      for (i = 0; i < 4; ++i)
	{
	  unsigned char c = (*inbuf)[bigendian ? 3 - i : i];
	  ch |= (c << (8 * i));
	}

      **outbuf = ch;

      *inbuf += 4;
      *inbytesleft -= 4;

      ++*outbuf;
      --*outcharsleft;
    }

  return unicode_read_ok;
}

static enum unicode_write_result
ucs4_write (void *arg,
	    unicode_char_t **inbuf, size_t *incharsleft,
	    char **outbuf, size_t *outbytesleft)
{
  int bigendian = (int) arg;
  int i;

  while (*incharsleft > 0 && *outbytesleft > 0)
    {
      unicode_char_t ch = **inbuf;

      if (*outbytesleft < 4)
	return unicode_write_more_room;

      for (i = 0; i < 4; ++i)
	{
	  unsigned char c = (ch >> (8 * i)) & 0xff;
	  (*outbuf)[bigendian ? 3 - i : i] = c;
	}

      *outbuf += 4;
      *outbytesleft -= 4;

      ++*inbuf;
      --*incharsleft;
    }

  return unicode_write_ok;
}

/* FIXME - bad name.  */
static char *ubn[] = { "UCS4", "UCS-4", "UCS4-big", NULL };
unicode_encoding_t unicode_ucs4_big_encoding =
{
  ubn,
  ucs4_big_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  ucs4_read,
  ucs4_write,
  NULL
};

/* FIXME - bad name.  */
static char *uln[] = { "UCS4-little", NULL };
unicode_encoding_t unicode_ucs4_little_encoding =
{
  uln,
  ucs4_little_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  ucs4_read,
  ucs4_write,
  NULL
};

static char *un[] = { "UCS4-native", NULL };
unicode_encoding_t unicode_ucs4_native_encoding =
{
  un,
  ucs4_native_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  ucs4_read,
  ucs4_write,
  NULL
};
