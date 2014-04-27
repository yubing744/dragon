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
 * Created:     2014/04/18
 **********************************************************************/


#ifndef Texture_Texture_Scene_Dragon3d_Com_H
#define Texture_Texture_Scene_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragonx/image/BufferedImage.h>
#include <dragon/util/concurrent/atomic/AtomicInteger.h>
#include <com/dragon3d/util/assets/Resource.h>

BeginPackage4(com, dragon3d, scene, texture)

Import dragon::lang;
Import dragonx::image;
Import dragon::util::concurrent::atomic;
Import com::dragon3d::util::assets;


class_ Texture extends(Object) {
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

    void setNativeData(void* data);
    void* getNativeData();
    
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

    void* nativeData;
};//Texture

EndPackage4 //(com, dragon3d, scene, texture)

#endif //Texture_Texture_Scene_Dragon3d_Com_H
