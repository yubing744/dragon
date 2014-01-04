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
 * Created:     2013/12/30
 **********************************************************************/

#include <iostream>
#include <fstream>
#include <string>

#include <dragonx/image/io/plugins/bmp/BMPImageWriter.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::image::io::plugins::bmp;
Import dragon::util::logging;

const Type* BMPImageWriter::TYPE = TypeOf<BMPImageWriter>();
static Logger* logger = Logger::getLogger(BMPImageWriter::TYPE, ERROR);

BMPImageWriter::BMPImageWriter() {

}

BMPImageWriter::~BMPImageWriter() {

}

#ifndef __LITTLE_ENDIAN__
    #ifndef __BIG_ENDIAN__
        #define __LITTLE_ENDIAN__
    #endif
#endif

#ifdef __LITTLE_ENDIAN__
    #define BITMAP_SIGNATURE 0x4d42
#else
    #define BITMAP_SIGNATURE 0x424d
#endif

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
    typedef unsigned __int32 uint32_t;
    typedef unsigned __int16 uint16_t;
    typedef unsigned __int8 uint8_t;
    typedef __int32 int32_t;
#elif defined(__GNUC__) || defined(__CYGWIN__) || defined(__MWERKS__) || defined(__WATCOMC__) || defined(__PGI) || defined(__LCC__)
    #include <stdint.h>
#else
    typedef unsigned int uint32_t;
    typedef unsigned short int uint16_t;
    typedef unsigned char uint8_t;
    typedef int int32_t;
#endif

#pragma pack(push, 1)

typedef struct _BITMAP_FILEHEADER {
    uint16_t Signature;
    uint32_t Size;
    uint32_t Reserved;
    uint32_t BitsOffset;
} BITMAP_FILEHEADER;

#define BITMAP_FILEHEADER_SIZE 14

typedef struct _BITMAP_HEADER {
    uint32_t HeaderSize;
    int32_t Width;
    int32_t Height;
    uint16_t Planes;
    uint16_t BitCount;
    uint32_t Compression;
    uint32_t SizeImage;
    int32_t PelsPerMeterX;
    int32_t PelsPerMeterY;
    uint32_t ClrUsed;
    uint32_t ClrImportant;
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t AlphaMask;
    uint32_t CsType;
    uint32_t Endpoints[9]; // see http://msdn2.microsoft.com/en-us/library/ms536569.aspx
    uint32_t GammaRed;
    uint32_t GammaGreen;
    uint32_t GammaBlue;
} BITMAP_HEADER;

typedef struct _RGBA {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint8_t Alpha;
} RGBA;

typedef struct _BGRA {
    uint8_t Blue;
    uint8_t Green;
    uint8_t Red;
    uint8_t Alpha;
} BGRA;

#pragma pack(pop)

class CColor {
public:
    static inline unsigned int BitCountByMask(unsigned int Mask) {
        unsigned int BitCount = 0;

        while (Mask) {
            Mask &= Mask - 1;
            BitCount++;
        }

        return BitCount;
    }

    static inline unsigned int BitPositionByMask(unsigned int Mask) {
        return BitCountByMask((Mask & (~Mask + 1)) - 1);
    }

    static inline unsigned int ComponentByMask(unsigned int Color, unsigned int Mask) {
        unsigned int Component = Color & Mask;
        return Component >> BitPositionByMask(Mask);
    }

    static inline unsigned int BitCountToMask(unsigned int BitCount) {
        return (BitCount == 32) ? 0xFFFFFFFF : (1 << BitCount) - 1;
    }

    static unsigned int Convert(unsigned int Color, unsigned int FromBitCount, unsigned int ToBitCount) {
        if (ToBitCount < FromBitCount) {
            Color >>= (FromBitCount - ToBitCount);
        } else {
            Color <<= (ToBitCount - FromBitCount);
            if (Color > 0) {
                Color |= BitCountToMask(ToBitCount - FromBitCount);
            }
        }

        return Color;
    }
};

