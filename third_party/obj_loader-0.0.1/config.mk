# version and name
VERSION = 0.01
AUTHOR = barondas

MACHINE=$(shell uname -s)

# includes and libs
INCS = -I.
LIBS =
ifeq ($(MACHINE), Darwin)
LIBS =
endif

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\" -std=c99
CFLAGS = -ggdb -pedantic -Wall ${INC} ${CPPFLAGS}
LDFLAGS = -ggdb ${LIBS}

# compiler and linker
CC = gcc
