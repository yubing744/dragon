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


#include <dragon/lang/Integer.h>
#include <dragon/util/HashMap.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/math/Mathf.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <com/dragon3d/output/graphics/renderer/OpenGLES2Renderer.h>
#include <com/dragon3d/output/graphics/shader/ShaderManager.h>

Import dragon::lang;
Import dragon::util;

Import com::dragon3d::output::graphics::renderer;
Import com::dragon3d::output::graphics::shader;

OpenGLES2Renderer::OpenGLES2Renderer(GraphicsDevice* graphicsDevice) 
  :graphicsDevice(graphicsDevice) {
    
    //this->normalShader = new Shader(normalVertexShaderStr, normalFragmentShaderStr);

    //this->cachedTextures = new HashMap<int, Integer>();
    //this->cachedShaders = new HashMap<int, Integer>();
}

OpenGLES2Renderer::~OpenGLES2Renderer() {
    //SafeRelease(this->defaultShader);
    //SafeRelease(this->normalShader);

    //SafeRelease(this->cachedTextures);
    //SafeRelease(this->cachedShaders);
}

GraphicsDevice* OpenGLES2Renderer::getDisplay() {
    return this->graphicsDevice;
}

void OpenGLES2RendererNativeInit(GraphicsDevice* graphicsDevice);

void OpenGLES2Renderer::init() {
    OpenGLES2RendererNativeInit(this->graphicsDevice);
}


