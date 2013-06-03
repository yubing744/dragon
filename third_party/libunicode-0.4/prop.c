/* prop.c - Character properties.

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

#include <stddef.h>

#include "unicode.h"
#include "chartables.h"

#define asize(x)  ((sizeof (x)) / sizeof (x[0]))

#define ATTTABLE(Page, Char) \
  ((attr_table[Page] == 0) ? 0 : (attr_table[Page][Char]))

/* We cheat a bit and cast type values to (char *).  We detect these
   using the &0xff trick.  */
#define TTYPE(Page, Char) \
  (((((int) type_table[Page]) & 0xff) == ((int) type_table[Page])) \
   ? ((int) (type_table[Page])) \
   : (type_table[Page][Char]))

#define TYPE(Char) (((Char) > (UNICODE_LAST_CHAR)) ? UNICODE_UNASSIGNED : TTYPE ((Char) >> 8, (Char) & 0xff))

#define ISDIGIT(Type) ((Type) == UNICODE_DECIMAL_NUMBER \
		       || (Type) == UNICODE_LETTER_NUMBER \
		       || (Type) == UNICODE_OTHER_NUMBER)

#define ISALPHA(Type) ((Type) == UNICODE_LOWERCASE_LETTER \
		       || (Type) == UNICODE_UPPERCASE_LETTER \
		       || (Type) == UNICODE_TITLECASE_LETTER \
		       || (Type) == UNICODE_MODIFIER_LETTER \
		       || (Type) == UNICODE_OTHER_LETTER)

int
unicode_isalnum (unicode_char_t c)
{
  int t = TYPE (c);
  return ISDIGIT (t) || ISALPHA (t);
}

int
unicode_isalpha (unicode_char_t c)
{
  int t = TYPE (c);
  return ISALPHA (t);
}

int
unicode_iscntrl (unicode_char_t c)
{
  return TYPE (c) == UNICODE_CONTROL;
}

int
unicode_isdigit (unicode_char_t c)
{
  return TYPE (c) == UNICODE_DECIMAL_NUMBER;
}

int
unicode_isgraph (unicode_char_t c)
{
  int t = TYPE (c);
  return (t != UNICODE_CONTROL
	  && t != UNICODE_FORMAT
	  && t != UNICODE_UNASSIGNED
	  && t != UNICODE_PRIVATE_USE
	  && t != UNICODE_SURROGATE
	  && t != UNICODE_SPACE_SEPARATOR);
}

int
unicode_islower (unicode_char_t c)
{
  return TYPE (c) == UNICODE_LOWERCASE_LETTER;
}

int
unicode_isprint (unicode_char_t c)
{
  int t = TYPE (c);
  return (t != UNICODE_CONTROL
	  && t != UNICODE_FORMAT
	  && t != UNICODE_UNASSIGNED
	  && t != UNICODE_PRIVATE_USE
	  && t != UNICODE_SURROGATE);
}

int
unicode_ispunct (unicode_char_t c)
{
  int t = TYPE (c);
  return (t == UNICODE_CONNECT_PUNCTUATION || t == UNICODE_DASH_PUNCTUATION
	  || t == UNICODE_CLOSE_PUNCTUATION || t == UNICODE_FINAL_PUNCTUATION
	  || t == UNICODE_INITIAL_PUNCTUATION || t == UNICODE_OTHER_PUNCTUATION
	  || t == UNICODE_OPEN_PUNCTUATION);
}

int
unicode_isspace (unicode_char_t c)
{
  int t = TYPE (c);
  return (t == UNICODE_SPACE_SEPARATOR || t == UNICODE_LINE_SEPARATOR
	  || t == UNICODE_PARAGRAPH_SEPARATOR);
}

int
unicode_isupper (unicode_char_t c)
{
  return TYPE (c) == UNICODE_UPPERCASE_LETTER;
}

int
unicode_istitle (unicode_char_t c)
{
  unsigned int i;
  for (i = 0; i < asize (title_table); ++i)
    if (title_table[i][0] == c)
      return 1;
  return 0;
}

int
unicode_isxdigit (unicode_char_t c)
{
  int t = TYPE (c);
  return ((c >= 'a' && c <= 'f')
	  || (c >= 'A' && c <= 'F')
	  || ISDIGIT (t));
}

int
unicode_isdefined (unicode_char_t c)
{
  int t = TYPE (c);
  return t != UNICODE_UNASSIGNED;
}

/* This function stolen from Markus Kuhn <Markus.Kuhn@cl.cam.ac.uk>.  */
int
unicode_iswide (unicode_char_t c)
{
  if (c < 0x1100)
    return 0;

  return ((c >= 0x1100 && c <= 0x115f)	   /* Hangul Jamo */
	  || (c >= 0x2e80 && c <= 0xa4cf && (c & ~0x0011) != 0x300a &&
	      c != 0x303f)		   /* CJK ... Yi */
	  || (c >= 0xac00 && c <= 0xd7a3)  /* Hangul Syllables */
	  || (c >= 0xf900 && c <= 0xfaff)  /* CJK Compatibility Ideographs */
	  || (c >= 0xfe30 && c <= 0xfe6f)  /* CJK Compatibility Forms */
	  || (c >= 0xff00 && c <= 0xff5f)  /* Fullwidth Forms */
	  || (c >= 0xffe0 && c <= 0xffe6));
}

unicode_char_t
unicode_toupper (unicode_char_t c)
{
  int t = TYPE (c);
  if (t == UNICODE_LOWERCASE_LETTER)
    return ATTTABLE (c >> 8, c & 0xff);
  else if (t == UNICODE_TITLECASE_LETTER)
    {
      unsigned int i;
      for (i = 0; i < asize (title_table); ++i)
	{
	  if (title_table[i][0] == c)
	    return title_table[i][1];
	}
    }
  return c;
}

unicode_char_t
unicode_tolower (unicode_char_t c)
{
  int t = TYPE (c);
  if (t == UNICODE_UPPERCASE_LETTER)
    return ATTTABLE (c >> 8, c & 0xff);
  else if (t == UNICODE_TITLECASE_LETTER)
    {
      unsigned int i;
      for (i = 0; i < asize (title_table); ++i)
	{
	  if (title_table[i][0] == c)
	    return title_table[i][2];
	}
    }
  return c;
}

unicode_char_t
unicode_totitle (unicode_char_t c)
{
  unsigned int i;
  for (i = 0; i < asize (title_table); ++i)
    {
      if (title_table[i][0] == c || title_table[i][1] == c
	  || title_table[i][2] == c)
	return title_table[i][0];
    }
  return (TYPE (c) == UNICODE_LOWERCASE_LETTER
	  ? ATTTABLE (c >> 8, c & 0xff)
	  : c);
}

int
unicode_digit_value (unicode_char_t c)
{
  if (TYPE (c) == UNICODE_DECIMAL_NUMBER)
    return ATTTABLE (c >> 8, c & 0xff);
  return -1;
}

int
unicode_xdigit_value (unicode_char_t c)
{
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 1;
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 1;
  if (TYPE (c) == UNICODE_DECIMAL_NUMBER)
    return ATTTABLE (c >> 8, c & 0xff);
  return -1;
}

int
unicode_type (unicode_char_t c)
{
  return TYPE (c);
}
