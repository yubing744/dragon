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


#ifndef Material_Model_Scene_Dragon3d_Com_H
#define Material_Model_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/util/Map.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/Float.h>
#include <dragon/lang/String.h>
#include <com/dragon3d/util/Shader.h>
#include <com/dragon3d/util/math/Color.h>
#include <com/dragon3d/util/math/Vector2.h>
#include <com/dragon3d/util/math/Vector4.h>
#include <com/dragon3d/scene/model/Texture.h>

BeginPackage4(com, dragon3d, scene, model)

Import dragon::util;
Import dragon::lang;

Import com::dragon3d::util;
Import com::dragon3d::util::math;
Import com::dragon3d::scene::model;

class _DragonExport Material extends(Object) {
public:
    class TextureProp extends(Object) {
    public:
        TextureProp() :texture(null), 
            textureOffset(Vector2::ZERO), 
            textureScale(Vector2::ONE) {

        };

        virtual ~TextureProp(){
            SafeRelease(this->texture);
        };

    public:
        Texture* texture;
        Vector2 textureOffset;
        Vector2 textureScale;
    };

public:
	Material();
    Material(const String& name);
	Material(const Color& color);
	Material(const Color& color, Texture* mainTexture);

	virtual ~Material(void);

public:
    void setName(const String& name);
    String* getName();

    void setShader(Shader* shader);
    Shader* getShader();

    Color getColor(const String& propName);
    int getInt(const String& propName);
    float getFloat(const String& propName);
    Matrix4x4 getMatrix(const String& propName);
    Texture* getTexture(const String& propName);
    Vector2 getTextureOffset(const String& propName);
    Vector2 getTextureScale(const String& propName);
    Vector4 getVector(const String& propName);

    bool hasProperty(const String& propName);

    void lerp(Material* start, Material* end, float t);

    void setColor(const String& propName, const Color& color);
    void setInt(const String& propName, int val);
    void setFloat(const String& propName, float val);
    void setMatrix(const String& propName, const Matrix4x4& matrix);
    void setTexture(const String& propName, Texture* texture);
    void setTextureOffset(const String& propName, const Vector2& offset);
    void setTextureScale(const String& propName, const Vector2& scale);

protected:
    TextureProp* getTextureProp(const String& propName);

public:
    Color color;
    Texture* mainTexture;
    Vector2 mainTextureOffset;
    Vector2 mainTextureScale;

protected:
	String* name;
    Map<String, Object>* props;

    Shader* shader;
    int renderQueue;
};//Material

EndPackage4 //(com, dragon3d, scene, model)

#endif //Material_Model_Scene_Dragon3d_Com_H