/* sjis.c - Translate to/from Shift-JIS, also MSFT code page 932 MBCS.

   Copyright (C) 1999 Tor Lillqvist

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

#include "jis/shiftjis.h"
#include "msft/cp932.h"

/*
 * The algorithm and table structure used here isn't particularily
 * sophisticated.  For a more space-efficient coding tables, see the
 * kanjimap program on ftp.unicode.org.
 *
 * I'm not pleased with having separate tables for Shift-JIS and CP932.
 * They have *lots* of overlap.
 */

typedef struct {
  unsigned short **table;
  unsigned short **revtable;
} context;

static context sjis_context = {
  sjis_table, NULL
};
static context cp932_context = {
  cp932_table, NULL
};

static int
sjis_init (void **privp)
{
  *privp = &sjis_context;
  return 1;
}

static int
cp932_init (void **privp)
{
  *privp = &cp932_context;
  return 1;
}

static enum unicode_read_result
sjis_read (void *arg, const char **inbuf, size_t *inbytesleft,
	   unicode_char_t **outbuf, size_t *outcharsleft)
{
  unsigned int c1, c2;
  unsigned int row, col;
  unsigned short **table = ((context *) arg)->table;
  int adjust;
  int rowOffset;
  int cellOffset;

  while (*inbytesleft > 0 && *outcharsleft > 0)
    {
      c1 = (unsigned char) **inbuf;

      if (c1 < 0x20)		/* Control characters */
	**outbuf = (unicode_char_t) c1;
      else if (c1 <= 0x7F	/* JIS-Roman */
	       || (c1 >= 0xA1	/* Half-width katakana */
		   && c1 <= 0xDF)) 
	**outbuf = (unicode_char_t) table[0][c1];
      else if ((c1 >= 0x81 && c1 <= 0x9F) || (c1 >= 0xE0 && c1 <= 0xEF))
	/* JIS X 0208-1997 */
	{
	  if (*inbytesleft == 1)
	    return unicode_read_incomplete;
	  ++*inbuf;
	  --*inbytesleft;
	  c2 = (unsigned char) **inbuf;
	  if (!((c2 >= 0x40 && c2 <= 0x7E) || (c2 >= 0x80 && c2 <= 0xFC)))
	    return unicode_read_error;
	  if (table[c1] && table[c1][c2])
	    **outbuf = table[c1][c2];
	  else
	    return unicode_read_error;
	}
      else
	return unicode_read_error;
      ++*inbuf;
      --*inbytesleft;

      ++*outbuf;
      --*outcharsleft;
    }

  return unicode_read_ok;
}

static enum unicode_write_result
sjis_write (void *arg,
	    unicode_char_t **inbuf, size_t *incharsleft,
	    char **outbuf, size_t *outbytesleft)
{
  if (*outbytesleft <= 0)
    return unicode_write_more_room;

  while (*outbytesleft > 0 && *incharsleft > 0)
    {
      unicode_char_t ch = **inbuf;

      ++*inbuf;
      --*incharsleft;

      if (ch < 0x20)
	{
	  /* Control character */
	  **outbuf = ch;
	  ++*outbuf;
	  --*outbytesleft;
	}
      else if (ch > 0xffff)
	{
	  /* Can't appear in table.  */
	  **outbuf = '?';
	  ++*outbuf;
	  --*outbytesleft;
	}
      else
	{
	  context *ctx = (context *) arg;
	  unsigned short **table = ctx->table;
	  unsigned short **revtable = ctx->revtable;
	  unsigned short *subrev;

	  if (revtable == NULL)
	    {
	      /* Set up reverse table */
	      int i;

	      revtable = ctx->revtable =
		malloc (0x100 * sizeof (ctx->revtable[0]));
	      
	      for (i = 0; i < 0x100; i++)
		revtable[i] = NULL;

	      for (i = 0; i < 0x100; i++)
		if (table[i] != NULL)
		  {
		    int j;
		    for (j = 0; j < 0x100; j++)
		      {
			int msb = table[i][j] / 0x100;
			int lsb = table[i][j] % 0x100;
			if (revtable[msb] == NULL)
			  {
			    int k;
			    revtable[msb] =
			      malloc (0x100 * sizeof (unsigned short));
			    for (k = 0; k < 0x100; k++)
			      revtable[msb][k] = 0;
			  }
			if (revtable[msb][lsb] != 0)
			  {
			    /* Duplicates occur in CP932.
			     * Follow the advice from CJKV.
			     */
			    if (revtable[msb][lsb] <= 0x818A)
			      /* JIS X 0208-1983 row 2 and NEC Row 13,
			       * use JIS X 0208-1983 code point
			       */
			      continue;
			    else if (revtable[msb][lsb] >= 0xEEEF
				     && revtable[msb][lsb] <= 0xEEFC)
			      /* IBM selected non-kanji, use NEC code point */
			      continue;
			    else
			      /* IBM selected kanji, use IBM code point */
			      ;
			  }
			revtable[msb][lsb] = (i << 8) | j;
		      }
		  }
	    }

	  subrev = revtable[ch/0x100];
	  if (subrev == NULL
	      || subrev[ch%0x100] == 0)
	    {
	      /* No mapping.  */
	      **outbuf = '?';
	      ++*outbuf;
	      --*outbytesleft;
	    }
	  else
	    {
	      if (subrev[ch%0x100] >= 0x100)
		{
		  if (*outbytesleft == 1)
		    return unicode_write_more_room;
		  **outbuf = ((subrev[ch%0x100] >> 8) & 0xFF);
		  ++*outbuf;
		  --*outbytesleft;
		}
	      **outbuf = (subrev[ch%0x100] & 0xFF);
	      ++*outbuf;
	      --*outbytesleft;
	    }
	}
    }

  return unicode_write_ok;
}

/* The encoding descriptor for Shift-JIS.  */
static char *sjn[] = { "Shift-JIS", "SJIS", NULL };
unicode_encoding_t unicode_sjis_encoding =
{
  sjn,
  sjis_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  sjis_read,
  sjis_write,
  NULL
};

/* The encoding descriptor for CP932.  */
static char *cp932n[] = { "CP932", NULL };
unicode_encoding_t unicode_cp932_encoding =
{
  cp932n,
  cp932_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  sjis_read,
  sjis_write,
  NULL
};
