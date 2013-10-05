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

#define TGA_RGB		 2
#define TGA_A		 3
#define TGA_RLE		10

class _DragonExport Texture {
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
	Texture(const char* textureFile);
	virtual ~Texture(void);

public:
	dg_uint getNativeTextureID();

public:
	int width;
	int height;
	dg_byte *data;

	FilterMode filterMode;
	int anisoLevel;
	TextureWrapMode wrapMode;
	float mipMapBias;
	
	int channels;
	dg_uint nativeTextureID;

private:
	bool isInit;
	char* textureFile;
};//Texture

EndPackage4 //(com, dragon3d, scene, model)

#endif //Texture_Model_Scene_Dragon3d_Com_H