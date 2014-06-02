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
#include <fcntl.h>
//#include <stdbool.h>

#ifdef __MSDOS__
#include <io.h>
#endif /* __MSDOS__ */

#include "gif_lib.h"
//#include "getarg.h"

#define PROGRAM_NAME    "gif_image_writer"
#define VERSION_COOKIE "1.0"

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
    " v%- c%-#Colors!d 1%- s!-Width|Height!d!d h%- RGBFile!*s";

/* Make some variables global, so we could access them faster: */
static int
    ExpNumOfColors = 8,
    ColorMapSize = 256;
static bool
    ColorFlag = false,
    OneFileFlag = false,
    HelpFlag = false;

#include <dragonx/image/io/plugins/gif/GIFImageWriter.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::image::io::plugins::gif;
Import dragon::util::logging;

const Type* GIFImageWriter::TYPE = TypeOf<GIFImageWriter>();
static Logger* logger = Logger::getLogger(GIFImageWriter::TYPE, ERROR);

GIFImageWriter::GIFImageWriter() {

}

GIFImageWriter::~GIFImageWriter() {

}

/******************************************************************************
 * Code to quantize high resolution image into lower one. You may want to
 * peek into the following article this code is based on:
 * "Color Image Quantization for frame buffer Display", by Paul Heckbert
 * SIGGRAPH 1982 page 297-307.
 ******************************************************************************
 * History:
 * 5 Jan 90 - Version 1.0 by Gershon Elber.
 *****************************************************************************/

#define ABS(x)    ((x) > 0 ? (x) : (-(x)))

#define COLOR_ARRAY_SIZE 32768
#define BITS_PER_PRIM_COLOR 5
#define MAX_PRIM_COLOR      0x1f

static int SortRGBAxis;

typedef struct QuantizedColorType {
    GifByteType RGB[3];
    GifByteType NewColorIndex;
    long Count;
    struct QuantizedColorType *Pnext;
} QuantizedColorType;

typedef struct NewColorMapType {
    GifByteType RGBMin[3], RGBWidth[3];
    unsigned int NumEntries; /* # of QuantizedColorType in linked list below */
    unsigned long Count; /* Total number of pixels in all the entries */
    QuantizedColorType *QuantizedColors;
} NewColorMapType;

static int SubdivColorMap(NewColorMapType * NewColorSubdiv,
                          unsigned int ColorMapSize,
                          unsigned int *NewColorMapSize);
static int SortCmpRtn(const void *Entry1, const void *Entry2);


/*****************************************************************************
 * Same as fprintf to stderr but with optional print.
 *****************************************************************************/
bool GifWriteNoisyPrint = true;

void GifWriteQprintf(char *Format, ...) {
    char Line[128];
    va_list ArgPtr;

    va_start(ArgPtr, Format);

    if (GifWriteNoisyPrint) {
        logger->logV(LOG_LEVEL_DEBUG, Format, ArgPtr);
    }

    va_end(ArgPtr);
}

void PrintGifWriteError(void) {
    char *Err = GifErrorString();

    if (Err != NULL)
        logger->error("\nGIF-LIB error: %s.\n", Err);
    else
        logger->error("\nGIF-LIB undefined error %d.\n", GifError());
}

/******************************************************************************
 * Quantize high resolution image into lower one. Input image consists of a
 * 2D array for each of the RGB colors with size Width by Height. There is no
 * Color map for the input. Output is a quantized image with 2D array of
 * indexes into the output color map.
 *   Note input image can be 24 bits at the most (8 for red/green/blue) and
 * the output has 256 colors at the most (256 entries in the color map.).
 * ColorMapSize specifies size of color map up to 256 and will be updated to
 * real size before returning.
 *   Also non of the parameter are allocated by this routine.
 *   This function returns GIF_OK if succesfull, GIF_ERROR otherwise.
 ******************************************************************************/
