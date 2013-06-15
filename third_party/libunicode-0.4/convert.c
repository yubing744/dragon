/* convert.c - Character set conversion framework.

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

#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "unicode.h"
#include "convert.h"

#ifndef EILSEQ
/* On some systems, like SunOS, EILSEQ is not defined.  On those
   systems we use EBADMSG instead.  */
#  define EILSEQ EBADMSG
#endif

/* Linked list of all character sets.  */
static unicode_encoding_t *encodings;

void
unicode_register_encoding (unicode_encoding_t *vec)
{
  vec->next = encodings;
  encodings = vec;
}


static int 
__fix_strcasecmp (const char *s1, const char *s2) {
  char* p1 = s1;
  char* p2 = s2;

  int result = 0;

  while((*p1) != '\0' || (*p2) != '\0'){
    int r = tolower(*p1) - tolower(*p2);

    if (r != 0) {
        result = r;
        break;
    }

    p1++;
    p2++;
  }

  return result;
}

static unicode_encoding_t *
find_encoding (const char *name)
{
  unicode_encoding_t *cs;
  for (cs = encodings; cs; cs = cs->next)
    {
      int i;
      for (i = 0; cs->names[i]; ++i)
	{
	  if (! __fix_strcasecmp (cs->names[i], name))
	    return cs;
	}
    }
  return cs;
}

unicode_iconv_t
unicode_iconv_open (const char *tocode, const char *fromcode)
{
  unicode_iconv_t r = (unicode_iconv_t) malloc (sizeof (unicode_iconv_i));
  if (r == NULL)
    {
      errno = ENOMEM;
      return (unicode_iconv_t) -1;
    }

#ifdef UNICODE_USE_SYSTEM_ICONV
  r->u.native = iconv_open (tocode, fromcode);
  if (r->u.native != (iconv_t) -1)
    {
      r->type = unicode_iconv_type_native;
      return r;
    }
#endif

  r->type = unicode_iconv_type_ours;
  r->u.ours.from = find_encoding (fromcode);
  r->u.ours.to = find_encoding (tocode);
  if (r->u.ours.from == NULL || r->u.ours.to == NULL)
    {
      free (r);
      errno = EINVAL;
      return (unicode_iconv_t) -1;
    }

  /* FIXME: how to pick the size?  */
  r->u.ours.valid = 0;
  r->u.ours.size = 1024;
  r->u.ours.buffer = (unicode_char_t *) malloc (r->u.ours.size
					      * sizeof (unicode_char_t));
  if (r->u.ours.buffer == NULL)
    {
      free (r);
      errno = ENOMEM;
      return (unicode_iconv_t) -1;
    }

  if (r->u.ours.from->init && ! r->u.ours.from->init (&r->u.ours.from_data))
    {
      free (r->u.ours.buffer);
      free (r);
      errno = ENOMEM;
      return (unicode_iconv_t) -1;
    }
  if (r->u.ours.to->init && ! r->u.ours.to->init (&r->u.ours.to_data))
    {
      if (r->u.ours.from->destroy)
	r->u.ours.from->destroy (&r->u.ours.from_data);
      free (r->u.ours.buffer);
      free (r);
      errno = ENOMEM;
      return (unicode_iconv_t) -1;
    }

  return r;
}

int
unicode_iconv_close (unicode_iconv_t cd)
{
  int r = 0;

#ifdef UNICODE_USE_SYSTEM_ICONV
  if (cd->type == unicode_iconv_type_native)
    r = iconv_close (cd->u.native);
  else
#endif
    {
      if (cd->u.ours.to->destroy)
	cd->u.ours.to->destroy (&cd->u.ours.to_data);
      if (cd->u.ours.from->destroy)
	cd->u.ours.from->destroy (&cd->u.ours.from_data);
      free (cd->u.ours.buffer);
    }

  free (cd);
  return r;
}

size_t
unicode_iconv (unicode_iconv_t cd, const char **inbuf, size_t *inbytesleft,
	       char **outbuf, size_t *outbytesleft)
{
  size_t count = 0;

#ifdef UNICODE_USE_SYSTEM_ICONV
  if (cd->type == unicode_iconv_type_native)
    return iconv (cd->u.native, inbuf, inbytesleft, outbuf, outbytesleft);
#endif

  if (inbuf == NULL || *inbuf == NULL)
    {
      if (outbuf != NULL && *outbytesleft > 0)
	{
	  if (cd->u.ours.to->reset)
	    return cd->u.ours.to->reset (&cd->u.ours.to_data,
					 outbuf, outbytesleft);
	  else
	    return 0;
	}
    }

  if (outbuf == NULL || *outbytesleft <= 0)
    {
      errno = E2BIG;
      return -1;
    }

  /* FIXME: when converting to or from UCS4, we should just skip the
     intermediate buffer.  */
  while (*inbytesleft > 0)
    {
      size_t left = *inbytesleft;
      const char *here = *inbuf;

      enum unicode_read_result rr;
      unicode_char_t *buffer = cd->u.ours.buffer + cd->u.ours.valid;
      size_t charsleft = cd->u.ours.size - cd->u.ours.valid;

      enum unicode_write_result wr;

      /* Convert as many characters as possible into the intermediate
	 buffer.  */
      rr = cd->u.ours.from->read (cd->u.ours.from_data, inbuf, inbytesleft,
			   &buffer, &charsleft);
      switch (rr)
	{
	case unicode_read_ok:
	  count += buffer - cd->u.ours.buffer - cd->u.ours.valid;
	  cd->u.ours.valid = buffer - cd->u.ours.buffer;
	  break;

	case unicode_read_incomplete:
	  /* It doesn't matter whether we ever processed any user data
	     -- it only matters whether we processed *all* of it.  If
	     we failed to process all of it we return EINVAL.  */
	  *inbytesleft = left;
	  *inbuf = here;
	  errno = EINVAL;
	  return -1;

	case unicode_read_error:
	  *inbytesleft = left;
	  *inbuf = here;
	  errno = EILSEQ;
	  return -1;

	default:
	  assert (0);
	}

      /* Now convert as many characters as possible from the
	 intermediate buffer into the output buffer.  */
      buffer = cd->u.ours.buffer;
      charsleft = cd->u.ours.valid;
      wr = cd->u.ours.to->write (cd->u.ours.to_data, &buffer, &charsleft,
			  outbuf, outbytesleft);

      /* FIXME: circular buffer would be more efficient here.  */
#ifdef HAVE_MEMMOVE
      memmove (cd->u.ours.buffer, buffer, charsleft * sizeof (unicode_char_t));
#else
      bcopy (buffer, cd->u.ours.buffer, charsleft * sizeof (unicode_char_t));
#endif
      cd->u.ours.valid = charsleft;

      switch (wr)
	{
	case unicode_write_ok:
	  break;
	case unicode_write_more_room:
	  errno = E2BIG;
	  return -1;
	default:
	  assert (0);
	}
    }

  return count;
}