void OpenGLES2Renderer::clearBuffer() {
    glViewport(0, 0, 320, 480);
    
    Color c("#474747");
    //Color c("#FF0000");
    glClearColor(c.r, c.g, c.b, 0.5f);            // Black Background


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

/*
GLuint OpenGLES2RendererLoadProgram(Shader* shader) {
    // Load the shaders and get a linked program object
    char* utf8Vertex = shader->vertexShader->toUTF8String();
    char* utf8Fragment = shader->fragmentShader->toUTF8String();

    GLuint programObject = OpenGLES2RendererLoadProgram(utf8Vertex, utf8Fragment);

    SafeFree(utf8Vertex);
    SafeFree(utf8Fragment);

    return programObject;
}
*/

void OpenGLES2Renderer::drawSample() {
 
}

Matrix4x4 OpenGLES2RendererSetupCamera(Camera* camera) {
    // setup camera
    Matrix4x4 projMatrix = Matrix4x4::IDENTITY;

    if (camera != null) {
        com::dragon3d::util::math::Rect screenRect = camera->pixelRect;
        com::dragon3d::util::math::Rect nvp = camera->rect;

        glViewport(screenRect.x + screenRect.width * nvp.x, screenRect.y + screenRect.height * nvp.y, 
            screenRect.width * nvp.width, screenRect.height * nvp.height);

        if (!camera->orthographic) {
            Vector3 eye = camera->getTransform()->getPosition();
            Vector3 center = eye.add(Vector3::FORWARD);
            Vector3 up = Vector3::UP;
            projMatrix = projMatrix.multiply(Matrix4x4::lookAt(eye, center, up));

            projMatrix = projMatrix.multiply(Matrix4x4::perspective(camera->fieldOfView, camera->aspect, camera->nearClipPlane, camera->farClipPlane));
        } else {
            projMatrix = projMatrix.multiply(Matrix4x4::ortho(-camera->aspect, camera->aspect, -camera->aspect, camera->aspect, camera->nearClipPlane, camera->farClipPlane));
        }
    } 

    return projMatrix;
}

// Texture
/*
GLuint OpenGLES2RendererInitTexture(Texture* texture){
    GLuint textureID;

    // Use tightly packed data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Generate a texture object
    glGenTextures(1, &textureID);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, textureID);

    int textureType = GL_RGB;
  
    if(texture->channels == 4)
        textureType = GL_RGBA;

    // Load the texture
    glTexImage2D(GL_TEXTURE_2D, 0, textureType, texture->getWidth(), 
        texture->getHeight(), 0, textureType, GL_UNSIGNED_BYTE, texture->getData());

    // Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureID;
}
*/

/*
unsigned int OpenGLES2Renderer::loadTextureID(Texture* texture) {
    int textureID = texture->getID();

    Integer* nativeTextureID = this->cachedTextures->get(textureID);

    if (nativeTextureID == null) {
        nativeTextureID = new Integer(OpenGLES2RendererInitTexture(texture));
        this->cachedTextures->put(textureID, nativeTextureID);
    }

    SafeRelease(nativeTextureID);

    return nativeTextureID->intValue();
}
*/

/*
unsigned int OpenGLES2Renderer::loadProgramID(Shader* shader) {
    int shaderID = shader->getID();

    Integer* nativeShaderID = this->cachedShaders->get(shaderID);

    if (nativeShaderID == null) {
        nativeShaderID = new Integer(OpenGLES2RendererLoadProgram(shader));
        this->cachedShaders->put(shaderID, nativeShaderID);
    }

    SafeRelease(nativeShaderID);

    return nativeShaderID->intValue();
}
*/

Shader* OpenGLES2Renderer::loadShaderFrom(Material* material) {
    Shader* shader = null;

    if (material != null) {
        shader = material->getShader();
    } 

    if (shader == null) {
        shader = ShaderManager::getInstance()->getShader("Normal"); 
    }

    return shader;
}

void OpenGLES2Renderer::drawLine(const Vector3& startV, const Vector3& endV, const Color& color, Camera* camera) {  
    Shader* shader = ShaderManager::getInstance()->getShader("Default"); 

    shader->use();

    // transform mesh to camera space
    Matrix4x4 projMatrix = OpenGLES2RendererSetupCamera(camera);
    shader->setMatrix("modelViewProj", projMatrix);

    // Set Draw Color
    shader->setFloatVector("color", 4, Array<float>(color.getData(), 4, false));

    // Load the vertex data
    float vertices[] = {startV.x, startV.y, startV.z, endV.x, endV.y, endV.z};
    shader->setVertexAttribPointer("position", 3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_LINES, 0, 2);
}

void OpenGLES2Renderer::drawMesh(Mesh* mesh, const Matrix4x4& matrix, Material* material, Camera* camera, int submeshIndex) {
    //logger->debug("draw mesh");
    Shader* shader = this->loadShaderFrom(material);

    // Use the program object
    shader->use(); 

    // transform mesh to camera space
    Matrix4x4 mvpMatrix = Matrix4x4::IDENTITY;
    Matrix4x4 projMatrix = OpenGLES2RendererSetupCamera(camera);

    mvpMatrix = mvpMatrix.multiply(matrix);
    mvpMatrix = mvpMatrix.multiply(projMatrix);

    shader->setMatrix("modelViewProj", mvpMatrix);

    GLuint textureID;

    // setup material
    if (material != null) {
        // setup color
        Color color = material->color;
        shader->setFloatVector("color", 4, Array<float>(color.getData(), 4, false));

        // setup texture
        Texture* mainTexture = material->mainTexture;
        if (mainTexture != null) {
            shader->setSampler("s0", mainTexture, 0);
        }
    }

    // Enable Texture 2D
    if (mesh->hasUV() || mesh->hasUV2()) {
        glEnable(GL_TEXTURE_2D);
    }
   
    // Load the vertex data
    if (mesh->hasVertices()) {
        Array<float> vertices = mesh->getFloatVertices();
        shader->setVertexAttribPointer("position", 3, GL_FLOAT, sizeof(float) * 3, vertices.raw());
    }

    // Load the texture coordinate
    if (mesh->hasUV()) {
        Array<float> uvs = mesh->getFloatUVs();
        shader->setVertexAttribPointer("tex", 2, GL_FLOAT, sizeof(float) * 2, uvs.raw());
    }
    
  
    // Draw Elements
    Array<unsigned short> indices = mesh->getShortIndices(submeshIndex);
    int vCount = indices.length();

    if (vCount >0 && indices.raw()) {
        glDrawElements(GL_TRIANGLES, vCount, GL_UNSIGNED_SHORT, indices.raw());
    }
   
    // Disable Texture 2D
    if (mesh->hasUV() || mesh->hasUV2()) {
        glDisable(GL_TEXTURE_2D);
    }
}

// native void OpenGLES2Renderer::flushBuffer();