static int
QuantizeBuffer(unsigned int Width,
               unsigned int Height,
               int *ColorMapSize,
               const RenderedImage* image,
               GifByteType * OutputBuffer,
               GifColorType * OutputColorMap) {

    unsigned int Index, NumOfEntries;
    int i, j, MaxRGBError[3];
    unsigned int NewColorMapSize;
    long Red, Green, Blue;
    NewColorMapType NewColorSubdiv[256];
    QuantizedColorType *ColorArrayEntries, *QuantizedColor;

    ColorArrayEntries = (QuantizedColorType *)malloc(
                           sizeof(QuantizedColorType) * COLOR_ARRAY_SIZE);
    if (ColorArrayEntries == NULL) {
        return GIF_ERROR;
    }

    for (i = 0; i < COLOR_ARRAY_SIZE; i++) {
        ColorArrayEntries[i].RGB[0] = i >> (2 * BITS_PER_PRIM_COLOR);
        ColorArrayEntries[i].RGB[1] = (i >> BITS_PER_PRIM_COLOR) & MAX_PRIM_COLOR;
        ColorArrayEntries[i].RGB[2] = i & MAX_PRIM_COLOR;

        ColorArrayEntries[i].Count = 0;
    }

    /* Sample the colors and their distribution: */
    for (i = 0; i < (int)(Width * Height); i++) {
        Index = ((image->getRed(i) >> (8 - BITS_PER_PRIM_COLOR)) <<
                  (2 * BITS_PER_PRIM_COLOR)) +
                ((image->getGreen(i) >> (8 - BITS_PER_PRIM_COLOR)) <<
                  BITS_PER_PRIM_COLOR) +
                (image->getBlue(i) >> (8 - BITS_PER_PRIM_COLOR));
        ColorArrayEntries[Index].Count++;
    }

    /* Put all the colors in the first entry of the color map, and call the
     * recursive subdivision process.  */
    for (i = 0; i < 256; i++) {
        NewColorSubdiv[i].QuantizedColors = NULL;
        NewColorSubdiv[i].Count = NewColorSubdiv[i].NumEntries = 0;
        for (j = 0; j < 3; j++) {
            NewColorSubdiv[i].RGBMin[j] = 0;
            NewColorSubdiv[i].RGBWidth[j] = 255;
        }
    }

    /* Find the non empty entries in the color table and chain them: */
    for (i = 0; i < COLOR_ARRAY_SIZE; i++)
        if (ColorArrayEntries[i].Count > 0)
            break;
    QuantizedColor = NewColorSubdiv[0].QuantizedColors = &ColorArrayEntries[i];
    NumOfEntries = 1;
    while (++i < COLOR_ARRAY_SIZE)
        if (ColorArrayEntries[i].Count > 0) {
            QuantizedColor->Pnext = &ColorArrayEntries[i];
            QuantizedColor = &ColorArrayEntries[i];
            NumOfEntries++;
        }
    QuantizedColor->Pnext = NULL;

    NewColorSubdiv[0].NumEntries = NumOfEntries; /* Different sampled colors */
    NewColorSubdiv[0].Count = ((long)Width) * Height; /* Pixels */
    NewColorMapSize = 1;

    if (SubdivColorMap(NewColorSubdiv, *ColorMapSize, &NewColorMapSize) !=
       GIF_OK) {
        free((char *)ColorArrayEntries);
        return GIF_ERROR;
    }

    if (NewColorMapSize < *ColorMapSize) {
        /* And clear rest of color map: */
        for (i = NewColorMapSize; i < *ColorMapSize; i++)
            OutputColorMap[i].Red = OutputColorMap[i].Green =
                OutputColorMap[i].Blue = 0;
    }

    /* Average the colors in each entry to be the color to be used in the
     * output color map, and plug it into the output color map itself. */
    for (i = 0; i < NewColorMapSize; i++) {
        if ((j = NewColorSubdiv[i].NumEntries) > 0) {
            QuantizedColor = NewColorSubdiv[i].QuantizedColors;
            Red = Green = Blue = 0;
            while (QuantizedColor) {
                QuantizedColor->NewColorIndex = i;
                Red += QuantizedColor->RGB[0];
                Green += QuantizedColor->RGB[1];
                Blue += QuantizedColor->RGB[2];
                QuantizedColor = QuantizedColor->Pnext;
            }
            OutputColorMap[i].Red = (Red << (8 - BITS_PER_PRIM_COLOR)) / j;
            OutputColorMap[i].Green = (Green << (8 - BITS_PER_PRIM_COLOR)) / j;
            OutputColorMap[i].Blue = (Blue << (8 - BITS_PER_PRIM_COLOR)) / j;
        } else
            fprintf(stderr,
                    "\n%s: Null entry in quantized color map - that's weird.\n",
                    PROGRAM_NAME);
    }

    /* Finally scan the input buffer again and put the mapped index in the
     * output buffer.  */
    MaxRGBError[0] = MaxRGBError[1] = MaxRGBError[2] = 0;
    for (i = 0; i < (int)(Width * Height); i++) {
        Index = ((image->getRed(i) >> (8 - BITS_PER_PRIM_COLOR)) <<
                 (2 * BITS_PER_PRIM_COLOR)) +
                ((image->getGreen(i) >> (8 - BITS_PER_PRIM_COLOR)) <<
                 BITS_PER_PRIM_COLOR) +
                (image->getBlue(i) >> (8 - BITS_PER_PRIM_COLOR));
        Index = ColorArrayEntries[Index].NewColorIndex;
        OutputBuffer[i] = Index;

        if (MaxRGBError[0] < ABS(OutputColorMap[Index].Red - image->getRed(i)))
            MaxRGBError[0] = ABS(OutputColorMap[Index].Red - image->getRed(i));

        if (MaxRGBError[1] < ABS(OutputColorMap[Index].Green - image->getGreen(i)))
            MaxRGBError[1] = ABS(OutputColorMap[Index].Green - image->getGreen(i));

        if (MaxRGBError[2] < ABS(OutputColorMap[Index].Blue - image->getBlue(i)))
            MaxRGBError[2] = ABS(OutputColorMap[Index].Blue - image->getBlue(i));
    }

#ifdef DEBUG
    fprintf(stderr,
            "Quantization L(0) errors: Red = %d, Green = %d, Blue = %d.\n",
            MaxRGBError[0], MaxRGBError[1], MaxRGBError[2]);
#endif /* DEBUG */

    free((char *)ColorArrayEntries);

    *ColorMapSize = NewColorMapSize;

    return GIF_OK;
}

