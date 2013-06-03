/* ucs4.c - test the UCS-4 encoder/decoder.
   
   Copyright (C) 199 Tom Tromey

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

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unicode.h>

/* Return 1 on error, 0 on success.  */
static int
check (unicode_iconv_t context, char c)
{
  char input[100];
  char *inp = input;
  char output[100];
  size_t inbytes, outbytes;
  char *outp = output;

  inbytes = 1;
  input[0] = 'A';
  outbytes = sizeof (output);
  unicode_iconv (context,
		 (const char **) &inp, &inbytes,
		 &outp, &outbytes);

  if (inbytes != 0 || outp - output != 4)
    return 1;
  if (output[0] || output[1] || output[2] || ! output[3])
    return 1;

  return 0;
}

int main ()
{
  unicode_iconv_t context;

  unicode_init ();

  context = unicode_iconv_open ("UCS-4", "ASCII");
  return check (context, 'A');
}
