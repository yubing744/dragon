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

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::output::graphics::shader::glsl;

static Logger* logger = Logger::getLogger("GLSLShader#osx", WARN);

#define ERR(e) case e: return #e;
char const *_al_gl_error_string(GLenum e)
{
   switch (e) {
      ERR(GL_NO_ERROR)
      ERR(GL_INVALID_ENUM)
      ERR(GL_INVALID_VALUE)
      ERR(GL_INVALID_OPERATION)
      ERR(GL_STACK_OVERFLOW)
      ERR(GL_STACK_UNDERFLOW)
      ERR(GL_OUT_OF_MEMORY)
#ifndef ALLEGRO_CFG_NO_GLES2
      ERR(GL_INVALID_FRAMEBUFFER_OPERATION)
#endif
   }
   return "UNKNOWN";
}
#undef ERR

static bool check_gl_error(const char* name) {
   GLenum err = glGetError();

   if (err != 0 && err != GL_INVALID_ENUM) {
      logger->warn("GL Error: %s (%s)\n", name, _al_gl_error_string(err));
      return false;
   }

   return true;
}

bool GLSLShader::use() {
    GLuint program_object = this->programObject;
    GLenum err;

    glGetError(); /* clear error */
    glUseProgram(program_object);
    err = glGetError();

    if (err != GL_NO_ERROR) {
        logger->warn("glUseProgram(%u) failed: %s\n", program_object,
         _al_gl_error_string(err));
        return false;
    }

    return true;
}

bool GLSLShader::unuse() {
   glUseProgram(0);
   return true;
}

unsigned int GLSLShader::loadTextureID(Texture* texture){
    GLuint* pTextureID = (GLuint*)texture->getNativeData();

    if (pTextureID == NULL) {
        pTextureID = (GLuint*)malloc(sizeof(GLuint));
        
        // Use tightly packed data
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Generate a texture object
        glGenTextures(1, pTextureID);

        // Bind the texture object
        glBindTexture(GL_TEXTURE_2D, *pTextureID);

        int textureType = GL_RGB;

        if(texture->channels == 4)
            textureType = GL_RGBA;

        // Load the texture
        glTexImage2D(GL_TEXTURE_2D, 0, textureType, texture->getWidth(), 
            texture->getHeight(), 0, textureType, GL_UNSIGNED_BYTE, texture->getData());

        // Set the filtering mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


        texture->setNativeData(pTextureID);
    } 

    return *pTextureID;
}

bool GLSLShader::setSampler(const char* name, Texture* texture, int unit) {
    GLint handle;
    GLuint textureID;

    Ref<String> mapName = this->queryNameMapping(name);
    Array<char> utf8MapName = mapName->toUTF8CharArray();

    handle = glGetUniformLocation(this->programObject, utf8MapName);

    if (handle < 0) {
      logger->warn("No uniform variable '%s' in shader program\n", utf8MapName.raw());
      return false;
    }

    glActiveTexture(GL_TEXTURE0 + unit);


    textureID = (GLuint)this->loadTextureID(texture);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glUniform1i(handle, unit);

    return check_gl_error(utf8MapName);
}

bool GLSLShader::setMatrix(const char* name, const Matrix4x4& matrix) {
   GLint handle;

   Ref<String> mapName = this->queryNameMapping(name);
   Array<char> utf8MapName = mapName->toUTF8CharArray();

   handle = glGetUniformLocation(this->programObject, utf8MapName);

   if (handle < 0) {
      logger->warn("No uniform variable '%s' in shader program\n", utf8MapName.raw());
      return false;
   }

   //glUniformMatrix4fv(handle, 1, false, (float *)matrix.getData());
   glUniform4fv(handle, 4, (float *)matrix.getData());

   return check_gl_error(utf8MapName);
}

bool GLSLShader::setInt(const char* name, int val) {
   GLint handle;

   Ref<String> mapName = this->queryNameMapping(name);
   Array<char> utf8MapName = mapName->toUTF8CharArray();

   handle = glGetUniformLocation(this->programObject, utf8MapName);

   if (handle < 0) {
      logger->warn("No uniform variable '%s' in shader program\n", utf8MapName.raw());
      return false;
   }

   glUniform1i(handle, val);

   return check_gl_error(utf8MapName);
}

bool GLSLShader::setFloat(const char* name, float val) {
   GLint handle;

   Ref<String> mapName = this->queryNameMapping(name);
   Array<char> utf8MapName = mapName->toUTF8CharArray();

   handle = glGetUniformLocation(this->programObject, utf8MapName);

   if (handle < 0) {
      logger->warn("No uniform variable '%s' in shader program\n", utf8MapName.raw());
      return false;
   }

   glUniform1f(handle, val);

   return check_gl_error(utf8MapName);
}

bool GLSLShader::setIntVector(const char* name, int numComponents, const Array<int>& data) {
   GLint handle;

   Ref<String> mapName = this->queryNameMapping(name);
   Array<char> utf8MapName = mapName->toUTF8CharArray();

   handle = glGetUniformLocation(this->programObject, utf8MapName);

   if (handle < 0) {
      logger->warn("No uniform variable '%s' in shader program\n", utf8MapName.raw());
      return false;
   }

   int num_elems = data.size();
   const int* i = data.raw();

   switch (numComponents) {
      case 1:
         glUniform1iv(handle, num_elems, i);
         break;
      case 2:
         glUniform2iv(handle, num_elems, i);
         break;
      case 3:
         glUniform3iv(handle, num_elems, i);
         break;
      case 4:
         glUniform4iv(handle, num_elems, i);
         break;
      default:
         ASSERT(false);
         break;
   }

   return check_gl_error(utf8MapName);
}

bool GLSLShader::setFloatVector(const char* name, int numComponents, const Array<float>& data) {
   GLint handle;

   Ref<String> mapName = this->queryNameMapping(name);
   Array<char> utf8MapName = mapName->toUTF8CharArray();

   handle = glGetUniformLocation(this->programObject, utf8MapName);

   if (handle < 0) {
      logger->warn("No uniform variable '%s' in shader program\n", utf8MapName.raw());
      return false;
   }

   int num_elems = data.size() / numComponents;
   const float* f = data.raw();

   switch (numComponents) {
      case 1:
         glUniform1fv(handle, num_elems, f);
         break;
      case 2:
         glUniform2fv(handle, num_elems, f);
         break;
      case 3:
         glUniform3fv(handle, num_elems, f);
         break;
      case 4:
         glUniform4fv(handle, num_elems, f);
         break;
      default:
         ASSERT(false);
         break;
   }

   return check_gl_error(utf8MapName);
}

bool GLSLShader::setBool(const char* name, bool val) {
    return this->setInt(name, val);
}


bool GLSLShader::setVertexAttribPointer(const char* name, int size, int type, int stride, const void *pointer) {
   GLuint handle;

   Ref<String> mapName = this->queryNameMapping(name);
   Array<char> utf8MapName = mapName->toUTF8CharArray();

   handle = glGetAttribLocation(this->programObject, utf8MapName);

   if (handle < 0) {
      logger->warn("No vertex attrib variable '%s' in shader program\n", utf8MapName.raw());
      return false;
   }

   glVertexAttribPointer(handle, size, GL_FLOAT, false, stride, pointer);
   glEnableVertexAttribArray(handle);

   return check_gl_error(utf8MapName);
}