/******************************************************************************
 * Routine to subdivide the RGB space recursively using median cut in each
 * axes alternatingly until ColorMapSize different cubes exists.
 * The biggest cube in one dimension is subdivide unless it has only one entry.
 * Returns GIF_ERROR if failed, otherwise GIF_OK.
 ******************************************************************************/
static int
SubdivColorMap(NewColorMapType * NewColorSubdiv,
               unsigned int ColorMapSize,
               unsigned int *NewColorMapSize) {

    int MaxSize;
    unsigned int i, j, Index = 0, NumEntries, MinColor, MaxColor;
    long Sum, Count;
    QuantizedColorType *QuantizedColor, **SortArray;

    while (ColorMapSize > *NewColorMapSize) {
        /* Find candidate for subdivision: */
        MaxSize = -1;
        for (i = 0; i < *NewColorMapSize; i++) {
            for (j = 0; j < 3; j++) {
                if ((((int)NewColorSubdiv[i].RGBWidth[j]) > MaxSize) &&
                      (NewColorSubdiv[i].NumEntries > 1)) {
                    MaxSize = NewColorSubdiv[i].RGBWidth[j];
                    Index = i;
                    SortRGBAxis = j;
                }
            }
        }

        if (MaxSize == -1)
            return GIF_OK;

        /* Split the entry Index into two along the axis SortRGBAxis: */

        /* Sort all elements in that entry along the given axis and split at
         * the median.  */
        SortArray = (QuantizedColorType **)malloc(
                      sizeof(QuantizedColorType *) * 
                      NewColorSubdiv[Index].NumEntries);
        if (SortArray == NULL)
            return GIF_ERROR;
        for (j = 0, QuantizedColor = NewColorSubdiv[Index].QuantizedColors;
             j < NewColorSubdiv[Index].NumEntries && QuantizedColor != NULL;
             j++, QuantizedColor = QuantizedColor->Pnext)
            SortArray[j] = QuantizedColor;

        qsort(SortArray, NewColorSubdiv[Index].NumEntries,
              sizeof(QuantizedColorType *), SortCmpRtn);

        /* Relink the sorted list into one: */
        for (j = 0; j < NewColorSubdiv[Index].NumEntries - 1; j++)
            SortArray[j]->Pnext = SortArray[j + 1];
        SortArray[NewColorSubdiv[Index].NumEntries - 1]->Pnext = NULL;
        NewColorSubdiv[Index].QuantizedColors = QuantizedColor = SortArray[0];
        free((char *)SortArray);

        /* Now simply add the Counts until we have half of the Count: */
        Sum = NewColorSubdiv[Index].Count / 2 - QuantizedColor->Count;
        NumEntries = 1;
        Count = QuantizedColor->Count;
        while (QuantizedColor->Pnext != NULL &&
           (Sum -= QuantizedColor->Pnext->Count) >= 0 &&
               QuantizedColor->Pnext->Pnext != NULL) {
            QuantizedColor = QuantizedColor->Pnext;
            NumEntries++;
            Count += QuantizedColor->Count;
        }
        /* Save the values of the last color of the first half, and first
         * of the second half so we can update the Bounding Boxes later.
         * Also as the colors are quantized and the BBoxes are full 0..255,
         * they need to be rescaled.
         */
        MaxColor = QuantizedColor->RGB[SortRGBAxis]; /* Max. of first half */
        /* coverity[var_deref_op] */
        MinColor = QuantizedColor->Pnext->RGB[SortRGBAxis]; /* of second */
        MaxColor <<= (8 - BITS_PER_PRIM_COLOR);
        MinColor <<= (8 - BITS_PER_PRIM_COLOR);

        /* Partition right here: */
        NewColorSubdiv[*NewColorMapSize].QuantizedColors =
           QuantizedColor->Pnext;
        QuantizedColor->Pnext = NULL;
        NewColorSubdiv[*NewColorMapSize].Count = Count;
        NewColorSubdiv[Index].Count -= Count;
        NewColorSubdiv[*NewColorMapSize].NumEntries =
           NewColorSubdiv[Index].NumEntries - NumEntries;
        NewColorSubdiv[Index].NumEntries = NumEntries;

        for (j = 0; j < 3; j++) {
            NewColorSubdiv[*NewColorMapSize].RGBMin[j] =
               NewColorSubdiv[Index].RGBMin[j];
            NewColorSubdiv[*NewColorMapSize].RGBWidth[j] =
               NewColorSubdiv[Index].RGBWidth[j];
        }

        NewColorSubdiv[*NewColorMapSize].RGBWidth[SortRGBAxis] =
           NewColorSubdiv[*NewColorMapSize].RGBMin[SortRGBAxis] +
           NewColorSubdiv[*NewColorMapSize].RGBWidth[SortRGBAxis] - MinColor;
        NewColorSubdiv[*NewColorMapSize].RGBMin[SortRGBAxis] = MinColor;

        NewColorSubdiv[Index].RGBWidth[SortRGBAxis] =
           MaxColor - NewColorSubdiv[Index].RGBMin[SortRGBAxis];

        (*NewColorMapSize)++;
    }

    return GIF_OK;
}

