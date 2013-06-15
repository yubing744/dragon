/* utf8.c - Translate to/from UTF8.

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
/*
#ifdef HAVE_LANGINFO_H
#include <langinfo.h>
#endif
*/
#include <string.h>

#include "unicode.h"
#include "convert.h"
#include "utf8.h"

/* Skip backwards to previous utf8 character.  */
char *
unicode_previous_utf8 (const char *start, const char *p)
{
  int count = 6;
  for (--p; p > start && count; --p, --count)
    {
      if ((*p & 0xc0) != 0x80)
	break;
    }
  return count ? (char *) p : NULL;
}

/* Skip over a utf8 character.
   Note that P cannot be const because then there is no useful return
   type for this function.  */
char *
unicode_next_utf8 (const char *p)
{
  if (*p)
    {
      for (++p; (*p & 0xc0) == 0x80; ++p)
	;
    }
  return (char *) p;
}

/* Return length of a UTF8 string.  */
int
unicode_strlen (const char *p, int max)
{
  int len = 0;
  const char *start = p;
  /* special case for the empty string */
  if (!*p) 
    return 0;
  /* Note that the test here and the test in the loop differ subtly.
     In the loop we want to see if we've passed the maximum limit --
     for instance if the buffer ends mid-character.  Here at the top
     of the loop we want to see if we've just reached the last byte.  */
  while (max < 0 || p - start < max)
    {
      p = unicode_next_utf8 (p);
      ++len;
      if (! *p || (max > 0 && p - start > max))
	break;
    }
  return len;
}

/* Return pointer to the last UTF-8 sequence in a string.  */
char *
unicode_last_utf8 (const char *p)
{
  const char *start = p;
  /* special case for the empty string */
  if (!*p) 
    return (char *)p;
  p = p + strlen(p);
  p = unicode_previous_utf8(start, p);
  return (char *)p;
}


char *
unicode_get_utf8 (const char *p, unicode_char_t *result)
{
  int i, mask = 0, len;
  unsigned char c = (unsigned char) *p;

  UTF8_COMPUTE (c, mask, len);
  if (len == -1)
    return NULL;
  UTF8_GET (*result, p, i, mask, len);
  if (*result == (unicode_char_t) -1)
    return NULL;
  return (char *) p + len;
}

/* unicode_offset_to_index */

size_t 
unicode_offset_to_index(const char *src, int offset)
{
	const char *s = src;
	while (offset && *s) {
		s = unicode_next_utf8(s);
		offset--;
	}
	return s - src;
}

/* unicode_index_to_offset */

size_t 
unicode_index_to_offset(const char *src, int index)
{
	const char *s = src;
	size_t offset = 0;
	while (*s) {
		if ((s - src) >= index)
		  return offset;
		s = unicode_next_utf8(s);
		offset++;
	}
	return offset;
}

/* unicode_strncpy */

char
 *unicode_strncpy(char *dest, const char *src, size_t n)
{
	const char *s = src;
	size_t o_n = n;
	while (n && *s) {
		s = unicode_next_utf8(s);
		n--;
	}
	strncpy(dest, src, s - src);
	dest[s - src] = 0;
	return dest;
}

static int
unicode_get_charset_internal (char **a)
{
  char *charset = getenv("CHARSET");

  if (charset && a && ! *a)
    *a = charset;

  if (charset && strstr (charset, "UTF-8"))
      return 1;
/*
#ifdef _NL_CTYPE_CODESET_NAME
  charset = nl_langinfo (_NL_CTYPE_CODESET_NAME);
  if (charset)
    {
      if (a && ! *a)
	*a = charset;
      if (strcmp (charset, "UTF-8") == 0)
	return 1;
    }
#elif CODESET
  charset = nl_langinfo(CODESET);
  if (charset)
    {
      if (a && ! *a)
	*a = charset;
      if (strcmp (charset, "UTF-8") == 0)
	return 1;
    }
#endif  
*/
  if (a && ! *a) 
    *a = "US-ASCII";
  /* Assume this for compatibility at present.  */
  return 0;
}

static int utf8_locale_cache = -1;
static char *utf8_charset_cache = NULL;

int
unicode_get_charset (char **charset) 
{
  if (utf8_locale_cache != -1)
    {
      if (charset)
	*charset = utf8_charset_cache;
      return utf8_locale_cache;
    }
  utf8_locale_cache = unicode_get_charset_internal (&utf8_charset_cache);
  if (charset) 
    *charset = utf8_charset_cache;
  return utf8_locale_cache;
}

int
unicode_string_width(const char *p)
{
  /* for now, we just pass through to unicode_strlen 
   *
   *  FIXME : make characters with doublewidth property count for 2, 
   *          and nonspacing combining characters count for 0.
   */
  return unicode_strlen(p, -1);
}

void
unicode_pad_string(char *dest, int right, int width, const char *string) 
{
  char *old_dest = dest;
  strcpy(dest, string);
  
  width -= unicode_string_width(string);
  dest += strlen(dest);

  if (width < 0) {
    int i = unicode_offset_to_index(string, width);
    old_dest[i] = 0;
    return;
  }

  while (width > 0) {
    *dest = ' ';
    dest++;
    width--;
  }

  *dest = 0;

}

/* unicode_strchr */

char *
unicode_strchr(const char *p, unicode_char_t c)
{
  char ch[10];
  int first, len, i;

  if (c < 0x80) return strchr(p, c);  

  if (c < 0x800) {
    first = 0xc0;
    len = 2;
  } else if (c < 0x10000)
    {
      first = 0xe0;
      len = 3;
    }
  else if (c < 0x200000)
    {
      first = 0xf0;
      len = 4;
    }
  else if (c < 0x4000000)
    {
      first = 0xf8;
      len = 5;
    }
  else
    {
      first = 0xfc;
      len = 6;
    }
  
  for (i = len - 1; i > 0 ; --i)
    {
      ch[i] = (c & 0x3f) | 0x80;
      c >>= 6;
    }
  ch[0] = c | first;
  ch[len] = 0;
  
  return strstr(p, ch);
}

#if 0
/* unicode_strrchr 
 *
 * This is ifdefed out atm as there is no strrstr function in libc.
 *
 * One needs writing.
 */

char *
unicode_strrchr(const char *p, unicode_char_t c)
{
  char ch[10];
  int first, len, i;

  if (c < 0x80) return strrchr(p, c);  

  if (c < 0x800) {
    first = 0xc0;
    len = 2;
  } else if (c < 0x10000)
    {
      first = 0xe0;
      len = 3;
    }
  else if (c < 0x200000)
    {
      first = 0xf0;
      len = 4;
    }
  else if (c < 0x4000000)
    {
      first = 0xf8;
      len = 5;
    }
  else
    {
      first = 0xfc;
      len = 6;
    }
  
  for (i = len - 1; i > 0 ; --i)
    {
      ch[i] = (c & 0x3f) | 0x80;
      c >>= 6;
    }
  ch[0] = c | first;
  ch[len] = 0;
  
  return strrstr(p, ch);
}
#endif
