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
    SafeRetain(graphicsDevice);
}

OpenGLES2Renderer::~OpenGLES2Renderer() {
    SafeRelease(this->graphicsDevice);
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
    glClearColor(c.r, c.g, c.b, 0.5f);            // Black Background

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);

    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}


void OpenGLES2Renderer::setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height); 
}

void OpenGLES2Renderer::drawSample() {
 
}

Matrix4x4 OpenGLES2RendererSetupCamera(Camera* camera) {
    // setup camera
    Matrix4x4 projMatrix = Matrix4x4::IDENTITY;

    if (camera != null) {
        com::dragon3d::util::math::Rect viewport = camera->getViewPortRect();
        glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
        
        projMatrix = camera->getModelViewProjectionMatrix();
    } 

    return projMatrix;
}

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
        material->renderUntoShader(shader);
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
        shader->setVertexAttribPointer("uv", 2, GL_FLOAT, sizeof(float) * 2, uvs.raw());
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

