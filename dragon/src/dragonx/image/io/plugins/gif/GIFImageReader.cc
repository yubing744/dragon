/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2014/01/01
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

#ifdef __MSDOS__
#include <io.h>
#endif /* __MSDOS__ */

#include "gif_lib.h"
//#include "getarg.h"

#define PROGRAM_NAME    "gif2rgb"
#define VERSION_COOKIE  "1.0"

static char
    *VersionStr =
    PROGRAM_NAME
    VERSION_COOKIE
    "   Gershon Elber,  "
    __DATE__ ",   " __TIME__ "\n"
    "(C) Copyright 1989 Gershon Elber.\n";
static char
    *CtrlStr =
    PROGRAM_NAME
    " v%- 1%- o%-OutFileName!s h%- GifFile!*s";

/* Make some variables global, so we could access them faster: */
static int
    ExpNumOfColors = 8,
    ColorMapSize = 256;
static bool
    ColorFlag = false;

/* Make some variables global, so we could access them faster: */
static int
    ImageNum = 0,
    BackGround = 0,
    InterlacedOffset[] = { 0, 4, 2, 1 }, /* The way Interlaced image should. */
    InterlacedJumps[] = { 8, 8, 4, 2 };    /* be read - offsets and jumps... */
static ColorMapObject
    *ColorMap;
static bool
    OneFileFlag = false,
    HelpFlag = false;


#include <dragonx/image/io/plugins/gif/GIFImageReader.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::image::io::plugins::gif;
Import dragon::util::logging;

const Type* GIFImageReader::TYPE = TypeOf<GIFImageReader>();
static Logger* logger = Logger::getLogger(GIFImageReader::TYPE, ERROR);

GIFImageReader::GIFImageReader() {

}

GIFImageReader::~GIFImageReader() {

}

int gif_stream_read_func(GifFileType* gifFile, GifByteType* gifByte, int length) {
    InputStream* input = (InputStream*)gifFile->UserData;
    return input->read((byte*)gifByte, length);
}


/*****************************************************************************
 * Same as fprintf to stderr but with optional print.
 *****************************************************************************/
bool GifReadNoisyPrint = false;

void GifReadQprintf(char *Format, ...) {
    char Line[128];
    va_list ArgPtr;

    va_start(ArgPtr, Format);

    if (GifReadNoisyPrint) {
        logger->log_v(LOG_LEVEL_DEBUG, Format, ArgPtr);
    }

    va_end(ArgPtr);
}

void PrintGifReadError(void) {
    char *Err = GifErrorString();

    if (Err != NULL)
        logger->error("\nGIF-LIB error: %s.\n", Err);
    else
        logger->error("\nGIF-LIB undefined error %d.\n", GifError());
}