/* Copies internal RGBA buffer to user specified buffer and converts it into destination
 * bit format specified by component masks.
 *
 * Typical Bitmap color formats (BGR/BGRA):
 *
 * Masks for 16 bit (5-5-5): ALPHA = 0x00000000, RED = 0x00007C00, GREEN = 0x000003E0, BLUE = 0x0000001F
 * Masks for 16 bit (5-6-5): ALPHA = 0x00000000, RED = 0x0000F800, GREEN = 0x000007E0, BLUE = 0x0000001F
 * Masks for 24 bit: ALPHA = 0x00000000, RED = 0x00FF0000, GREEN = 0x0000FF00, BLUE = 0x000000FF
 * Masks for 32 bit: ALPHA = 0xFF000000, RED = 0x00FF0000, GREEN = 0x0000FF00, BLUE = 0x000000FF
 *
 * Other color formats (RGB/RGBA):
 *
 * Masks for 32 bit (RGBA): ALPHA = 0xFF000000, RED = 0x000000FF, GREEN = 0x0000FF00, BLUE = 0x00FF0000
 *
 * Bit count will be rounded to next 8 bit boundary. If IncludePadding is true, it will be ensured
 * that line width is a multiple of 4. padding bytes are included if necessary.
 *
 * NOTE: systems with big endian byte order may require masks in inversion order.
 */
bool GetBits(const RenderedImage* image, void* Buffer, unsigned int &Size, unsigned int RedMask, unsigned int GreenMask, unsigned int BlueMask, unsigned int AlphaMask, bool IncludePadding = true) {
    bool Result = false;

    int bitmapSize = image->getWidth() * image->getHeight();
    const RGBA* bitmapData = (RGBA*)image->getRawData();

    uint32_t BitCountRed = CColor::BitCountByMask(RedMask);
    uint32_t BitCountGreen = CColor::BitCountByMask(GreenMask);
    uint32_t BitCountBlue = CColor::BitCountByMask(BlueMask);
    uint32_t BitCountAlpha = CColor::BitCountByMask(AlphaMask);
    
    unsigned int BitCount = (BitCountRed + BitCountGreen + BitCountBlue + BitCountAlpha + 7) & ~7;

    if (BitCount > 32) {
        return false;
    }
    
    unsigned int w = image->getWidth();
    //unsigned int LineWidth = (w + 3) & ~3;
    unsigned int dataBytesPerLine = (w * BitCount + 7) / 8;
    unsigned int LineWidth = (dataBytesPerLine + 3) & ~3;

    if (Size == 0 || Buffer == 0) {
        //Size = (LineWidth * GetHeight() * BitCount) / 8 + sizeof(unsigned int);
        Size = (image->getWidth() * image->getHeight() * BitCount) / 8 + sizeof(unsigned int);
        return true;
    }

    uint8_t* BufferPtr = (uint8_t*) Buffer;
    
    Result = true;

    uint32_t BitPosRed = CColor::BitPositionByMask(RedMask);
    uint32_t BitPosGreen = CColor::BitPositionByMask(GreenMask);
    uint32_t BitPosBlue = CColor::BitPositionByMask(BlueMask);
    uint32_t BitPosAlpha = CColor::BitPositionByMask(AlphaMask);
    
    unsigned int j = 0;

    for (unsigned int i = 0; i < bitmapSize; i++) {
        *(uint32_t*) BufferPtr =
            (CColor::Convert(bitmapData[i].Blue, 8, BitCountBlue) << BitPosBlue) |
            (CColor::Convert(bitmapData[i].Green, 8, BitCountGreen) << BitPosGreen) | 
            (CColor::Convert(bitmapData[i].Red, 8, BitCountRed) << BitPosRed) | 
            (CColor::Convert(bitmapData[i].Alpha, 8, BitCountAlpha) << BitPosAlpha);
        
        if (IncludePadding) {
            j++;
            if (j >= w) {
                for (unsigned int k = 0; k < LineWidth - dataBytesPerLine; k++) {
                    BufferPtr += (BitCount >> 3);
                }
                j = 0;
            }
        }

        BufferPtr += (BitCount >> 3);
    }
    
    Size -= sizeof(unsigned int);

    return Result;
}

