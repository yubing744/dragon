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
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/shader/glsl/GLSLShader.h>
#include <com/dragon3d/output/graphics/shader/glsl/GLSLShaderCompiler.h>
#include <com/dragon3d/output/graphics/shader/ShaderManager.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::output::graphics::shader;
Import com::dragon3d::output::graphics::shader::glsl;

static Logger* logger = Logger::getLogger("GLSLShaderCompiler#shared", INFO);

GLSLShaderCompiler::GLSLShaderCompiler() {

}

GLSLShaderCompiler::~GLSLShaderCompiler() {

}

//
///
/// \brief Load a shader, check for compile errors, print error messages to output log
/// \param type Type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
/// \param shaderSrc Shader source string
/// \return A new shader object on success, 0 on failure
//
unsigned int GLSLShaderCompiler::loadShader(int type, const char *define, const char *program) {
   GLuint shader;
   GLint compiled;
   
   //GLenum glType = (type==GLSL_VERTEX_SHADER)?GL_VERTEX_SHADER:GL_FRAGMENT_SHADER;
   GLenum glType = (GLenum)type;

   // Create the shader object
   shader = glCreateShader(glType);

   if (shader == 0)
    return 0;

   logger->debug("shader code: %s", program);

   // Load the shader source
   char version[32] = {0};

   const char *source[] = { version, define, program };

   glShaderSource(shader, 3, source, NULL);
   
   // Compile the shader
   glCompileShader(shader);

   // Check the compile status
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

   if (!compiled) {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
      
      if (infoLen > 1){
         char* infoLog = (char*)malloc(sizeof(char) * infoLen );

         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );     
         logger->error("Error compiling shader:\n%s\n", infoLog);

         free(infoLog);
      }

      glDeleteShader(shader);

      return 0;
   }

   return shader;
}

//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
bool GLSLShaderCompiler::loadProgram(GLSLShader* shader, ShaderSource* source) {
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    Ref<String> code = source->getCode();
    const Array<char> program = code->toUTF8CharArray();

    // load the vertex
    vertexShader = this->loadShader(GL_VERTEX_SHADER, "#define VERTEX\n", program);
    if ( vertexShader == 0 ) {
        return false;
    }

    // load fragment shader
    fragmentShader = this->loadShader(GL_FRAGMENT_SHADER, "#define FRAGMENT\n", program);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        return false;
    }

    // try delete program if already exists
    if (shader->programObject) {
        glDeleteProgram(shader->programObject);
    }

    // Create the program object
    programObject = glCreateProgram();
    if (programObject == 0) {
        return false;
    }

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    //glBindAttribLocation(programObject, 0, "a_position" );
    //glBindAttribLocation(programObject, 1, "a_texCoord" );

    // Link the program
    glLinkProgram(programObject);

    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (!linked) {
        GLint infoLen = 0;

        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
      
        if (infoLen > 1){
            char* infoLog = (char* )malloc (sizeof(char) * infoLen );

            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);          
            logger->error("Error linking program:\n%s\n", infoLog);

            free(infoLog);
        }

        glDeleteProgram(programObject);

        return false;
   }

   // Free up no longer needed shader resources
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

   shader->programObject = programObject;
   return true;
}

// auto register shader compiler
static struct GLSLShaderCompilerAutoRegister {
    GLSLShaderCompilerAutoRegister() {
        ShaderManager::getInstance()->registerShaderCompiler(GLSL, new GLSLShaderCompiler());
    }
} __obj;
