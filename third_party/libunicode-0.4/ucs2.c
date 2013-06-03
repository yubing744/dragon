/* ucs2.c - Translate to/from UCS2.

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

#define HIGH_SURROGATE 0xd800
#define LOW_SURROGATE 0xdc00
#define LAST_SURROGATE 0xdfff

static int
ucs2_big_init (void **privp)
{
  *privp = (void *) 1;
  return 1;
}

static int
ucs2_little_init (void **privp)
{
  *privp = (void *) 0;
  return 1;
}

static int
ucs2_native_init (void **privp)
{
  int p = 1;
  char *q = (char *) &p;
  int v = *q;
  /* 1 means big-endian.  */
  *privp = (void *) ! v;
  return 1;
}

static int
get_one (int bigendian, int off, const char **inbuf)
{
  int c = 0, i;
  for (i = 0; i < 2; ++i)
    {
      unsigned char x = (*inbuf)[off + (bigendian ? 1 - i : i)];
      c |= (x << (8 * i));
    }
  return c;
}

static enum unicode_read_result
ucs2_read (void *bigep, const char **inbuf, size_t *inbytesleft,
	   unicode_char_t **outbuf, size_t *outcharsleft)
{
  int bigendian = (int) bigep;
  int converted = 0;

  while (*inbytesleft > 0 && *outcharsleft > 0)
    {
      unicode_char_t ch;
      int c, bytes = 2;

      if (*inbytesleft < 2)
	return unicode_read_incomplete;

      c = get_one (bigendian, 0, inbuf);
      if (c >= HIGH_SURROGATE && c < LOW_SURROGATE)
	{
	  int lo;

	  if (*inbytesleft < 4)
	    return converted ? unicode_read_ok : unicode_read_incomplete;

	  lo = get_one (bigendian, 2, inbuf);
	  if (lo >= LOW_SURROGATE && lo < LAST_SURROGATE)
	    {
	      /* Got a surrogate pair.  Compute character.  */
	      ch = (c - 0xd800) * 0x400 + (lo - 0xdc00) + 0x10000;
	      bytes = 4;
	    }
	  else
	    {
	      /* If we got an isolated surrogate, we just return it.  */
	      ch = c;
	    }
	}
      else
	ch = c;

      **outbuf = ch;

      *inbuf += bytes;
      *inbytesleft -= bytes;

      ++*outbuf;
      --*outcharsleft;

      converted = 1;
    }

  return unicode_read_ok;
}

/* Helper function to write a character.  */
static void
write_one (int ch, int bigendian, char **outbuf)
{
  int i;
  for (i = 0; i < 2; ++i)
    {
      unsigned char c = (ch >> (8 * i)) & 0xff;
      (*outbuf)[bigendian ? 1 - i : i] = c;
    }
}

static enum unicode_write_result
ucs2_write (void *arg,
	    unicode_char_t **inbuf, size_t *incharsleft,
	    char **outbuf, size_t *outbytesleft)
{
  int bigendian = (int) arg;

  while (*incharsleft > 0 && *outbytesleft > 0)
    {
      unicode_char_t ch = **inbuf;

      if (*outbytesleft < 2)
	return unicode_write_more_room;

      if (ch > 0x10ffff)
	{
	  /* Too big for surrogate.  Choose replacement character.  */
	  ch = 0xfffe;
	}
      else if (ch > 0xffff)
	{
	  /* Write as surrogate pair.  */
	  int hi;
	  if (*outbytesleft < 4)
	    return unicode_write_more_room;
	  ch -= 0x10000;
	  hi = ch / 0x400 + 0xd800;
	  write_one (hi, bigendian, outbuf);
	  *outbuf += 2;
	  *outbytesleft -= 2;
	  ch = (ch & 0x3ff) + 0xdc00;
	}

      write_one (ch, bigendian, outbuf);

      *outbuf += 2;
      *outbytesleft -= 2;

      ++*inbuf;
      --*incharsleft;
    }

  return unicode_write_ok;
}

/* FIXME - bad name */
static char *ubn[] = { "UCS2-big", NULL };
unicode_encoding_t unicode_ucs2_big_encoding =
{
  ubn,
  ucs2_big_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  ucs2_read,
  ucs2_write,
  NULL
};

/* FIXME - bad name */
static char *uln[] = { "UCS2-little", NULL };
unicode_encoding_t unicode_ucs2_little_encoding =
{
  uln,
  ucs2_little_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  ucs2_read,
  ucs2_write,
  NULL
};

static char *u2n[] = { "UCS2", "UCS-2", NULL };
unicode_encoding_t unicode_ucs2_native_encoding =
{
  u2n,
  ucs2_native_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  ucs2_read,
  ucs2_write,
  NULL
};
