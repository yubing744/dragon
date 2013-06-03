/* unicode.h - Header file for Unicode library.

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

#ifndef UNICODE_H
#define UNICODE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>      /* For size_t */

/* FIXME: assumes 32-bit int.  */
typedef unsigned int unicode_char_t;

/* These are the possible character classifications.  */
#define UNICODE_CONTROL 0
#define UNICODE_FORMAT 1
#define UNICODE_UNASSIGNED 2
#define UNICODE_PRIVATE_USE 3
#define UNICODE_SURROGATE 4
#define UNICODE_LOWERCASE_LETTER 5
#define UNICODE_MODIFIER_LETTER 6
#define UNICODE_OTHER_LETTER 7
#define UNICODE_TITLECASE_LETTER 8
#define UNICODE_UPPERCASE_LETTER 9
#define UNICODE_COMBINING_MARK 10
#define UNICODE_ENCLOSING_MARK 11
#define UNICODE_NON_SPACING_MARK 12
#define UNICODE_DECIMAL_NUMBER 13
#define UNICODE_LETTER_NUMBER 14
#define UNICODE_OTHER_NUMBER 15
#define UNICODE_CONNECT_PUNCTUATION 16
#define UNICODE_DASH_PUNCTUATION 17
#define UNICODE_CLOSE_PUNCTUATION 18
#define UNICODE_FINAL_PUNCTUATION 19
#define UNICODE_INITIAL_PUNCTUATION 20
#define UNICODE_OTHER_PUNCTUATION 21
#define UNICODE_OPEN_PUNCTUATION 22
#define UNICODE_CURRENCY_SYMBOL 23
#define UNICODE_MODIFIER_SYMBOL 24
#define UNICODE_MATH_SYMBOL 25
#define UNICODE_OTHER_SYMBOL 26
#define UNICODE_LINE_SEPARATOR 27
#define UNICODE_PARAGRAPH_SEPARATOR 28
#define UNICODE_SPACE_SEPARATOR 29

/* Call this to initialize the library.  */
void unicode_init (void);

/* Returns 1 if current locale uses UTF-8 charset.  If CHARSET is
   not null, sets *CHARSET to the name of the current locale's
   charset.  This value is statically allocated.  */
int unicode_get_charset (char **charset);

/* These are all analogs of the <ctype.h> functions.  */
int unicode_isalnum (unicode_char_t c);
int unicode_isalpha (unicode_char_t c);
int unicode_iscntrl (unicode_char_t c);
int unicode_isdigit (unicode_char_t c);
int unicode_isgraph (unicode_char_t c);
int unicode_islower (unicode_char_t c);
int unicode_isprint (unicode_char_t c);
int unicode_ispunct (unicode_char_t c);
int unicode_isspace (unicode_char_t c);
int unicode_isupper (unicode_char_t c);
int unicode_isxdigit (unicode_char_t c);
int unicode_istitle (unicode_char_t c);
int unicode_isdefined (unicode_char_t c);
int unicode_iswide (unicode_char_t c);

/* More <ctype.h> functions.  These convert between the three cases.
   See the Unicode book to understand title case.  */
unicode_char_t unicode_toupper (unicode_char_t c);
unicode_char_t unicode_tolower (unicode_char_t c);
unicode_char_t unicode_totitle (unicode_char_t c);

/* If C is a digit (according to `unicode_isdigit'), then return its
   numeric value.  Otherwise return -1.  */
int unicode_digit_value (unicode_char_t c);

/* If C is a hex digit (according to `unicode_isxdigit'), then return
   its numeric value.  Otherwise return -1.  */
int unicode_xdigit_value (unicode_char_t c);

/* Return the Unicode character type of a given character.  */
int unicode_type (unicode_char_t c);

/* If P points to the middle of a Utf-8 character, this function
   returns a pointer to the first byte of the character.  If P points
   to the start of a Utf-8 character, this function returns a pointer
   to the first byte of the previous character.  If P does not point
   to a Utf-8 character, NULL is returned.  START bounds the search;
   in no case will a value before START be returned.  */
char *unicode_previous_utf8 (const char *start, const char *p);

/* Return a pointer to the first byte of the next Utf-8 character
   after P.  This works whether P points to the start or to the middle
   of a Utf-8 character.  P is assumed to be nul-terminated.  */
char *unicode_next_utf8 (const char *p);

/* Return the length, in characters, of P, a UTF-8 string.  MAX is the
   maximum number of bytes to examine.  If MAX is less than 0, then P
   is assumed to be nul-terminated.  */
int unicode_strlen (const char *p, int max);

/* Returns the visual width, in character-size units, of P, a string.
   This value may be used for tabulation.  */
int unicode_string_width (const char *p);

/* Fetch the next Utf-8 character from P into RESULT, and return a
   pointer to the start of the next Utf-8 character.  If P is not well
   formed, will return NULL.  */
char *unicode_get_utf8 (const char *p, unicode_char_t *result);

/* Returns the offset within the string, in bytes, of the character offset
   given. */

size_t unicode_offset_to_index(const char *p, int offset);

/* Returns the offset within the string, in characters, of the byte offset
   given. */

size_t unicode_index_to_offset(const char *p, int offset);

/* Returns a pointer to the _last_ non-NULL utf-8 within the string */
	
char *unicode_last_utf8(const char *p);

/* Copies n characters from src to dest */

char *unicode_strncpy(char *dest, const char *src, size_t n);

/* Find the UTF-8 character corresponding to ch, in string p. These
   functions are equivilants to strchr and strrchr */

char *unicode_strchr(const char *p, unicode_char_t ch);
char *unicode_strrchr(const char *p, unicode_char_t ch);

/* Pads a string to fill out a requested visual width */

void unicode_pad_string(char *dest, int right, int width, const char *string);
	
/* Compute canonical ordering of a string in-place.  This rearranges
   decomposed characters in the string according to their combining
   classes.  See the Unicode manual for more information.  */
void unicode_canonical_ordering (unicode_char_t *string, size_t len);

/* Compute canonical decomposition of a character.  Returns malloc()d
   string of Unicode characters.  RESULT_LEN is set to the resulting
   length of the string.  */
unicode_char_t *unicode_canonical_decomposition (unicode_char_t ch,
						 size_t *result_len);

/* An opaque type used by the iconv workalike.  */
typedef struct unicode_iconv_i *unicode_iconv_t;

/* Create a new iconv conversion instance.  TOCODE is the destination
   charset, FROMCODE is the source charset.  Returns -1 if a charset
   name is not recognized or if out of memory.  Can set errno to
   ENOMEM or EINVAL.  */
unicode_iconv_t unicode_iconv_open (const char *tocode, const char *fromcode);

/* Close an iconv conversion instance.  */
int unicode_iconv_close (unicode_iconv_t cd);

/* Convert characters from INBUF into OUTBUF.  Parameters are in/out
   and are updated by this function.  Returns -1 and sets errno on
   error (including E2BIG if not enough room left in output buffer).
   Otherwise returns number of conversions performed; this can be 0.
   Note that on some systems EILSEQ (a possible error code) is not
   defined.  On such systems we use EBADMSG instead.  */
size_t unicode_iconv (unicode_iconv_t cd,
		      const char **inbuf, size_t *inbytesleft,
		      char **outbuf, size_t *outbytesleft);

#ifdef __cplusplus
}
#endif

#endif /* UNICODE_H */
