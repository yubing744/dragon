/* ordering.c - Test unicode_canonical_ordering().

   Copyright (C) 1998, 1999 Tom Tromey

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */

/* FIXME: for now, just hard-code the tests.  Later, put into separate
   files for easy addition.  */
/* FIXME: once decomposition is added, add tests for that.  */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include "unicode.h"

#define asize(Ary) ((sizeof (Ary)) / sizeof ((Ary)[0]))



/* This test comes from the Unicode book.  */

#define A           0x0041
#define UNDERDOT    0x0323
#define DIAERESIS   0x0308
#define BREVE       0x0306
#define A_UNDERDOT  0x1ea0
#define A_DIAERESIS 0x00c4
#define A_BREVE     0x0102

static unicode_char_t t1_src[] =
{
  A, DIAERESIS, UNDERDOT
};

static unicode_char_t t1_dst[] =
{
  A, UNDERDOT, DIAERESIS
};

static unicode_char_t t2_src[] =
{
  A_DIAERESIS, UNDERDOT
};

static unicode_char_t t3_src[] =
{
  A, UNDERDOT, DIAERESIS
};

static unicode_char_t t4_src[] =
{
  A_UNDERDOT, DIAERESIS
};

static unicode_char_t t5_dst[] =
{
  A, DIAERESIS, BREVE
};

static unicode_char_t t5_src[] =
{
  A_DIAERESIS, BREVE
};

static unicode_char_t t6_src[] =
{
  A, DIAERESIS, BREVE
};

static unicode_char_t t7_dst[] =
{
  A, BREVE, DIAERESIS
};

static unicode_char_t t7_src[] =
{
  A, BREVE, DIAERESIS
};

static unicode_char_t t8_src[] =
{
  A_BREVE, DIAERESIS
};



static int
check (unicode_char_t *src, size_t s_len, unicode_char_t *dst, size_t d_len)
{
  size_t i;
  if (s_len != d_len)
    return 0;
  for (i = 0; i < s_len; ++i)
    {
      if (src[i] != dst[i])
	return 0;
    }
  return 1;
}

static int
check_decomp (unicode_char_t *src, size_t s_len,
	      unicode_char_t *dst, size_t d_len)
{
  size_t len;
  /* Don't bother to free -- this is just test code.  */
  unicode_char_t *dec = unicode_canonical_decomposition (src[0], &len);
  unicode_char_t *d2;

  d2 = malloc ((s_len - 1 + len) * sizeof (unicode_char_t));
  memcpy (d2, dec, len * sizeof (unicode_char_t));
  memcpy (&d2[len], src + 1, (s_len - 1) * sizeof (unicode_char_t));

  unicode_canonical_ordering (d2, s_len - 1 + len);

  return check (d2, s_len - 1 + len, dst, d_len);
}

int
main (int argc, char **argv)
{
  int ok = 1;
  int i;

  unicode_canonical_ordering (t1_src, asize (t1_src));
  if (! check (t1_src, asize (t1_src), t1_dst, asize (t1_dst)))
    ok = 0;

  if (! check_decomp (t2_src, asize (t2_src), t1_dst, asize (t1_dst)))
    ok = 0;

  unicode_canonical_ordering (t3_src, asize (t3_src));
  if (! check (t3_src, asize (t3_src), t1_dst, asize (t1_dst)))
    ok = 0;

  if (! check_decomp (t4_src, asize (t4_src), t1_dst, asize (t1_dst)))
    ok = 0;

  if (! check_decomp (t5_src, asize (t5_src), t5_dst, asize (t5_dst)))
    ok = 0;

  unicode_canonical_ordering (t6_src, asize (t6_src));
  if (! check (t6_src, asize (t6_src), t5_dst, asize (t5_dst)))
    ok = 0;

  unicode_canonical_ordering (t7_src, asize (t7_src));
  if (! check (t7_src, asize (t7_src), t7_dst, asize (t7_dst)))
    ok = 0;

  if (! check_decomp (t8_src, asize (t8_src), t7_dst, asize (t7_dst)))
    ok = 0;

  exit (! ok);
}
