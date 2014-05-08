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

#include <dragon/lang/System.h>

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>

#include <dragon/util/TreeMap.h>
#include <com/dragon3d/scene/model/Material.h>

Import dragon::lang::gc;

Import dragon::util;
Import dragon::util::logging;

Import com::dragon3d::scene::model;

const Type* Material::TYPE = TypeOf<Material>();
const Type* Material::TextureProp::TYPE = TypeOf<Material::TextureProp>();

static Logger* logger = Logger::getLogger(Material::TYPE, LOG_LEVEL_DEBUG);


Material::Material() :name(null),
    shader(null) {
    this->props = new TreeMap<String, Object>();
}

Material::Material(const String& name) :name(new String(name)),
    shader(null) {
    this->props = new TreeMap<String, Object>();
}

Material::Material(const Color& color) :name(null),
    shader(null) {
    this->props = new TreeMap<String, Object>();
    this->setMainColor(color);
}

Material::Material(const Color& color, Texture* mainTexture) :name(null), 
    shader(null){
    this->props = new TreeMap<String, Object>();
    this->setMainTexture(mainTexture);
}

Material::~Material(void){
    SafeRelease(this->props);
}

void Material::setName(const String& name) {
    SafeRelease(this->name);
    this->name = new String(name);
}

String* Material::getName() {
    String* ret = this->name;
    ret->retain();
    return ret;
}

void Material::setShader(Shader* shader) {
    SafeRelease(this->shader);
    this->shader = shader;
}

Shader* Material::getShader() {
    Shader* shader = this->shader;
    SafeRetain(shader);
    return shader;
}

Color Material::getColor(const String& propName) {
    Color ret = Color::BLACK;

    Color* prop = (Color*)this->props->get(propName);

    if (prop != null) {
        ret = *prop;
        SafeRelease(prop);
    }

    return ret;
}

float Material::getFloat(const String& propName) {
    float ret = 0.0f;

    Float* prop = (Float*)this->props->get(propName);
    
    if (prop != null) {
        ret = prop->floatValue();
        SafeRelease(prop);
    }

    return ret;
}

int Material::getInt(const String& propName) {
    int ret = 0;

    Integer* prop = (Integer*)this->props->get(propName);
    
    if (prop != null) {
        ret = prop->intValue();
        SafeRelease(prop);
    }

    return ret;
}

Matrix4x4 Material::getMatrix(const String& propName) {
    Matrix4x4 ret = Matrix4x4::IDENTITY;

    Matrix4x4* prop = (Matrix4x4*)this->props->get(propName);
    
    if (prop != null) {
        ret = *prop;
        SafeRelease(prop);
    }

    return ret;
}

Texture* Material::getTexture(const String& propName) {
    Texture* ret = null;

    TextureProp* prop = (TextureProp*)this->props->get(propName);

    if (prop != null && prop->texture!=null) {
        ret = prop->texture;
        ret->retain();
    } 

    SafeRelease(prop);

    return ret;
}

Vector2 Material::getTextureOffset(const String& propName) {
    Vector2 ret = Vector2::ZERO;

    TextureProp* prop = (TextureProp*)this->props->get(propName);

    if (prop != null && prop->textureOffset!=null) {
        ret = *prop->textureOffset;
    } 

    SafeRelease(prop);

    return ret;
}

Vector2 Material::getTextureTiling(const String& propName) {
    Vector2 ret = Vector2::ZERO;

    TextureProp* prop = (TextureProp*)this->props->get(propName);

    if (prop != null && prop->textureTiling!=null) {
        ret = *prop->textureTiling;
    } 

    SafeRelease(prop);

    return ret;
}

Vector4 Material::getVector(const String& propName) {
    Vector4 ret = Vector4::ZERO;

    Vector4* prop = (Vector4*)this->props->get(propName);
    
    if (prop != null) {
        ret = *prop;
        SafeRelease(prop);
    }

    return ret;
}

bool Material::hasProperty(const String& propName) {
    return this->props->containsKey(propName);
}

void Material::lerp(Material* start, Material* end, float t) {

}

void Material::setColor(const String& propName, const Color& color) {
    Color* prop = (Color*)this->props->get(propName);

    if (prop == null) {
        prop = new Color(color);
        this->props->put(propName, prop);
    } else {
        *prop = color;
    }

    SafeRelease(prop);
}

void Material::setInt(const String& propName, int val) {
    Integer* prop = (Integer*)this->props->get(propName);

    if (prop != null) {
        SafeRelease(prop);
    }

    prop = new Integer(val);
    this->props->put(propName, prop);

    SafeRelease(prop);
}

void Material::setFloat(const String& propName, float val) {
    Float* prop = (Float*)this->props->get(propName);

    if (prop != null) {
        SafeRelease(prop);
    }

    prop = new Float(val);
    this->props->put(propName, prop);

    SafeRelease(prop);
}

