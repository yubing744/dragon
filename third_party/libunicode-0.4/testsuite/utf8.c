/* utf8.c - test the UTF-8 encoder/decoder

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
#include <errno.h>

#include <unicode.h>

/* Test UCS4->UTF8->UCS4 round trip conversion.  */
void test_utf8_sequence(unicode_char_t value, int expected_length) 
{
  unsigned char from[16];
  char to[16];
  int from_size = 4;
  int to_size = 16;
  const char *from_ptr = from;
  char *to_ptr = to;
  unicode_char_t result;
  unicode_iconv_t i = unicode_iconv_open("UTF-8", "UCS4");
  if (i == (unicode_iconv_t) -1) {
    printf("Couldn't open UTF-8 <- UCS4 converter.\n");
    exit(1);
  }

  from[0] = ((value & 0xFF000000) >> 24);
  from[1] = ((value & 0x00FF0000) >> 16);
  from[2] = ((value & 0x0000FF00) >> 8);
  from[3] = ((value & 0x000000FF));
  /* UCS4 should be serialised in Network Byte Order */
  if (unicode_iconv(i, &from_ptr, &from_size, &to_ptr, &to_size)==-1) {
    perror("unicode_iconv");
    exit(1);
  }

  *to_ptr = 0;

  if ((to_ptr - to) != expected_length) {
    printf("Character : U-%08x : expect UTF-8 length %i : generated : %i\n",
	   value, expected_length, to_ptr - to);
    exit(1);
  }

  if (unicode_get_utf8(to, &result)==NULL) {
    printf("Badly formed UTF-8 string for U-%08x\n", value);
    exit(1);
  }

  if (value != result) {
    printf("UCS4 -> UTF8 -> UCS4 conversion failed for U-%08x\n", value);
    exit(1);
  }

  unicode_iconv_close(i);
}


