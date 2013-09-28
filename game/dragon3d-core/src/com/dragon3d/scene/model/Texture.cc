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
 * Created:     2013/09/28
 **********************************************************************/


#include <com/dragon3d/scene/model/Texture.h>

Import com::dragon3d::scene::model;

Texture::Texture() {

}

Texture::~Texture() {

}

/*

#include "dg_texture.h"

#include "dg_platform.h"
#include "dg_graphics_lib.h"

//#include "bitmap.h"
//#include "jpeglib.h"
//#pragma comment(lib, "jpeg.lib")

DGLog* DGTexture::LOG = new DGLog("dg_texture");

DGTexture::DGTexture(const char* textureFile){
	this->isInit = DG_FALSE;
	load(textureFile);
}

DGTexture::~DGTexture(void){

}

void DGTexture::load(const char* strFileName) {
	if(!strFileName)  
		return;

	if(strstr(strFileName, ".jpg")){
		loadJPG(strFileName);
	} else if(strstr(strFileName, ".tga")){
		loadTGA(strFileName);
	} else if(strstr(strFileName, ".bmp")){
		loadBMP(strFileName);
	} else {
		return;
	}
}

void DGTexture::loadBMP(const char *strFileName){
	/*
	CBitmap bitmap(strFileName);		
	
	tImage *pImage = (tImage *)malloc(sizeof(tImage));
	
	GLuint pixelLength = bitmap.GetWidth() * bitmap.GetHeight() * 4;
	GLubyte* pixelData = (GLubyte*)malloc(pixelLength);

	bitmap.GetBits(pixelData, pixelLength, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	pImage->channels = 4;
	pImage->sizeX = bitmap.GetWidth();
	pImage->sizeY = bitmap.GetHeight();
	pImage->data  = pixelData;
	*/

	/*
	AUX_RGBImageRec *pBitmap = NULL;
	FILE *pFile = NULL;
	
	if((pFile = fopen(strFileName, "rb")) == NULL){
		LOG->error("Can't load BMP image!");
		return NULL;
	}
	
	pBitmap = auxDIBImageLoad((char*)strFileName);				
	
	tImage *pImage = (tImage *)malloc(sizeof(tImage));
	
	pImage->channels = 3;
	pImage->sizeX = pBitmap->sizeX;
	pImage->sizeY = pBitmap->sizeY;
	pImage->data  = pBitmap->data;
	
	free(pBitmap);

	return pImage;
	*/

/*
}

void DGTexture::loadJPG(const char *strFileName){
	*/
	/*
	struct jpeg_decompress_struct cinfo;
	tImage *pImageData = NULL;
	FILE *pFile;
	
	if((pFile = fopen(strFileName, "rb")) == NULL) 
	{
		MessageBox(NULL, "Can't load JPG image!", "ERROR", MB_OK | MB_ICONINFORMATION);
		return NULL;
	}
	
	jpeg_error_mgr jerr;
	
	cinfo.err = jpeg_std_error(&jerr);
	
	jpeg_create_decompress(&cinfo);
	
	jpeg_stdio_src(&cinfo, pFile);
	
	pImageData = (tImage*)malloc(sizeof(tImage));
	
	
	jpeg_read_header(&cinfo, TRUE);
	
	jpeg_start_decompress(&cinfo);
	
	pImageData->channels = cinfo.num_components;
	pImageData->sizeX    = cinfo.image_width;
	pImageData->sizeY    = cinfo.image_height;
	
	int rowSpan = cinfo.image_width * cinfo.num_components;
	
	pImageData->data = ((unsigned char*)malloc(sizeof(unsigned char)*rowSpan*pImageData->sizeY));
	
	unsigned char** rowPtr = new unsigned char*[pImageData->sizeY];
	
	for (int i = 0; i < pImageData->sizeY; i++)
		rowPtr[i] = &(pImageData->data[i * rowSpan]);
	
	int rowsRead = cinfo.output_height-1;
	while (cinfo.output_scanline < cinfo.output_height) 
	{
		rowsRead -= jpeg_read_scanlines(&cinfo, &rowPtr[rowsRead], cinfo.output_height - rowsRead);
	}

	delete [] rowPtr;
	
	jpeg_finish_decompress(&cinfo);
	
	jpeg_destroy_decompress(&cinfo);
	
	fclose(pFile);

	return pImageData;
	*/
