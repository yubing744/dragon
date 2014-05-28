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
#include <com/dragon3d/output/graphics/vbo/VBOMeshCacheManager.h>

Import dragon::lang;
Import dragon::util;

Import com::dragon3d::output::graphics::renderer;
Import com::dragon3d::output::graphics::shader;
Import com::dragon3d::output::graphics::vbo;

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
    glViewport(0, 0, 320, 320);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(true);

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

#define VERTEX_POS_SIZE 3
#define VERTEX_NORMAL_SIZE 3
#define VERTEX_TEXCOORD0_SIZE 2 

#define VERTEX_POS_INDX 0 
#define VERTEX_NORMAL_INDX 1 
#define VERTEX_TEXCOORD0_INDX 2

void OpenGLES2Renderer::drawSample() {
    float cubeVerts[] =
    {
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f, -0.5f,

      -0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,

      -0.5f, -0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f, 0.5f,
      -0.5f,  0.5f, 0.5f,
      0.5f,  0.5f, 0.5f, 
      0.5f, -0.5f, 0.5f,

      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
   };

   float cubeNormals[] =
   {
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
   };

   float cubeTex[] =
   {
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
    };

    unsigned short cubeIndices[] =
    {
        0, 2, 1,
        0, 3, 2, 
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11, 
        12, 15, 14,
        12, 14, 13, 
        16, 17, 18,
        16, 18, 19, 
        20, 23, 22,
        20, 22, 21
    };

    int numVertices = 24;
    int numIndices = 36;

    Shader* shader = ShaderManager::getInstance()->getShader("Normal");
    unsigned int programID = shader->getID();

    if (shader != null) {
        shader->use();

        GLuint vboIds[3];

        // vboIds[3] – used to store element indices 
        glGenBuffers(3, vboIds);
    
        glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]); 
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices, cubeVerts, GL_STATIC_DRAW); 

        glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
        glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * numVertices, cubeTex, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[2]); 
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numIndices, cubeIndices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]); 
        glEnableVertexAttribArray(VERTEX_POS_INDX); 

        glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]); 
        glEnableVertexAttribArray(VERTEX_TEXCOORD0_INDX);

        glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glVertexAttribPointer(VERTEX_TEXCOORD0_INDX, VERTEX_TEXCOORD0_SIZE, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

        glBindAttribLocation(programID, VERTEX_POS_INDX, "POSITION");
        glBindAttribLocation(programID, VERTEX_TEXCOORD0_INDX,"TEXCOORD"); 

        //shader->setVertexAttribPointer("position", 3, GL_FLOAT, 3, 0);
        //shader->setVertexAttribPointer("uv", 2, GL_FLOAT, 2, 0);

        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

       GLenum err = glGetError();

       if (err != 0 && err != GL_INVALID_ENUM) {
          logger->error("GL Error: \n");
       }

        glDeleteBuffers(3, vboIds);
    }
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

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
   
    VBOMeshCache* cache = VBOMeshCacheManager::getInstance()->getCacheMeshData(mesh);
    glBindBuffer(GL_ARRAY_BUFFER, cache->vertexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cache->indexBufferID);

    int vtxStride = cache->vtxStride;

    // Load the vertex data
    if (mesh->hasVertices()) {
        shader->setVertexAttribPointer("position", 3, GL_FLOAT, vtxStride, (const void*)cache->posOffset);
    }

    // Load the texture coordinate
    if (mesh->hasUV()) {
        shader->setVertexAttribPointer("uv", 2, GL_FLOAT, vtxStride, (const void*)cache->uvOffset);
    }
    
     // Load the texture coordinate 2
    if (mesh->hasUV2()) {
        shader->setVertexAttribPointer("uv2", 2, GL_FLOAT, vtxStride, (const void*)cache->uv2Offset);
    }

    // Draw Elements
    Array<unsigned short> indices = mesh->getShortIndices(submeshIndex);
    int vCount = indices.length();

    if (vCount >0) {
        glDrawElements(GL_TRIANGLES, vCount, GL_UNSIGNED_SHORT, 0);
    }
   
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Disable Texture 2D
    if (mesh->hasUV() || mesh->hasUV2()) {
        glDisable(GL_TEXTURE_2D);
    }
}

// native void OpenGLES2Renderer::flushBuffer();