/* Test that UTF-8 bytes are consumed properly from input buffers.  */
void
test_utf8_results (char *input, char *expected)
{
  unicode_iconv_t context;
  size_t inbytesleft, outbytesleft;
  const char *inbuf;
  char *outbuf;
  char output[60];
  int result;

  context = unicode_iconv_open("8859-1", "UTF-8");
  if (context < 0)
    exit (1);
  inbuf = input;
  inbytesleft = strlen (inbuf);
  outbuf = output;
  outbytesleft = sizeof (output);
  result = unicode_iconv (context, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
  if (result < 0)
    exit (1);
  if (outbuf - output != strlen (expected)
      || memcmp (output, expected, outbuf - output) != 0)
    exit (1);
}

/* Test that we can split UTF-8 encodings across multiple calls to
   libunicode, and everything will still work.  INPUT is an input
   string in UTF8; SPLIT is an interesting byte position to split it
   at, which must be in the middle of a multi-byte encoding; and
   EXPECTED is the expected UCS-4 result.  */

void
test_split_utf8_results (char *input, int split,
			 unicode_char_t *expected, int expected_len)
{
  unicode_iconv_t context;
  char input_buffer[100];
  unicode_char_t output_buffer[100];
  size_t inbytesleft, outbytesleft;
  const char *inbuf;
  char *outbuf;
  int result;

  /* It is easier to do the comparison with UCS4-native.  */
  context = unicode_iconv_open("UCS4-native", "UTF-8");
  if (context < 0)
    exit (1);

  /* Copy the first half of the input, and try to convert it.  */
  memcpy (input_buffer, input, split);

  inbuf = input_buffer;
  inbytesleft = split;

  outbuf = (char *) &output_buffer;
  outbytesleft = sizeof (output_buffer);

  /* Convert the first half.  */
  result = unicode_iconv (context,
			  &inbuf, &inbytesleft, 
			  &outbuf, &outbytesleft);
  if (result < 0 && errno != EINVAL)
    exit (1);

  /* Copy the remaining input to the beginning of the buffer, and
     convert the second half.  */
  {
    int latter_len = strlen (input + split);

    memmove (input_buffer, inbuf, inbytesleft);
    memcpy (input_buffer + inbytesleft, input + split, latter_len);
    inbuf = input_buffer;
    inbytesleft += latter_len;
  }
  
  result = unicode_iconv (context,
			  &inbuf, &inbytesleft,
			  &outbuf, &outbytesleft);
  if (result < 0)
    exit (1);

  if (((unicode_char_t *) outbuf - output_buffer) != expected_len
      || (memcmp (output_buffer, expected, expected_len * sizeof (*expected))
	  != 0))
    exit (1);
}

void
test_utf8_strlen(const char *string, int expected_len)
{
  int utf8_len = unicode_strlen(string, -1);
  if (utf8_len != expected_len) {
    printf("Expected length : %i, value returned by unicode_strlen : %i\n", expected_len, utf8_len);
    exit(1);
  }
}

void
test_utf8_strncpy(const char *string, int copy_len, int expected_len)
{
  char buffer[4096];
  unicode_strncpy(buffer, string, copy_len);
  if (strlen(buffer) != expected_len) 
    {
      printf("Expected bytes : %i, number of bytes copied by unicode_strncpy : %i\n", 
  	     expected_len, strlen(buffer));
      exit(1);
    }
  if (unicode_strlen(buffer, -1) != copy_len)
    {
      printf("Expected length : %i, actual length.\n", 
	     copy_len, unicode_strlen(buffer, -1));
    }
}

void
test_last_utf8(const char *p, int expected)
{
  const char *s = unicode_last_utf8(p);
  int dif = s - p;
  if (expected == dif) return;
  printf("unicode_last_utf8 failed. Expected %i, got %i\n", expected, dif);
  exit(1);
}

void
test_display_width(const char *p, int expected)
{
  int got = unicode_string_width(p);
  if (expected == got) return;
  printf("unicode_display_width failed. Expected %i, got %i\n", expected, got);
  exit(1);
}

typedef size_t (*index_fn_t)(const char *, int);

void
test_index_function(index_fn_t fn, const char *str, int data, int expected)
{
  int returned = fn(str, data);
  if (expected != returned) {
    printf("test_index_function broke. Expected : %i, got : %i\n", expected, returned);
    exit(1);
  }
}

void
test_unicode_strchr(const char *str, unicode_char_t sought, int expected)
{
  /* expected : -1 signifies return value from unicode_strchr should be NULL */
  char *returned = unicode_strchr(str, sought);
  const char *expect = expected + str;
  if (expected == -1 && returned) {
    printf("unicode_strchr : Expected NULL, didn't get it.\n");
    exit(1);
  }
  if (!returned) {
    printf("Unexpectedly got NULL.\n");
    exit(1);
  }
  if (expect != returned) {
    printf("Got %i, was expecting %i.\n", returned - str, expected);
    exit(1);
  }
}

int main()
{
  unicode_init ();

  test_index_function(unicode_offset_to_index, "",  0, 0);
  test_index_function(unicode_index_to_offset, "",  0, 0);

  test_index_function(unicode_offset_to_index, "ABC",  0, 0);
  test_index_function(unicode_index_to_offset, "ABC",  0, 0);

  test_index_function(unicode_offset_to_index, "ABC",  1, 1);
  test_index_function(unicode_index_to_offset, "ABC",  1, 1);

  test_index_function(unicode_offset_to_index, "ABC",  2, 2);
  test_index_function(unicode_index_to_offset, "ABC",  2, 2);

  test_index_function(unicode_offset_to_index, "ΑΒΓΔΕΖΗΘΙΚΛ", 1, 2);
  test_index_function(unicode_index_to_offset, "ΑΒΓΔΕΖΗΘΙΚΛ", 2, 1);

  test_index_function(unicode_offset_to_index, "αβγδεζηθικλ", 5, 10);
  test_index_function(unicode_index_to_offset, "αβγδεζηθικλ", 10, 5);

  test_unicode_strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 'Z', 25);
  test_unicode_strchr("ΑΒΓΔΕΖΗΘΙΚΛ", 
		      0x391, 0);
  test_unicode_strchr("ΑΒΓΔΕΖΗΘΙΚΛ", 
		      0x395, 8);
  test_unicode_strchr("AΑBΒCGΓDΔEΕZΖHΗΘIΙKΚLΛ", 
		      'B', 3);

  test_utf8_strlen("", 0);
  test_utf8_strlen("a", 1);
  test_utf8_strlen("ab", 2);
  test_utf8_strlen("rɒbət wɒz hiə", 13);

  test_utf8_strncpy("test", 0, 0);
  test_utf8_strncpy("test", 1, 1);
  test_utf8_strncpy("test", 2, 2);
  test_utf8_strncpy("rɒbət wɒz hiə", 10, 13);
	
  test_last_utf8("", 0);
  test_last_utf8("a", 0);
  test_last_utf8("ab", 1);
  test_last_utf8("ɒb", 2);
  test_last_utf8("rɒ", 1);

  test_display_width("", 0);
  test_display_width(".", 1);
  test_display_width("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
  test_display_width("АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ", 32);

  test_utf8_sequence(0x00000000, 1);
  test_utf8_sequence(0x0000007f, 1);
  test_utf8_sequence(0x00000080, 2);
  test_utf8_sequence(0x000007ff, 2);
  test_utf8_sequence(0x00008000, 3);
  test_utf8_sequence(0x0000ffff, 3);
  test_utf8_sequence(0x00010000, 4);
  test_utf8_sequence(0x001fffff, 4);
  test_utf8_sequence(0x00200000, 5);
  test_utf8_sequence(0x03ffffff, 5);
  test_utf8_sequence(0x04000000, 6);
  test_utf8_sequence(0x7fffffff, 6);

  test_utf8_results ("\xc3\x96", "\326");

  {
    unicode_char_t expected[] = { 0xd6 };

    test_split_utf8_results ("\xc3\x96", 1, expected, 1);
  }

  return 0;
}
