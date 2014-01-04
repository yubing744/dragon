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

#include <dragonx/image/io/plugins/bmp/BMPImageReader.h>
#include <dragon/util/logging/Logger.h>

Import dragonx::image::io::plugins::bmp;
Import dragon::util::logging;

const Type* BMPImageReader::TYPE = TypeOf<BMPImageReader>();
static Logger* logger = Logger::getLogger(BMPImageReader::TYPE, ERROR);

BMPImageReader::BMPImageReader() {

}

BMPImageReader::~BMPImageReader() {

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
} BITMAP_HEADER;

typedef struct _BITMAP_HEADER_EXT {
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t AlphaMask;
    uint32_t CsType;
    uint32_t Endpoints[9]; // see http://msdn2.microsoft.com/en-us/library/ms536569.aspx
    uint32_t GammaRed;
    uint32_t GammaGreen;
    uint32_t GammaBlue;
} BITMAP_HEADER_EXT;

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

BufferedImage* BMPImageReader::read(InputStream* input) throw(IOException*) {
    BufferedImage* image = null;
    
    BITMAP_FILEHEADER bitmapFileHeader;
    BITMAP_HEADER bitmapHeader;
    BITMAP_HEADER_EXT bitmapHeaderExt;
    BGRA* colorTable = null;
    
    unsigned int bitmapSize;
    unsigned int readCount = 0;

    RGBA *bitmapData;

    input->read((char*) &bitmapFileHeader, BITMAP_FILEHEADER_SIZE);

    if (bitmapFileHeader.Signature != BITMAP_SIGNATURE) {
        throw new IOException("not bitmap!");
    }

    input->read((char*)&bitmapHeader, sizeof(BITMAP_HEADER));
    readCount += sizeof(BITMAP_HEADER);

    /* Load Color Table */
    unsigned int colorTableSize = 0;

    if (bitmapHeader.BitCount == 1) {
        colorTableSize = 2;
    } else if (bitmapHeader.BitCount == 4) {
        colorTableSize = 16;
    } else if (bitmapHeader.BitCount == 8) {
        colorTableSize = 256;
    }
    
    // Always allocate full sized color table
    if (bitmapHeader.Compression < 3) {
        colorTable = new BGRA[colorTableSize]; // std::bad_alloc exception should be thrown if memory is not available
    
        int colorTableOffset = BITMAP_FILEHEADER_SIZE + bitmapHeader.HeaderSize;
        input->skip(colorTableOffset - readCount);
        readCount = colorTableOffset;

        input->read((char*)colorTable, sizeof(BGRA) * colorTableSize);
        readCount += sizeof(BGRA) * colorTableSize;
    } else {
        input->read((char*)&bitmapHeaderExt, sizeof(BITMAP_HEADER_EXT));
        readCount += sizeof(BITMAP_HEADER_EXT);
    }

    /* Color Table for 16 bits images are not supported yet */  
    int imageWidth = bitmapHeader.Width < 0 ? -bitmapHeader.Width : bitmapHeader.Width;
    int imageHeight = bitmapHeader.Height < 0 ? -bitmapHeader.Height : bitmapHeader.Height;
    int imageBitCount = bitmapHeader.BitCount;

    image = new BufferedImage(imageWidth, imageHeight, ColorModel::TYPE_32_RGBA);

    bitmapSize = imageWidth * imageHeight;
    bitmapData = (RGBA*)image->getRawData();
    
    unsigned int lineWidth = ((imageWidth * imageBitCount / 8) + 3) & ~3;
    uint8_t* line = new uint8_t[lineWidth];
    
    input->skip(bitmapFileHeader.BitsOffset - readCount);
    readCount = bitmapFileHeader.BitsOffset;

    int index = 0;
    bool result = true;

    if (bitmapHeader.Compression == 0) {
        for (unsigned int i = 0; i < imageHeight; i++) {
            input->read((char*)line, lineWidth);

            uint8_t *linePtr = line;
            
            for (unsigned int j = 0; j < imageWidth; j++) {
                if (bitmapHeader.BitCount == 1) {
                    uint32_t color = *((uint8_t*) linePtr);

                    for (int k = 0; k < 8; k++) {
                        bitmapData[index].Red = colorTable[color & 0x80 ? 1 : 0].Red;
                        bitmapData[index].Green = colorTable[color & 0x80 ? 1 : 0].Green;
                        bitmapData[index].Blue = colorTable[color & 0x80 ? 1 : 0].Blue;
                        bitmapData[index].Alpha = colorTable[color & 0x80 ? 1 : 0].Alpha;

                        index++;
                        color <<= 1;
                    }

                    linePtr++;
                    j += 7;
                } else if (bitmapHeader.BitCount == 4) {
                    uint32_t color = *((uint8_t*) linePtr);

                    bitmapData[index].Red = colorTable[(color >> 4) & 0x0f].Red;
                    bitmapData[index].Green = colorTable[(color >> 4) & 0x0f].Green;
                    bitmapData[index].Blue = colorTable[(color >> 4) & 0x0f].Blue;
                    bitmapData[index].Alpha = colorTable[(color >> 4) & 0x0f].Alpha;
                    index++;

                    bitmapData[index].Red = colorTable[color & 0x0f].Red;
                    bitmapData[index].Green = colorTable[color & 0x0f].Green;
                    bitmapData[index].Blue = colorTable[color & 0x0f].Blue;
                    bitmapData[index].Alpha = colorTable[color & 0x0f].Alpha;
                    index++;

                    linePtr++;
                    j++;
                } else if (bitmapHeader.BitCount == 8) {
                    uint32_t color = *((uint8_t*) linePtr);

                    bitmapData[index].Red = colorTable[color].Red;
                    bitmapData[index].Green = colorTable[color].Green;
                    bitmapData[index].Blue = colorTable[color].Blue;
                    bitmapData[index].Alpha = colorTable[color].Alpha;
                    index++;

                    linePtr++;
                } else if (bitmapHeader.BitCount == 16) {
                    uint32_t color = *((uint16_t*) linePtr);

                    bitmapData[index].Red = ((color >> 10) & 0x1f) << 3;
                    bitmapData[index].Green = ((color >> 5) & 0x1f) << 3;
                    bitmapData[index].Blue = (color & 0x1f) << 3;
                    bitmapData[index].Alpha = 255;

                    index++;
                    linePtr += 2;
                } else if (bitmapHeader.BitCount == 24) {
                    uint32_t color = *((uint32_t*) linePtr);

                    bitmapData[index].Blue = color & 0xff;
                    bitmapData[index].Green = (color >> 8) & 0xff;
                    bitmapData[index].Red = (color >> 16) & 0xff;
                    bitmapData[index].Alpha = 255;

                    index++;
                    linePtr += 3;
                } else if (bitmapHeader.BitCount == 32) {
                    uint32_t color = *((uint32_t*) linePtr);

                    bitmapData[index].Blue = color & 0xff;
                    bitmapData[index].Green = (color >> 8) & 0xff;
                    bitmapData[index].Red = (color >> 16) & 0xff;
                    bitmapData[index].Alpha = color >> 24;

                    index++;
                    linePtr += 4;
                }
            }
        }
    } else if (bitmapHeader.Compression == 1) { // RLE 8
        uint8_t count = 0;
        uint8_t colorIndex = 0;
        int x = 0, y = 0;

        int readCount = 1;

        while (readCount > 0) {
            input->read((char*) &count, sizeof(uint8_t));
            input->read((char*) &colorIndex, sizeof(uint8_t));

            if (count > 0) {
                index = x + y * imageWidth;

                for (int k = 0; k < count; k++) {
                    bitmapData[index + k].Red = colorTable[colorIndex].Red;
                    bitmapData[index + k].Green = colorTable[colorIndex].Green;
                    bitmapData[index + k].Blue = colorTable[colorIndex].Blue;
                    bitmapData[index + k].Alpha = colorTable[colorIndex].Alpha;
                }

                x += count;
            } else if (count == 0) {
                int flag = colorIndex;

                if (flag == 0) {
                    x = 0;
                    y++;
                } else if (flag == 1) {
                    break;
                } else if (flag == 2) {
                    char rx = 0;
                    char ry = 0;

                    input->read((char*) &rx, sizeof(char));
                    input->read((char*) &ry, sizeof(char));

                    x += rx;
                    y += ry;
                } else {
                    count = flag;
                    index = x + y * imageWidth;

                    for (int k = 0; k < count; k++) {
                        input->read((char*) &colorIndex, sizeof(uint8_t));

                        bitmapData[index + k].Red = colorTable[colorIndex].Red;
                        bitmapData[index + k].Green = colorTable[colorIndex].Green;
                        bitmapData[index + k].Blue = colorTable[colorIndex].Blue;
                        bitmapData[index + k].Alpha = colorTable[colorIndex].Alpha;
                    }

                    x += count;

                    // Attention: Current Microsoft STL implementation seems to be buggy, tellg() always returns 0.
                    //if (file.tellg() & 1) {
                    //    file.seekg(1, std::ios::cur);
                    //}
                }
            }
        }
    } else if (bitmapHeader.Compression == 2) { // RLE 4
        throw new IOException("not support compression bmp!");
    } else if (bitmapHeader.Compression == 3) { // BITFIELDS
        /* We assumes that mask of each color component can be in any order */

        uint32_t bitCountRed = CColor::BitCountByMask(bitmapHeaderExt.RedMask);
        uint32_t bitCountGreen = CColor::BitCountByMask(bitmapHeaderExt.GreenMask);
        uint32_t bitCountBlue = CColor::BitCountByMask(bitmapHeaderExt.BlueMask);
        uint32_t bitCountAlpha = CColor::BitCountByMask(bitmapHeaderExt.AlphaMask);

        for (unsigned int i = 0; i < imageHeight; i++) {
            input->read((char*)line, lineWidth);
            
            uint8_t *linePtr = line;
            
            for (unsigned int j = 0; j < imageWidth; j++) {
                uint32_t color = 0;

                if (bitmapHeader.BitCount == 16) {
                    color = *((uint16_t*) linePtr);
                    linePtr += 2;
                } else if (bitmapHeader.BitCount == 32) {
                    color = *((uint32_t*) linePtr);
                    linePtr += 4;
                } else {
                    // Other formats are not valid
                }

                bitmapData[index].Red = CColor::Convert(CColor::ComponentByMask(color, bitmapHeaderExt.RedMask), bitCountRed, 8);
                bitmapData[index].Green = CColor::Convert(CColor::ComponentByMask(color, bitmapHeaderExt.GreenMask), bitCountGreen, 8);
                bitmapData[index].Blue = CColor::Convert(CColor::ComponentByMask(color, bitmapHeaderExt.BlueMask), bitCountBlue, 8);
                bitmapData[index].Alpha = CColor::Convert(CColor::ComponentByMask(color, bitmapHeaderExt.AlphaMask), bitCountAlpha, 8);

                index++;
            }
        }
    }
    
    delete[] colorTable;
    delete[] line;

    return image;
}