/****************************************************************************
 * Routine called by qsort to compare two entries.
 ****************************************************************************/
static int
SortCmpRtn(const void *Entry1,
           const void *Entry2) {

    return (*((QuantizedColorType **) Entry1))->RGB[SortRGBAxis] -
       (*((QuantizedColorType **) Entry2))->RGB[SortRGBAxis];
}

int gif_write_stream_func(GifFileType* gifFile, const GifByteType* gifByte, int length) {
    OutputStream* output = (OutputStream*)gifFile->UserData;
    output->write((byte*)gifByte, length);
    return length;
}

void GIFImageWriter::write(const RenderedImage* image, OutputStream* output) throw(IOException*) {  
    const ColorModel* colorModel = image->getColorModel();
    const byte* pData = (byte*)image->getRawData();

    int width = image->getWidth();
    int height = image->getHeight();
    int bitCount = colorModel->getBitCount();
    bool hasAlpha = colorModel->hasAlpha();

    GifFileType *GifFile;

    GifByteType *Buffer, *BufferP = NULL;
    ColorMapObject *OutputColorMap = NULL;
    GifByteType *OutputBuffer = NULL;

    /* Open stdout for the output file: */
    if ((GifFile = EGifOpen(output, gif_write_stream_func)) == NULL) {
        EGifCloseFile(GifFile);
        throw new IOException("error in open gif stream!");
    }

    int ColorMapSize = 1 << ExpNumOfColors;

    if ((OutputColorMap = MakeMapObject(ColorMapSize, NULL)) == NULL ||
        (OutputBuffer = (GifByteType *) malloc(width * height * sizeof(GifByteType))) == NULL) {
        throw new IOException("Failed to allocate memory required, aborted.");
    }

    if (QuantizeBuffer(width, height, &ColorMapSize, image, 
               OutputBuffer, OutputColorMap->Colors) == GIF_ERROR) {
        EGifCloseFile(GifFile);
        throw new IOException("error in quantize buffer!");
    }

    GifByteType *Ptr = OutputBuffer;

    // put screen desc
    if (EGifPutScreenDesc(GifFile, width, height, ExpNumOfColors, 0, OutputColorMap) == GIF_ERROR) {
        EGifCloseFile(GifFile);
        throw new IOException("error in put gif image desc!");
    }

    // put image desc
    if (EGifPutImageDesc(GifFile, 0, 0, width, height, false, NULL) == GIF_ERROR) {
        EGifCloseFile(GifFile);
        throw new IOException("error in put gif image desc!");
    }

    GifWriteQprintf("\n%s: Image 1 at (%d, %d) [%dx%d]:     ",
           PROGRAM_NAME, GifFile->Image.Left, GifFile->Image.Top,
           GifFile->Image.Width, GifFile->Image.Height);

    for (int i = 0; i < height; i++) {
        if (EGifPutLine(GifFile, Ptr, width) == GIF_ERROR) {
            EGifCloseFile(GifFile);
            throw new IOException("error in put gif line data!");
        }

        GifWriteQprintf("\b\b\b\b%-4d", height - i - 1);

        Ptr += (width * sizeof(GifByteType));
    }

    EGifCloseFile(GifFile);
    FreeMapObject(OutputColorMap);
}