BufferedImage* GIFImageReader::read(InputStream* input) throw(IOException*) {
    GifRecordType RecordType;
    GifByteType *Extension;

    GifRowType *rowBuffer;
    GifFileType *GifFile;

    int Row, Col, Width, Height, ExtCode;
    int ImageNum = 0;
    int Count = 0;
    GifRowType GifRow;

    if ((GifFile = DGifOpen(input, gif_stream_read_func)) == NULL) {
        throw new IOException("error in open git inputstream!");
    }

    if ((rowBuffer = (GifRowType *)malloc(GifFile->SHeight * sizeof(GifRowType))) == NULL) {
        throw new IOException("Failed to allocate memory required, aborted.");
    }

    int rowByteSize = GifFile->SWidth * sizeof(GifPixelType);


    if ((rowBuffer[0] = (GifRowType) malloc(rowByteSize)) == NULL) {
        throw new IOException("Failed to allocate memory required, aborted.");
    }

    for (int i = 0; i < GifFile->SWidth; i++) {
        rowBuffer[0][i] = GifFile->SBackGroundColor;
    }

    for (int i = 1; i < GifFile->SHeight; i++) {
        /* Allocate the other rows, and set their color to background too: */
        if ((rowBuffer[i] = (GifRowType) malloc(rowByteSize)) == NULL)
            throw new IOException("Failed to allocate memory required, aborted.");

        memcpy(rowBuffer[i], rowBuffer[0], rowByteSize);
    }

    do {
        if (DGifGetRecordType(GifFile, &RecordType) == GIF_ERROR) {
            PrintGifReadError();
            throw new IOException("error in read gif record type!");
        }

        switch (RecordType) {
            case IMAGE_DESC_RECORD_TYPE:
                if (DGifGetImageDesc(GifFile) == GIF_ERROR) {
                    PrintGifReadError();
                    throw new IOException("error in get image desc info!");
                }

                Row = GifFile->Image.Top; /* Image Position relative to Screen. */
                Col = GifFile->Image.Left;

                Width = GifFile->Image.Width;
                Height = GifFile->Image.Height;

                GifReadQprintf("\n%s: Image %d at (%d, %d) [%dx%d]:     ",
                    PROGRAM_NAME, ++ImageNum, Col, Row, Width, Height);

                if (GifFile->Image.Left + GifFile->Image.Width > GifFile->SWidth ||
                    GifFile->Image.Top + GifFile->Image.Height > GifFile->SHeight) {

                    String* msg = String::format("Image %d is not confined to screen dimension, aborted.\n", ImageNum);
                    IOException* e = new IOException(msg);
                    SafeDelete(msg);

                    throw e;
                }

                if (GifFile->Image.Interlace) {
                    int i, j;
                    /* Need to perform 4 passes on the images: */
                    for (Count = i = 0; i < 4; i++) {
                        for (j = Row + InterlacedOffset[i]; j < Row + Height; j += InterlacedJumps[i]) {
                            GifReadQprintf("\b\b\b\b%-4d", Count++);

                            if (DGifGetLine(GifFile, &rowBuffer[j][Col], Width) == GIF_ERROR) {
                                PrintGifReadError();
                                throw new IOException("error in read gif row data!");
                            }
                        }
                    }
                } else {
                    int i;
                    for (i = 0; i < Height; i++) {
                        GifReadQprintf("\b\b\b\b%-4d", i);

                        if (DGifGetLine(GifFile, &rowBuffer[Row++][Col], Width) == GIF_ERROR) {
                            PrintGifReadError();
                            throw new IOException("error in read gif row data!");
                        }
                    }
                }
                break;
            case EXTENSION_RECORD_TYPE:
                /* Skip any extension blocks in file: */
                if (DGifGetExtension(GifFile, &ExtCode, &Extension) == GIF_ERROR) {
                    PrintGifReadError();
                    throw new IOException("error in read gif extension data!");
                }

                while (Extension != NULL) {
                    if (DGifGetExtensionNext(GifFile, &Extension) == GIF_ERROR) {
                        PrintGifReadError();
                        throw new IOException("error in read gif extension data!");
                    }
                }
                break;
            case TERMINATE_RECORD_TYPE:
                break;
            default:            /* Should be traps by DGifGetRecordType. */
                break;
        }

    } while(RecordType != TERMINATE_RECORD_TYPE);

    ColorMapObject* ColorMap = (GifFile->Image.ColorMap
        ? GifFile->Image.ColorMap
        : GifFile->SColorMap);

    if (ColorMap == NULL) {
        throw new IOException("error in get gif color map!");
    }

    int imageWidth = GifFile->SWidth;
    int imageHeight = GifFile->SHeight;

    GifByteType* BufferP = NULL;
    GifColorType *ColorMapEntry = NULL;

    BufferedImage* image = new BufferedImage(imageWidth, imageHeight, ColorModel::TYPE_24_RGB);
    GifByteType* Buffer = (GifByteType*)(const_cast<byte*>(image->getRawData()));
    BufferP = Buffer;

    for (int i = 0; i < imageHeight; i++) {
        GifRow = rowBuffer[i];
        GifReadQprintf("\b\b\b\b%-4d", imageHeight - i);

        for (int j = 0; j < imageWidth; j++) {
            ColorMapEntry = &ColorMap->Colors[GifRow[j]];

            *BufferP++ = ColorMapEntry->Red;
            *BufferP++ = ColorMapEntry->Green;
            *BufferP++ = ColorMapEntry->Blue;
        }
    }

    DGifCloseFile(GifFile);

    return image;
}