/*
}

void DGTexture::loadTGA(const char *strFileName){
	DGPlatform* platform = DGPlatform::getCurrent();

	DGushort width = 0, height = 0;	
	DGubyte length = 0;				
	DGubyte imageType = 0;					
	DGubyte bits = 0;		
	DGubyte* data = NULL;

	//FILE *pFile = NULL;	
	DGResource* res = NULL;

	int channels = 0;					
	int stride = 0;					
	int i = 0;						
	
	if((res = platform->openResource(strFileName)) == NULL){
		LOG->error("Can't load TGA image!");
		return;
	}

	res->read(&length, sizeof(DGubyte), 1);
	res->seek(1, SEEK_CUR); 
	res->read(&imageType, sizeof(DGubyte), 1);
	
	res->seek(9, SEEK_CUR); 

	res->read(&width,  sizeof(DGushort), 1);
	res->read(&height, sizeof(DGushort), 1);
	res->read(&bits,   sizeof(DGubyte), 1);
	
	res->seek(length + 1, SEEK_CUR); 
	
	if(imageType != TGA_RLE)
	{
		if(bits == 24 || bits == 32)
		{
			channels = bits / 8;
			stride = channels * width;
			data = ((unsigned char*)malloc(sizeof(unsigned char)*stride*height));
			
			for(int y = 0; y < height; y++)
			{
				unsigned char *pLine = &(data[stride * y]);
				
				res->read(pLine, stride, 1);
				
				for(i = 0; i < stride; i += channels)
				{
					int temp     = pLine[i];
					pLine[i]     = pLine[i + 2];
					pLine[i + 2] = temp;
				}
			}
		}
		else if(bits == 16)
		{
			unsigned short pixels = 0;
			int r=0, g=0, b=0;
			
			channels = 3;
			stride = channels * width;
			data = ((unsigned char*)malloc(sizeof(unsigned char)*stride*height));
			
			for(int i = 0; i < width*height; i++)
			{
				res->read(&pixels, sizeof(unsigned short), 1);
				
				b = (pixels & 0x1f) << 3;
				g = ((pixels >> 5) & 0x1f) << 3;
				r = ((pixels >> 10) & 0x1f) << 3;
				
				data[i * 3 + 0] = r;
				data[i * 3 + 1] = g;
				data[i * 3 + 2] = b;
			}
		}	
		else
			return;
	}
	else
	{
		DGubyte rleID = 0;
		int colorsRead = 0;
		channels = bits / 8;
		stride = channels * width;
		
		data = ((unsigned char*)malloc(sizeof(unsigned char)*stride*height));
		DGubyte *pColors = ((DGubyte*)malloc(sizeof(DGubyte)*channels));
		
		while(i < width*height)
		{
			res->read(&rleID, sizeof(DGubyte), 1);
			
			if(rleID < 128)
			{
				rleID++;
				
				while(rleID)
				{
					res->read(pColors, sizeof(DGubyte) * channels, 1);
					
					data[colorsRead + 0] = pColors[2];
					data[colorsRead + 1] = pColors[1];
					data[colorsRead + 2] = pColors[0];
					
					if(bits == 32)
						data[colorsRead + 3] = pColors[3];
					
					i++;
					rleID--;
					colorsRead += channels;
				}
			}
			else
			{
				rleID -= 127;
				
				res->read(pColors, sizeof(DGubyte) * channels, 1);
				
				while(rleID)
				{
					data[colorsRead + 0] = pColors[2];
					data[colorsRead + 1] = pColors[1];
					data[colorsRead + 2] = pColors[0];
					
					if(bits == 32)
						data[colorsRead + 3] = pColors[3];
					
					i++;
					rleID--;
					colorsRead += channels;
				}
			}
		}
	}

	platform->closeResource(res);
	
	this->channels = channels;
	this->width = width;
	this->height = height;
	this->data = data;
}

DGuint DGTexture::getNativeTextureID(){
	return this->nativeTextureID;
}


void DGTexture::initTexture(DGGraphicsLib* glib){
	if (glib && !this->isInit) {
		glib->initTexture(this);
		this->isInit = DG_TRUE;
	}
}

 */