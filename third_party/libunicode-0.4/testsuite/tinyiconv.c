/* Simple iconv-like program using libunicode.

   Copyright (C) 1999 Tor Lillqvist

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

int
main (int argc, char **argv)
{
  char *fromcode, *tocode;
  unsigned char bfr[1000];
  unsigned char result[1000];
  unsigned char rresult[1000];
  unicode_iconv_t ic, ric;
  int from_size, to_size;
  unsigned char *from, *to;
  unsigned char *p;
  int lineno;

  unicode_init ();

  if (argc == 1)
    {
      /* Probably run from "make check" */
      fromcode = "UTF-8";
      tocode = "UCS-4";
      /* Use this same file as test input */
      /* Thus, put some interesting stuff in UTF-8 here:
       * Tämä on tekstiä.
       * Somebody please write something in Japanese or Chinese here, 
       * encoded in UTF-8.
       * Etc.
       */
      freopen ("tinyiconv.c", "r", stdin);
      freopen ("/dev/null", "w", stdout);
    }
  else
    {
      if (argc != 3)
	{
	  fprintf (stderr, "Usage: tinyiconv fromcode tocode <input >output\n");
	  exit (1);
	}
      fromcode = argv[1];
      tocode = argv[2];
    }

  if ((ic = unicode_iconv_open(tocode, fromcode)) == (unicode_iconv_t) -1)
    {
      fprintf (stderr, "Conversion from %s to %s not available\n",
	       fromcode, tocode);
      exit (1);
    }

  if ((ric = unicode_iconv_open(fromcode, tocode)) == (unicode_iconv_t) -1)
    {
      fprintf (stderr, "Reverse conversion from %s to %s not available\n",
	       tocode, fromcode);
      exit (1);
    }

  lineno = 0;
  while (fgets (bfr, sizeof (bfr), stdin))
    {
      lineno++;
      from = bfr;
      from_size = strlen (bfr);
      to = result;
      to_size = sizeof (result);
      if (unicode_iconv (ic, (const char **) &from, &from_size,
			 &to, &to_size) == -1)
	{
	  fprintf (stderr, "Forward conversion failed on line %d\n",
		   lineno);
	  exit (1);
	}

      *to = 0;
      printf ("%s", result);

      from = result;
      from_size = to - result;
      to = rresult;
      to_size = sizeof (rresult);
      if (unicode_iconv (ric, (const char **) &from, &from_size,
			 &to, &to_size) == -1)
	{
	  fprintf (stderr, "Reverse conversion failed on line %d\n",
		   lineno);
	  exit (1);
	}

      if (strlen (bfr) != to - rresult)
	fprintf (stderr, "Roundtrip length mismatch on line %d (%d vs %d)\n",
		 lineno, strlen (bfr), to - rresult);
      else if (memcmp (bfr, rresult, to - rresult) != 0)
	printf ("Roundtrip mismatch on line %d\n", lineno);

    }
  unicode_iconv_close (ic);
  unicode_iconv_close (ric);

  return 0;
}
