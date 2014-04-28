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

#include <dragon/util/Scanner.h>

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>

#include <dragon/io/StringReader.h>

#include <com/dragon3d/output/graphics/shader/glsl/GLSLShader.h>
#include <com/dragon3d/output/graphics/shader/glsl/GLSLShaderCompiler.h>
#include <com/dragon3d/output/graphics/shader/ShaderManager.h>

Import dragon::io;
Import dragon::util;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::output::graphics::shader;
Import com::dragon3d::output::graphics::shader::glsl;

const Type* GLSLShaderCompiler::TYPE = TypeOf<GLSLShaderCompiler>();
static Logger* logger = Logger::getLogger(GLSLShaderCompiler::TYPE, INFO);

Shader* GLSLShaderCompiler::compile(ShaderSource* source) throw(ShaderException*) {
    GLSLShader* shader = new GLSLShader();

    shader->init();

    if (this->loadProgram(shader, source)) {
        Ref<String> name = source->getName();
        shader->setName(name);

        this->parseAndSetNameMapping(source, shader);

        shader->prepare();

        return shader;
    } else {
        throw new ShaderException("error in compile shader!");
    }
}

void GLSLShaderCompiler::parseAndSetNameMapping(ShaderSource* source, GLSLShader* shader) {
    Ref<String> code = source->getCode();
    Ref<StringReader> reader = new StringReader(code);
    Ref<Scanner> scanner = new Scanner(reader);

    this->parseShaderNameMapping(scanner, "//program main_vertex", shader);   
    this->parseShaderNameMapping(scanner, "//program main_fragment", shader); 
}

void GLSLShaderCompiler::parseShaderNameMapping(Scanner* scanner, const String& startPattern, GLSLShader* shader) {
    // read vertext shader map
    scanner->skip(startPattern);
    scanner->useDelimiter("\n");

    while(scanner->hasNext()) {
        Ref<String> token = scanner->next();

        if (token->startsWith("//semantic")) {
            continue;
        }

        if (token->startsWith("//var")) {
            if (logger->isDebugEnabled()) {
                logger->debug("the token:" + token);
            }

            this->parseTokenNameMapping(token, shader);

            continue;
        }
        
        break;
    }
}

void GLSLShaderCompiler::parseTokenNameMapping(String* line, GLSLShader* shader) {
    Array<String*> tokens = line->split(":");

    Ref<String> varToken = tokens[0];
    Ref<String> semantic = tokens[1];
    Ref<String> name = tokens[2];

    if (logger->isDebugEnabled()) {
        logger->debug("varToken:" + varToken);
        logger->debug("semantic:" + semantic);
        logger->debug("name:" + name);
    }

    Array<String*> varTokens = varToken->split(" ");
    Ref<String> key = varTokens[2];

    Array<String*> nameTokens = name->split(",");

    if (nameTokens.size()>0 && !semantic->contains("$vout")) {
        Ref<String> theName = nameTokens[0];
        theName = theName->replaceAll("\\[\\d\\]", " ");
        theName = theName->trim();

        if (logger->isDebugEnabled()) {
            logger->debug("mapping key:" + key);
            logger->debug("mapping val:" + theName);
        }

        shader->registerNameMapping(key, theName);
    }
}

