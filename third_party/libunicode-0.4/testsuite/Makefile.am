## Process this file with automake to create Makefile.in.

std = ordering cxxsmoke roundtrip tinyiconv utf8 ucs4

AM_CPPFLAGS = -I$(srcdir)/..

# The following does not work correctly under automake-1.4a,
# because of some bugs in variable expansion. This is apparently 
# fixed in devel versions, but until then, we'll avoid
# the conditional, since it isn't doing anything right now
# anyways

# if NATIVE_ICONV
# check_PROGRAMS = $(std)
# else
# check_PROGRAMS = $(std) ## iconv
# endif

check_PROGRAMS = $(std)

TESTS = $(check_PROGRAMS)

ordering_SOURCES = ordering.c
ordering_LDADD = ../libunicode.la

# A C++ smoke test.
cxxsmoke_SOURCES = cxxsmoke.cc
cxxsmoke_LDADD = ../libunicode.la

# A roundtrip test
roundtrip_SOURCES = roundtrip.c
roundtrip_LDADD = ../libunicode.la

# Tests for the UTF-8 encoder/decoder
utf8_SOURCES = utf8.c
utf8_LDADD = ../libunicode.la

# Test for UCS-4 encoder/decoder.
ucs4_SOURCES = ucs4.c
ucs4_LDADD = ../libunicode.la

tinyiconv_SOURCES = tinyiconv.c
tinyiconv_LDADD = ../libunicode.la
