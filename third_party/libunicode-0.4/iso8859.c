/* iso8859.c - Convert ISO8859-* to/from Unicode.

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

#include "iso/iso8859-2.h"
#include "iso/iso8859-3.h"
#include "iso/iso8859-4.h"
#include "iso/iso8859-5.h"
#include "iso/iso8859-6.h"
#include "iso/iso8859-7.h"
#include "iso/iso8859-8.h"
#include "iso/iso8859-9.h"
#include "iso/iso8859-10.h"
#include "iso/iso8859-14.h"
#include "iso/iso8859-15.h"

#include "iso/windows-1252.h"
#include "iso/koi8-r.h"
#include "iso/koi8-u.h"
#include "iso/tis620.2533-1.h"
#include "iso/armscii-8.h"
#include "iso/georgian-academy.h"
#include "iso/georgian-ps.h"

static int
iso8859_2_init (void **privp)
{
  *privp = (void *) iso8859_2_table;
  return 1;
}

static int
iso8859_3_init (void **privp)
{
  *privp = (void *) iso8859_3_table;
  return 1;
}

static int
iso8859_4_init (void **privp)
{
  *privp = (void *) iso8859_4_table;
  return 1;
}

static int
iso8859_5_init (void **privp)
{
  *privp = (void *) iso8859_5_table;
  return 1;
}

static int
iso8859_6_init (void **privp)
{
  *privp = (void *) iso8859_6_table;
  return 1;
}

static int
iso8859_7_init (void **privp)
{
  *privp = (void *) iso8859_7_table;
  return 1;
}

static int
iso8859_8_init (void **privp)
{
  *privp = (void *) iso8859_8_table;
  return 1;
}

static int
iso8859_9_init (void **privp)
{
  *privp = (void *) iso8859_9_table;
  return 1;
}

static int
iso8859_10_init (void **privp)
{
  *privp = (void *) iso8859_10_table;
  return 1;
}

static int
iso8859_14_init (void **privp)
{
  *privp = (void *) iso8859_14_table;
  return 1;
}

static int
iso8859_15_init (void **privp)
{
  *privp = (void *) iso8859_15_table;
  return 1;
}

static int
windows_1252_init (void **privp)
{
  *privp = (void *) windows_1252_table;
  return 1;
}

static int
koi8_r_init (void **privp)
{
  *privp = (void *) koi8_r_table;
  return 1;
}

static int
koi8_u_init (void **privp)
{
  *privp = (void *) koi8_u_table;
  return 1;
}

static int
tis_620_init (void **privp)
{
  *privp = (void *) tis_620_table;
  return 1;
}

static int
armscii_8_init (void **privp)
{
  *privp = (void *) armscii_8_table;
  return 1;
}

static int
georgian_academy_init (void **privp)
{
  *privp = (void *) georgian_academy_table;
  return 1;
}

static int
georgian_ps_init (void **privp)
{
  *privp = (void *) georgian_ps_table;
  return 1;
}


static enum unicode_read_result
iso8859_read (void *arg, const char **inbuf, size_t *inbytesleft,
	      unicode_char_t **outbuf, size_t *outcharsleft)
{
  while (*inbytesleft > 0 && *outcharsleft > 0)
    {
      unsigned char c = (unsigned char) **inbuf;
      unsigned short *xlate = (unsigned short *) arg;

      ++*inbuf;
      --*inbytesleft;

      /* Special case the digits in 8859-6.  */
      if (xlate == iso8859_6_table
	  && c >= 0x30
	  && c <= 0x39)
	{
	  **outbuf = ISO6_DIGIT_ZERO + c - 0x30;
	}
      else if (c < 0x80)
	**outbuf = c;
      else
	**outbuf = (unicode_char_t) xlate[c - 0x80];

      ++*outbuf;
      --*outcharsleft;
    }

  return unicode_read_ok;
}