/* See GetBits(). 
 * It creates a corresponding color table (palette) which have to be destroyed by the user after usage.
 *
 * Supported Bit depths are: 4, 8
 *
 * Todo: Optimize, use optimized palette, do ditehring (see my dithering class), support padding for 4 bit bitmaps
 */
bool GetBitsWithPalette(const RenderedImage* image, void* Buffer, unsigned int &Size, unsigned int BitCount, BGRA* &Palette, unsigned int &PaletteSize, bool OptimalPalette = false, bool IncludePadding = true) {
    bool Result = false;

    if (BitCount > 16) {
        return false;
    }

    int bitmapSize = image->getWidth() * image->getHeight();
    const RGBA* bitmapData = (RGBA*)image->getRawData();

    unsigned int w = image->getWidth();
    unsigned int dataBytesPerLine = (w * BitCount + 7) / 8;
    unsigned int LineWidth = (dataBytesPerLine + 3) & ~3;

    if (Size == 0 || Buffer == 0) {
        Size = (LineWidth * image->getHeight() * BitCount) / 8;
        return true;
    }
    

    if (OptimalPalette) {
        PaletteSize = 0;
        // Not implemented
    } else {
        if (BitCount == 1) {
            PaletteSize = 2;
            // Not implemented: Who need that?
        } else if (BitCount == 4) { // 2:2:1
            PaletteSize = 16;
            Palette = new BGRA[PaletteSize];
            for (int r = 0; r < 4; r++) {
                for (int g = 0; g < 2; g++) {
                    for (int b = 0; b < 2; b++) {
                        Palette[r | g << 2 | b << 3].Red = r ? (r << 6) | 0x3f : 0;
                        Palette[r | g << 2 | b << 3].Green = g ? (g << 7) | 0x7f : 0;
                        Palette[r | g << 2 | b << 3].Blue = b ? (b << 7) | 0x7f : 0;
                        Palette[r | g << 2 | b << 3].Alpha = 0xff;
                    }
                }
            }
        } else if (BitCount == 8) { // 3:3:2
            PaletteSize = 256;
            Palette = new BGRA[PaletteSize];
            for (int r = 0; r < 8; r++) {
                for (int g = 0; g < 8; g++) {
                    for (int b = 0; b < 4; b++) {
                        Palette[r | g << 3 | b << 6].Red = r ? (r << 5) | 0x1f : 0;
                        Palette[r | g << 3 | b << 6].Green = g ? (g << 5) | 0x1f : 0;
                        Palette[r | g << 3 | b << 6].Blue = b ? (b << 6) | 0x3f : 0;
                        Palette[r | g << 3 | b << 6].Alpha = 0xff;
                    }
                }
            }
        } else if (BitCount == 16) { // 5:5:5
            // Not implemented
        }
    }

    unsigned int j = 0;
    uint8_t* BufferPtr = (uint8_t*) Buffer;
    
    for (unsigned int i = 0; i < bitmapSize; i++) {
        if (BitCount == 1) {
            // Not implemented: Who needs that?
        } else if (BitCount == 4) {
            *BufferPtr = ((bitmapData[i].Red >> 6) | (bitmapData[i].Green >> 7) << 2 | (bitmapData[i].Blue >> 7) << 3) << 4;
            i++;
            *BufferPtr |= (bitmapData[i].Red >> 6) | (bitmapData[i].Green >> 7) << 2 | (bitmapData[i].Blue >> 7) << 3;
        } else if (BitCount == 8) {
            *BufferPtr = (bitmapData[i].Red >> 5) | (bitmapData[i].Green >> 5) << 3 | (bitmapData[i].Blue >> 5) << 6;
        } else if (BitCount == 16) {
            // Not implemented
        }

        if (IncludePadding) {
            j++;
            if (j >= w) {
                for (unsigned int k = 0; k < (LineWidth - dataBytesPerLine); k++) {
                    BufferPtr += BitCount / 8;
                }
                j = 0;
            }
        }

        BufferPtr++;
    }
    
    Result = true;

    return Result;
}


