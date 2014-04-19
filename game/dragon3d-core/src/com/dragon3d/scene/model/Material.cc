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

#include <dragon/util/TreeMap.h>
#include <com/dragon3d/scene/model/Material.h>

Import dragon::util;
Import com::dragon3d::scene::model;

Material::Material() :name(null),
    color(Color::WHITE), 
    mainTexture(null), 
    mainTextureOffset(Vector2::ZERO), 
    mainTextureScale(Vector2::ONE),
    shader(null) {
    this->props = new TreeMap<String, Object>();
}

Material::Material(const String& name) :name(new String(name)),
    color(Color::WHITE), 
    mainTexture(null), 
    mainTextureOffset(Vector2::ZERO), 
    mainTextureScale(Vector2::ONE),
    shader(null) {
    this->props = new TreeMap<String, Object>();
}

Material::Material(const Color& color) :name(null),
    color(color), 
    mainTexture(null), 
    mainTextureOffset(Vector2::ZERO), 
    mainTextureScale(Vector2::ONE),
    shader(null) {
    this->props = new TreeMap<String, Object>();
}

Material::Material(const Color& color, Texture* mainTexture) :name(null), 
    color(color), 
    mainTexture(mainTexture), 
    mainTextureOffset(Vector2::ZERO), 
    mainTextureScale(Vector2::ONE),
    shader(null){
    this->mainTexture->retain();
    this->props = new TreeMap<String, Object>();
}

Material::~Material(void){
    SafeRelease(this->mainTexture);
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

    if (prop != null) {
        ret = prop->textureOffset;
    } 

    SafeRelease(prop);

    return ret;
}

Vector2 Material::getTextureScale(const String& propName) {
    Vector2 ret = Vector2::ZERO;

    TextureProp* prop = (TextureProp*)this->props->get(propName);

    if (prop != null) {
        ret = prop->textureScale;
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
    prop->textureOffset = offset;
    SafeRelease(prop);
}

void Material::setTextureScale(const String& propName, const Vector2& scale) {
    TextureProp* prop = this->getTextureProp(propName);
    prop->textureScale = scale;
    SafeRelease(prop);
}