static enum unicode_write_result
iso8859_write (void *arg,
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

      if (ch > 0xffff)
	{
	  /* Can't appear in table.  */
	  ch = '?';
	}
      else if (ch >= 0x80)
	{
	  unsigned short *xlate = (unsigned short *) arg;

	  /* Special case the digits in 8859-6.  */
	  if (xlate == iso8859_6_table
	      && ch >= ISO6_DIGIT_ZERO
	      && ch <= ISO6_DIGIT_ZERO + 9)
	    ch -= ISO6_DIGIT_ZERO - 0x30;
	  /* Special case for old mapping in 8859-7.  */
	  else if (xlate == iso8859_7_table
		   && ch == 0x02bd)
	    ch = 0xa1;
	  /* Special case for old mapping in 8859-7.  */
	  else if (xlate == iso8859_7_table
		   && ch == 0x02bc)
	    ch = 0xa2;
	  else
	    {
	      int i;
	      /* Search in table.  This is slow, but maintaining a
		 backwards map is more expensive than it is
		 worthwhile.  */
	      for (i = 0; i < 128; ++i)
		{
		  if (ch == xlate[i])
		    {
		      ch = i + 0x80;
		      break;
		    }
		}
	      if (i == 128)
		ch = '?';
	    }
	}

      **outbuf = (char) (ch & 0xff);
      ++*outbuf;
      --*outbytesleft;
    }

  return unicode_write_ok;
}

#define P3(One, Two, Three) One ## Two ## Three

#define ISO_DEFINE(Num)							      \
static char * n ## Num [] = { "8859-"  # Num,				      \
			      "ISO-8859-" # Num,			      \
			      NULL };					      \
unicode_encoding_t P3 (unicode_iso8859_, Num, _encoding) =		      \
{									      \
  n ## Num,								      \
  P3 (iso8859_, Num, _init),						      \
  NULL,				/* Destroy.  */				      \
  NULL,				/* Reset.  */				      \
  iso8859_read,								      \
  iso8859_write,							      \
  NULL									      \
}

ISO_DEFINE (2);
ISO_DEFINE (3);
ISO_DEFINE (4);
ISO_DEFINE (5);
ISO_DEFINE (6);
ISO_DEFINE (7);
ISO_DEFINE (8);
ISO_DEFINE (9);
ISO_DEFINE (10);
ISO_DEFINE (14);
ISO_DEFINE (15);

static char *wn[] = { "cp1252", "WINDOWS-1252", NULL };
unicode_encoding_t unicode_windows_1252_encoding =
{
  wn,
  windows_1252_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  iso8859_read,
  iso8859_write,
  NULL
};

static char *krn[] = { "koi8-r", NULL };
unicode_encoding_t unicode_koi8_r_encoding =
{
  krn,
  koi8_r_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  iso8859_read,
  iso8859_write,
  NULL
};

static char *kun[] = { "koi8-u", NULL };
unicode_encoding_t unicode_koi8_u_encoding =
{
  kun,
  koi8_u_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  iso8859_read,
  iso8859_write,
  NULL
};

static char *tisn[] = { "tis620.2533-1", NULL };
unicode_encoding_t unicode_tis_620_encoding =
{
  tisn,
  tis_620_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  iso8859_read,
  iso8859_write,
  NULL
};

static char *armn[] = { "armscii-8", NULL };
unicode_encoding_t unicode_armscii_8_encoding =
{
  armn,
  armscii_8_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  iso8859_read,
  iso8859_write,
  NULL
};

static char *gan[] = { "georgian-academy", NULL };
unicode_encoding_t unicode_georgian_academy_encoding =
{
  gan,
  georgian_academy_init,
  NULL,				/* Destroy.  */
  NULL,				/* Reset.  */
  iso8859_read,
  iso8859_write,
  NULL
};

static char *gpn[] = { "georgian-ps", NULL };
unicode_encoding_t unicode_georgian_ps_encoding =
{
  gpn,
  georgian_ps_init,
  NULL,                         /* Destroy.  */
  NULL,                         /* Reset.  */
  iso8859_read,
  iso8859_write,
  NULL
};
