/*
 *  tgaio.h
 *
 *  Copyright (C) 2001-2002, Matthias Brueckner
 *  Copyright (C) 2011, Alexander Azhevsky, Andrey Antsut
 *  
 *  This file is part of the TGA Extended library (libtga-ex).
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __TGA_IO_H
#define __TGA_IO_H 1

#include "tga.h"


int tga_fgetc(TGA* tga);

size_t tga_fread(TGA* tga, void* buffer, size_t size, size_t count);

int tga_fputc(TGA* tga, int c);

size_t tga_fwrite(TGA* tga, const void* buffer, size_t size, size_t count);

void tga_fseek(TGA* tga, long offset, int origin);

long tga_ftell(TGA* tga);


#endif /* __TGA_IO_H */
