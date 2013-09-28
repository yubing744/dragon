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


#ifndef Texture_Model_Scene_Dragon3d_Com_H
#define Texture_Model_Scene_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, scene, model)

Import com::dragon3d::scene::model;

class _DragonExport Texture {
public:
	Texture();
	virtual ~Texture();

public:
	
protected:
	
};//Texture

EndPackage4 //(com, dragon3d, scene, model)

#endif //Texture_Model_Scene_Dragon3d_Com_H
/*

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