void BMPImageWriter::write(const RenderedImage* image, OutputStream* output) throw(IOException*) {
    const ColorModel* colorModel = image->getColorModel();
    const RGBA* bitmapData = (RGBA*)image->getRawData();

    int BitCount = colorModel->getBitCount();

    BITMAP_FILEHEADER bfh;
    BITMAP_HEADER bh;

    memset(&bfh, 0, sizeof(bfh));
    memset(&bh, 0, sizeof(bh));

    bfh.Signature = BITMAP_SIGNATURE;
    bfh.BitsOffset = BITMAP_FILEHEADER_SIZE + sizeof(BITMAP_HEADER);
    bfh.Size = (image->getWidth() * image->getHeight() * BitCount) / 8 + bfh.BitsOffset;

    bh.HeaderSize = sizeof(BITMAP_HEADER);
    bh.BitCount = BitCount;
    
    if (BitCount == 32) {
        bh.Compression = 3; // BITFIELD

        bh.AlphaMask = 0xff000000;
        bh.BlueMask = 0x00ff0000;
        bh.GreenMask = 0x0000ff00;
        bh.RedMask = 0x000000ff;
    } else if (BitCount == 16) {
        bh.Compression = 3; // BITFIELD

        bh.AlphaMask = 0x00000000;
        bh.BlueMask = 0x0000001f;
        bh.GreenMask = 0x000007E0;
        bh.RedMask = 0x0000F800;
    } else {
        bh.Compression = 0; // RGB
    }
    
    unsigned int LineWidth = (image->getWidth() + 3) & ~3;

    bh.Planes = 1;
    bh.Height = image->getHeight();
    bh.Width = image->getWidth();
    bh.SizeImage = (LineWidth * BitCount * image->getHeight()) / 8;
    bh.PelsPerMeterX = 3780;
    bh.PelsPerMeterY = 3780;
    
    if (BitCount == 32) {
        output->write((char*) &bfh, sizeof(BITMAP_FILEHEADER));
        output->write((char*) &bh, sizeof(BITMAP_HEADER));
        output->write((char*) bitmapData, bh.SizeImage);
    } else if (BitCount < 16) {
        uint8_t* Bitmap = new uint8_t[bh.SizeImage];
        
        BGRA *Palette = 0;
        unsigned int PaletteSize = 0;

        if (GetBitsWithPalette(image, Bitmap, bh.SizeImage, BitCount, Palette, PaletteSize)) {
            bfh.BitsOffset += PaletteSize * sizeof(BGRA);

            output->write((char*) &bfh, BITMAP_FILEHEADER_SIZE);
            output->write((char*) &bh, sizeof(BITMAP_HEADER));
            output->write((char*) Palette, PaletteSize * sizeof(BGRA));
            output->write((char*) Bitmap, bh.SizeImage);
        }

        delete [] Bitmap;
        delete [] Palette;
    } else {
        uint32_t RedMask = 0;
        uint32_t GreenMask = 0;
        uint32_t BlueMask = 0;
        uint32_t AlphaMask = 0;

        if (BitCount == 16) {
            RedMask = 0x0000F800;
            GreenMask = 0x000007E0;
            BlueMask = 0x0000001F;
            AlphaMask = 0x00000000;
        } else if (BitCount == 24) {
            RedMask = 0x00FF0000;
            GreenMask = 0x0000FF00;
            BlueMask = 0x000000FF;
        } else {
            throw new IOException("other color formats are not valid!");
        }

        if (GetBits(image, NULL, bh.SizeImage, RedMask, GreenMask, BlueMask, AlphaMask)) {
            uint8_t* Bitmap = new uint8_t[bh.SizeImage];

            if (GetBits(image, Bitmap, bh.SizeImage, RedMask, GreenMask, BlueMask, AlphaMask)) {
                output->write((char*) &bfh, sizeof(BITMAP_FILEHEADER));
                output->write((char*) &bh, sizeof(BITMAP_HEADER));
                output->write((char*) Bitmap, bh.SizeImage);
            }

            delete [] Bitmap;
        }
    }
}
