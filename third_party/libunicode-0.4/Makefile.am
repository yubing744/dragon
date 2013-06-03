## Process this file with automake to create Makefile.in.

AUTOMAKE_OPTIONS = gnu

SUBDIRS = . iso jis msft testsuite

bin_SCRIPTS = unicode-config

AM_CFLAGS = $(cflags)

lib_LTLIBRARIES = libunicode.la

libunicode_la_SOURCES = chartables.h convert.c convert.h decomp.c \
init.c iso8859.c latin1.c prop.c sjis.c ucs2.c ucs4.c utf8.c utf8.h utf8conv.c

include_HEADERS = unicode.h
noinst_HEADERS = decomp.h convert.h

cvs-dist: maintainer-check
	@if sed 1q $(srcdir)/NEWS | grep -e "$(VERSION)" > /dev/null; then :; else \
	  echo "NEWS not updated; not releasing" 1>&2; \
	  exit 1;				\
	fi
	cd $(srcdir) && cvs -q tag `echo "Release-$(VERSION)" | sed 's/\./-/g'`
	$(MAKE) distcheck
