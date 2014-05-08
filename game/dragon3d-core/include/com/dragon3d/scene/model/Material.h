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
#include <com/dragon3d/util/math/Color.h>
#include <com/dragon3d/util/math/Vector2.h>
#include <com/dragon3d/util/math/Vector4.h>
#include <com/dragon3d/scene/texture/Texture.h>
#include <com/dragon3d/output/graphics/shader/Shader.h>

BeginPackage4(com, dragon3d, scene, model)

Import dragon::util;
Import dragon::lang;

Import com::dragon3d::util;
Import com::dragon3d::util::math;
Import com::dragon3d::scene::texture;
Import com::dragon3d::output::graphics::shader;

class _DragonExport Material extends(Object) {
public:
    static const Type* TYPE;

public:
    class TextureProp extends(Object) {
    public:
        static const Type* TYPE;

    public:
        TextureProp() :texture(null), 
            textureOffset(null), 
            textureTiling(null) {
            this->textureOffset = new Vector2(0, 0);
            this->textureTiling = new Vector2(1, 1);
        };

        virtual ~TextureProp(){
            SafeRelease(this->texture);
            SafeRelease(this->textureOffset);
            SafeRelease(this->textureTiling);
        };

    public:
        Texture* texture;
        Vector2* textureOffset;
        Vector2* textureTiling;
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
    Vector2 getTextureTiling(const String& propName);
    Vector4 getVector(const String& propName);

    bool hasProperty(const String& propName);

    void lerp(Material* start, Material* end, float t);

    void setColor(const String& propName, const Color& color);
    void setInt(const String& propName, int val);
    void setFloat(const String& propName, float val);
    void setMatrix(const String& propName, const Matrix4x4& matrix);
    void setTexture(const String& propName, Texture* texture);
    void setTextureOffset(const String& propName, const Vector2& offset);
    void setTextureTiling(const String& propName, const Vector2& tiling);

    void renderUntoShader(Shader* shader);

public:
    void setMainColor(const Color& color);
    Color getMainColor();

    Texture* getMainTexture();
    Vector2 getMainTextureOffset();
    Vector2 getMainTextureTiling();
    
    void setMainTexture(Texture* texture);
    void setMainTextureOffset(const Vector2& offset);
    void setMainTextureTiling(const Vector2& tiling);

protected:
    TextureProp* getTextureProp(const String& propName);
    void renderPropUnto(const String& name, Object* obj, Shader* shader);

protected:
	String* name;
    Map<String, Object>* props;

    Shader* shader;
    int renderQueue;
};//Material

EndPackage4 //(com, dragon3d, scene, model)

#endif //Material_Model_Scene_Dragon3d_Com_H