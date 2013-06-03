/* init.c - Initialize libunicode.

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

void
unicode_init (void)
{
  unicode_register_encoding (&unicode_utf8_encoding);
  unicode_register_encoding (&unicode_java_utf8_encoding);
  unicode_register_encoding (&unicode_ascii_encoding);
  unicode_register_encoding (&unicode_latin1_encoding);
  unicode_register_encoding (&unicode_ucs4_big_encoding);
  unicode_register_encoding (&unicode_ucs4_little_encoding);
  unicode_register_encoding (&unicode_ucs4_native_encoding);
  unicode_register_encoding (&unicode_ucs2_big_encoding);
  unicode_register_encoding (&unicode_ucs2_little_encoding);
  unicode_register_encoding (&unicode_ucs2_native_encoding);

  unicode_register_encoding (&unicode_iso8859_2_encoding);
  unicode_register_encoding (&unicode_iso8859_3_encoding);
  unicode_register_encoding (&unicode_iso8859_4_encoding);
  unicode_register_encoding (&unicode_iso8859_5_encoding);
  unicode_register_encoding (&unicode_iso8859_6_encoding);
  unicode_register_encoding (&unicode_iso8859_7_encoding);
  unicode_register_encoding (&unicode_iso8859_8_encoding);
  unicode_register_encoding (&unicode_iso8859_9_encoding);
  unicode_register_encoding (&unicode_iso8859_10_encoding);
  unicode_register_encoding (&unicode_iso8859_14_encoding);
  unicode_register_encoding (&unicode_iso8859_15_encoding);
  unicode_register_encoding (&unicode_windows_1252_encoding);
  unicode_register_encoding (&unicode_koi8_r_encoding);
  unicode_register_encoding (&unicode_koi8_u_encoding);
  unicode_register_encoding (&unicode_tis_620_encoding);
  unicode_register_encoding (&unicode_armscii_8_encoding);
  unicode_register_encoding (&unicode_georgian_academy_encoding);
  unicode_register_encoding (&unicode_georgian_ps_encoding);
  unicode_register_encoding (&unicode_sjis_encoding);
  unicode_register_encoding (&unicode_cp932_encoding);
}
