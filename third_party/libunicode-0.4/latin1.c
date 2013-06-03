/* latin1.c - Translate to/from Latin1.

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
latin1_init (void **privp)
{
  *privp = (void *) 0xff;
  return 1;
}

static int
ascii_init (void **privp)
{
  *privp = (void *) 0x7f;
  return 1;
}

static enum unicode_read_result
latin1_read (void *arg, const char **inbuf, size_t *inbytesleft,
	     unicode_char_t **outbuf, size_t *outcharsleft)
{
  while (*inbytesleft > 0 && *outcharsleft > 0)
    {
      unsigned char c = (unsigned char) **inbuf;

      /* We actually always handle Latin-1 on the input side.  It
	 doesn't matter.  */
      **outbuf = (unicode_char_t) c;

      ++*inbuf;
      --*inbytesleft;

      ++*outbuf;
      --*outcharsleft;
    }

  return unicode_read_ok;
}

static enum unicode_write_result
latin1_write (void *arg,
	      unicode_char_t **inbuf, size_t *incharsleft,
	      char **outbuf, size_t *outbytesleft)
{
  unsigned int mask = (unsigned int) arg;

  if (*outbytesleft <= 0)
    return unicode_write_more_room;

  while (*outbytesleft > 0 && *incharsleft > 0)
    {
      unicode_char_t ch = **inbuf;

      if (ch > mask)
	ch = '?';
      **outbuf = (char) (ch & mask);

      ++*outbuf;
      --*outbytesleft;

      ++*inbuf;
      --*incharsleft;
    }

  return unicode_write_ok;
}

/* The encoding descriptor for Latin1.  */
static char *l1n[] = { "8859-1", "ISO-8859-1", NULL };
unicode_encoding_t unicode_latin1_encoding =
{
  l1n,
  latin1_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  latin1_read,
  latin1_write,
  NULL
};

/* The encoding descriptor for ASCII.  */
static char *an[] = { "ASCII", NULL };
unicode_encoding_t unicode_ascii_encoding =
{
  an,
  ascii_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  latin1_read,
  latin1_write,
  NULL
};
