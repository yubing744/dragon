// cxxsmoke.cc - Smoke test for C++ use.
// Written by Tom Tromey <tromey@cygnus.com>
// This file is public domain.  It is absurd to copyright it.

#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include "unicode.h"

int
main (int argc, char **argv)
{
  // We don't actually have to do anything.
  // This test just makes sure that the header can be included by a
  // C++ program without error.
  return 0;
}