void Material::setMatrix(const String& propName, const Matrix4x4& matrix) {
    Matrix4x4* prop = (Matrix4x4*)this->props->get(propName);

    if (prop == null) {
        prop = new Matrix4x4(matrix);
        this->props->put(propName, prop);
    } else {
        *prop = matrix;
    }

    SafeRelease(prop);
}

Material::TextureProp* Material::getTextureProp(const String& propName) {
    Material::TextureProp* prop = (Material::TextureProp*)this->props->get(propName);

    if (prop == null) {
        prop = new Material::TextureProp();
        this->props->put(propName, prop);
    } 

    return prop;
}

void Material::setTexture(const String& propName, Texture* texture) {
    TextureProp* prop = this->getTextureProp(propName);

    SafeRelease(prop->texture);
    texture->retain();
    prop->texture = texture;

    SafeRelease(prop);
}

void Material::setTextureOffset(const String& propName, const Vector2& offset) {
    TextureProp* prop = this->getTextureProp(propName);
    prop->textureOffset = new Vector2(offset);
    SafeRelease(prop);
}

void Material::setTextureTiling(const String& propName, const Vector2& tiling) {
    TextureProp* prop = this->getTextureProp(propName);
    prop->textureTiling = new Vector2(tiling);
    SafeRelease(prop);
}

void Material::setMainColor(const Color& color) {
    this->setColor("color", color);
}

Color Material::getMainColor() {
    return this->getColor("color");
}

Texture* Material::getMainTexture() {
    return this->getTexture("mainTex");
}

void Material::setMainTexture(Texture* texture) {
    this->setTexture("mainTex", texture);
}

Vector2 Material::getMainTextureOffset() {
    return this->getTextureOffset("mainTex");
}

Vector2 Material::getMainTextureTiling() {
    return this->getTextureTiling("mainTex");
}

void Material::setMainTextureOffset(const Vector2& offset) {
    this->setTextureOffset("mainTex", offset);
}

void Material::setMainTextureTiling(const Vector2& tiling) {
    this->setTextureTiling("mainTex", tiling);
}

void Material::renderUntoShader(Shader* shader) {
    Ref<Iterator<Map<String, Object>::Entry> > it = this->props->iterator();

    while(it->hasNext()) {
        Ref<Map<String, Object>::Entry> entry = it->next();
        String name = entry->getKey();
        Ref<Object> obj = entry->getValue();

        if (logger->isDebugEnabled()) {
            logger->debug("set matrial prop:" + name);
        }

        this->renderPropUnto(name, obj, shader);
    }
}

void Material::renderPropUnto(const String& name, Object* obj, Shader* shader) {
    if (obj != null) {
        const Array<char> utf8Name = name->toUTF8CharArray();
        const Type* clazz = (const Type*)obj->getClass();

        // int
        if (Integer::TYPE->equals(clazz)) {
            Integer* val = (Integer*)obj;
            shader->setInt(utf8Name, val->intValue());
        } 

        // float
        else if (Float::TYPE->equals(clazz)) {
            Float* val = (Float*)obj;
            shader->setFloat(utf8Name, val->floatValue());
        } 

        // color
        else if (Color::TYPE->equals(clazz)) {
            Color* val = (Color*)obj;
            shader->setFloatVector(utf8Name, 4, Array<float>(val->getData(), 4, false));
        }

        // vector
        else if (Vector4::TYPE->equals(clazz)) {
            Vector4* val = (Vector4*)obj;
            shader->setFloatVector(utf8Name, 4, Array<float>(val->getData(), 4, false));
        }

        // matrix
        else if (Matrix4x4::TYPE->equals(clazz)) {
            Matrix4x4* val = (Matrix4x4*)obj;
            shader->setMatrix(utf8Name, *val);
        }

        // texture
        else if (Material::TextureProp::TYPE->equals(clazz)) {
            Material::TextureProp* val = (Material::TextureProp*)obj;

            Texture* texture = val->texture;
            Vector2* textureOffset = val->textureOffset;
            Vector2* textureTiling = val->textureTiling;

            if (texture != null) {
                shader->setSampler(utf8Name, texture, 0);
            }

            if (textureOffset != null) {
                Ref<String> offsetName = name.concat("Offset");
                const Array<char> utf8OffsetName = offsetName->toUTF8CharArray();
                shader->setFloatVector(utf8OffsetName, 2, Array<float>(textureOffset->getData(), 2, false));
            }

            if (textureTiling != null) {
                Ref<String> tilingName = name.concat("Tiling");
                const Array<char> utf8TilingName = tilingName->toUTF8CharArray();
                shader->setFloatVector(utf8TilingName, 2, Array<float>(textureTiling->getData(), 2, false));
            }
        }
    }
}
