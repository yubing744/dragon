#pragma once

#ifndef DG_TEXTURE
#define DG_TEXTURE

#include "dg_game.h"
#include "dg_log.h"

#define TGA_RGB		 2
#define TGA_A		 3
#define TGA_RLE		10

class DGGraphicsLib;

class DGTexture
{
public:
	enum FilterMode {
		Point,
		Bilinear,
		Trilinear
	};

	enum TextureWrapMode {
		Repeat,
		Clamp
	};

public:
	DGTexture(const char* textureFile);
	virtual ~DGTexture(void);

public:
	void initTexture(DGGraphicsLib* glib);
	DGuint getNativeTextureID();

protected:
	void load(const char* strFileName);
	void loadBMP(const char *strFileName);
	void loadJPG(const char *strFileName);
	void loadTGA(const char *strFileName);

public:
	DGuint width;
	DGuint height;
	DGubyte *data;

	FilterMode filterMode;
	DGuint anisoLevel;
	TextureWrapMode wrapMode;
	DGfloat mipMapBias;
	
	DGuint channels;
	DGuint nativeTextureID;

private:
	DGboolean isInit;

private:
	static DGLog* LOG;
};

#endif