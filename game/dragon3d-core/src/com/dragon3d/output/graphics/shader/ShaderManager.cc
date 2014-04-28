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
 * Created:     2014/04/23
 **********************************************************************/


#include <dragon/lang/gc/Reference.h>

#include <dragon/lang/String.h>
#include <dragon/util/HashMap.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/framework/GameException.h>

#include <com/dragon3d/output/graphics/shader/Shader.h>
#include <com/dragon3d/output/graphics/shader/ShaderSource.h>
#include <com/dragon3d/output/graphics/shader/ShaderCompiler.h>
#include <com/dragon3d/output/graphics/shader/ShaderException.h>
#include <com/dragon3d/output/graphics/shader/ShaderManager.h>

#include <com/dragon3d/util/assets/AssetsManager.h>
#include <com/dragon3d/util/assets/ResourceUtils.h>
#include <com/dragon3d/util/assets/ResourceNotFoundException.h>

Import dragon::lang::gc;

Import dragon::lang;
Import dragon::util;
Import dragon::util::logging;

Import com::dragon3d::framework;
Import com::dragon3d::util;
Import com::dragon3d::util::assets;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::shader;

const Type* ShaderManager::TYPE = TypeOf<ShaderManager>();
static Logger* logger = Logger::getLogger(ShaderManager::TYPE, LOG_LEVEL_DEBUG);
AtomicInteger* ShaderManager::sequence = new AtomicInteger(0);


ShaderManager* ShaderManager::instance = null;

ShaderManager* ShaderManager::getInstance() {
    if (instance == null) {
        instance = new ShaderManager();
    }

    return instance;
}

int ShaderManager::GetNextShaderID() {
    return sequence->incrementAndGet();
}

ShaderManager::ShaderManager() {
    this->shaders = new HashMap<Integer, Shader>();
    this->compilers = new HashMap<String, ShaderCompiler>();
}

ShaderManager::~ShaderManager() {
    SafeRelease(this->shaders);
    SafeRelease(this->compilers);
}

void ShaderManager::init() {

}

Shader* ShaderManager::getShader(int shaderID) {
    Integer theID(shaderID);
    return this->shaders->get(theID);
}

Shader* ShaderManager::getShader(const String& name) {
    Ref<Iterator<Map<Integer, Shader>::Entry> > it = this->shaders->iterator();

    while(it->hasNext()) {
        Ref<Map<Integer, Shader>::Entry> entry = it->next();

        Ref<Shader> shader = entry->getValue();
        Ref<String> shaderName = shader->getName();

        if (shaderName->equals(name)) {
            return shader.retain();
        }
    }

    return null; 
}

void ShaderManager::registerShader(const String& name, ShaderType type, String* code) {
    String strShaderType = ShaderTypeToString(type);
    Ref<ShaderCompiler> compiler = this->compilers->get(strShaderType);

    if (compiler != null) {
        Ref<ShaderSource> source = new ShaderSource(name, type, code);

        Ref<Shader> shader = compiler->compile(source);

        this->shaders->put(shader->getID(), shader);
    } else {
        throw new ShaderException("not support compiler shader with type" + type);
    }
}

void ShaderManager::registerShaderCompiler(ShaderType type, ShaderCompiler* compiler) {
    const String& strShaderType = ShaderTypeToString(type);
    this->compilers->put(strShaderType, compiler);
}


void ShaderManager::importShader(Resource* shaderRes) {
    if (shaderRes->exists()) {
        Ref<String> shaderPath = shaderRes->getPath();

        if (logger->isDebugEnabled()) {
            logger->debug("import shader:" + shaderPath);
        }

        Ref<String> name = shaderRes->getName();
        Ref<String> strType = shaderRes->getType();
        ShaderType type = ShaderTypeFromString(strType);
        Ref<String> code = ResourceUtils::readResourceToString(shaderRes, "UTF-8");
        
        if (logger->isDebugEnabled()) {
            logger->debug("shader name:" + name);
            logger->debug("shader type:" + strType);
            logger->debug("shader code:\n" + code);
        }
    
        if (this->supportShaderType(strType)) {
            this->registerShader(name, type, code);
        }
    } else {
        Ref<String> msg = String::format("not found shader with path: %s", shaderRes->getPath());
        throw new ResourceNotFoundException(msg);
    }
}

void ShaderManager::importShader(const String& shaderPath) {
    Ref<Resource> res = AssetsManager::getInstance()->getResource(shaderPath);
    this->importShader(res);
}

void ShaderManager::importShaders(const String& shaderDirPath) {
    Ref<List<Resource> > shaderPaths = AssetsManager::getInstance()->getResources(shaderDirPath, true);

    Ref<Iterator<Resource> > it = shaderPaths->iterator();

    while(it->hasNext()) {
        Ref<Resource> shaderRes = it->next();
        this->importShader(shaderRes);
    }
}

bool ShaderManager::supportShaderType(const String& type) {
    Ref<ShaderCompiler> compiler = this->compilers->get(type);
    return compiler != null;
}