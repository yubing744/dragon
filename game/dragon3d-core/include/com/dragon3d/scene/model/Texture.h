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
#include <dragon/lang/Object.h>
#include <dragonx/image/BufferedImage.h>
#include <com/dragon3d/scene/model/shader/Shader.h>
#include <dragon/util/concurrent/atomic/AtomicInteger.h>
#include <com/dragon3d/util/assets/Resource.h>

BeginPackage4(com, dragon3d, scene, model)

Import dragon::lang;
Import dragonx::image;
Import com::dragon3d::scene::model;
Import com::dragon3d::scene::model::shader;
Import dragon::util::concurrent::atomic;
Import com::dragon3d::util::assets;

class _DragonExport Texture extends(Object) {
private:
	static AtomicInteger* sequence;

public:
	static int GetNextTextureID();

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
	Texture(Resource* res);
	Texture(const String& resPath);
	virtual ~Texture(void);

public:
	unsigned int getID();

public:
	int getWidth();
	int getHeight();
	Array<byte> getData();

public:
	FilterMode filterMode;
	int anisoLevel;
	TextureWrapMode wrapMode;
	float mipMapBias;
	
	int channels;

private:
	unsigned int id;
	BufferedImage* image;
};//Texture

EndPackage4 //(com, dragon3d, scene, model)

#endif //Texture_Model_Scene_Dragon3d_Com_H