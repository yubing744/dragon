/*
 *  tga.c
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

#include <stdio.h>
#include <stdlib.h>
#include "tga.h"
#include "tgaio.h"




TGA*
TGAOpen(char *file, 
	char *mode)
{
 	TGA *tga;
	FILE *fd;

	tga = (TGA*)malloc(sizeof(TGA));
	if (!tga) {
		TGA_ERROR(tga, TGA_OOM);
		return NULL;
	}
	
	tga->off = 0;
	tga->error = 0;
	tga->fgetcFunc = 0;
	tga->freadFunc = 0;
	tga->fputcFunc = 0;
	tga->fwriteFunc = 0;
	tga->fseekFunc = 0;
	tga->ftellFunc = 0;

	fd = fopen(file, mode);
	if (!fd) {
		TGA_ERROR(tga, TGA_OPEN_FAIL);
		free(tga);
		return NULL;
	}
	tga->fd = fd;
	tga->last = TGA_OK;
	return tga;
}


TGA*
TGAOpenFd(FILE *fd)
{
	TGA *tga;

	tga = (TGA*)malloc(sizeof(TGA));
	if (!tga) {
		TGA_ERROR(tga, TGA_OOM);
		return NULL;
	}

	if (!fd) {
		TGA_ERROR(tga, TGA_OPEN_FAIL);
		free(tga);
		return NULL;
	}

	tga->off = tga_ftell(tga);
	if(tga->off == -1) {
		TGA_ERROR(tga, TGA_OPEN_FAIL);
		free(tga);
		return NULL;
	}

	tga->error = 0;
	tga->fgetcFunc = 0;
	tga->freadFunc = 0;
	tga->fputcFunc = 0;
	tga->fwriteFunc = 0;
	tga->fseekFunc = 0;
	tga->ftellFunc = 0;
	
	tga->fd = fd;
	tga->last = TGA_OK;
	return tga;
}


TGA*
TGAOpenUserDef(void *io,
			TGAFGetcFunc fgetcFunc, TGAFReadFunc freadFunc,
			TGAFPutcFunc fputcFunc, TGAFWriteFunc fwriteFunc,
			TGAFSeekFunc fseekFunc, TGAFTellFunc ftellFunc)
{
	TGA *tga;

	tga = (TGA*)malloc(sizeof(TGA));
	if (!tga) {
		TGA_ERROR(tga, TGA_OOM);
		return NULL;
	}

	memset(tga, 8, sizeof(TGA));

	tga->fd = io;

	tga->error = 0;
	tga->fgetcFunc = fgetcFunc;
	tga->freadFunc = freadFunc;
	tga->fputcFunc = fputcFunc;
	tga->fwriteFunc = fwriteFunc;
	tga->fseekFunc = fseekFunc;
	tga->ftellFunc = ftellFunc;

	tga->off = tga_ftell(tga);
	if(tga->off == -1) {
		TGA_ERROR(tga, TGA_OPEN_FAIL);
		free(tga);
		return NULL;
	}

	tga->last = TGA_OK;
	return tga;
}


void 
TGAClose(TGA *tga)
{
	if (tga && !tga->fgetcFunc && !tga->freadFunc && !tga->fputcFunc && !tga->fwriteFunc && !tga->fseekFunc && !tga->ftellFunc) {
		fclose(tga->fd);
	}
	
	if (tga) {
		free(tga);
	}
}


char*
TGAStrError(tuint8 code)
{
	if (code >= TGA_ERRORS) code = TGA_ERROR;
	return tga_error_strings[code];
}


tlong
__TGASeek(TGA  *tga, 
	  tlong off, 
	  int   whence)
{
	tga_fseek(tga, off, whence);
	tga->off = tga_ftell(tga);
	return tga->off;
}


void
__TGAbgr2rgb(tbyte  *data, 
	     size_t  size, 
	     size_t  bytes)
{
	size_t i;
	tbyte tmp;
	
	for (i = 0; i < size; i += bytes) {
		tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}
}
