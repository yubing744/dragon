/* roundtrip.c - Test roundtrip from 8bit character sets to UTF-8 and back

   Copyright (C) 1999 Robert Brady

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

#include "unicode.h"

char from_data[256];
char to_data[256 * 6 + 1];

void
try_roundtrip(const char *charset) 
{
  int c;
  unicode_iconv_t i;
  int from_size, to_size;
  char *from, *to;

  for (c=0;c<256;c++)
    from_data[c] = c;

  from_size = 256;
  to_size = 256 * 6;
  
  from = from_data;
  to = to_data;

  i = unicode_iconv_open("UTF-8", charset);
  if (i == (unicode_iconv_t)-1) {
    printf("Error opening %s <- %s.\n", "UTF-8", charset);
    exit(1);
  }
  unicode_iconv(i, (const char **)&from, &from_size, &to, &to_size);
  unicode_iconv_close(i);

  *to = 0;
  to = to_data;
  to_size = strlen(to);
  
  from = from_data;
  from_size = 256;

  i = unicode_iconv_open(charset, "UTF-8");
  if (i == (unicode_iconv_t)-1) {
    printf("Error opening %s <- %s.\n", charset, "UTF-8");
    exit(1);
  }
  unicode_iconv(i, (const char **)&to, &to_size, &from, &from_size);
  unicode_iconv_close(i);

  for (c = 0 ; c < 256; c++) {
    if (((unsigned char)from[c]) != c) {
      printf("%s:%02x\n", charset, c);
      exit(1);
    }
  }
}

int main() 
{
  unicode_init ();

  try_roundtrip("8859-1");
  try_roundtrip("8859-2");
  try_roundtrip("8859-3");
  try_roundtrip("8859-4");
  try_roundtrip("8859-5");
  try_roundtrip("8859-6");
  try_roundtrip("8859-7");
  try_roundtrip("8859-8");
  try_roundtrip("8859-9");
  try_roundtrip("8859-10");
  try_roundtrip("8859-14");
  try_roundtrip("8859-15");
  try_roundtrip("cp1252");
  try_roundtrip("koi8-r");
  try_roundtrip("koi8-u");
  return 0;
}
