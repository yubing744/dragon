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


#include <com/dragon3d/output/graphics/renderer/OpenGLRenderer.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <com/dragon3d/util/math/Mathf.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

Import dragon::util::logging;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;
Import com::dragon3d::util::math;

OpenGLRenderer::OpenGLRenderer(GraphicsDevice* graphicsDevice) {
    this->graphicsDevice = graphicsDevice;
}

OpenGLRenderer::~OpenGLRenderer() {

}

void OpenGLRenderer::init() {
	logger->info("init");

    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading

    //Color c("#474747");
    Color c("#FF0000");
    glClearColor(c.r, c.g, c.b, 0.5f);                  // Black Background

    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations

    glPointSize(8);  
    glLineWidth(5); 

    // The following commands should induce OpenGL to create round points and   
    // antialias points and lines.  (This is implementation dependent unfortunately).  
    //RGBA mode antialias need cooperate with blend function.  
    glEnable(GL_POINT_SMOOTH);  
    glEnable(GL_LINE_SMOOTH);  
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();
}

//native void OpenGLRenderer::flushBuffer();

void OpenGLRenderer::drawSample() {
	logger->debug("draw sample shape.");

	glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.85f, 0.35f);

    glBegin(GL_TRIANGLES);
    
    {

        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);

    }

    glEnd();
}


void OpenGLRendererInitTexture(Texture* texture) {
    glGenTextures(1, &texture->nativeTextureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, texture->nativeTextureID);
    
    int textureType = GL_RGB;
    
    if(texture->channels == 4)
        textureType = GL_RGBA;
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, texture->channels, texture->width, 
        texture->height, textureType, GL_UNSIGNED_BYTE, texture->data);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);                         
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void OpenGLRendererSetupCamera(Camera* camera) {
    // setup camera
    if (camera != null) {
        com::dragon3d::util::math::Rect screenRect = camera->pixelRect;
        com::dragon3d::util::math::Rect nvp = camera->rect;

        glViewport(screenRect.x + screenRect.width * nvp.x, screenRect.y + screenRect.height * nvp.y, 
            screenRect.width * nvp.width, screenRect.height * nvp.height);

        if (!camera->orthographic) {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity(); 
            
            Matrix4x4 projMatrix = Matrix4x4::IDENTITY;

            Vector3 eye = camera->transform->getPosition();
            Vector3 center = eye.add(Vector3::FORWARD);
            Vector3 up = Vector3::UP;
            projMatrix = projMatrix.multiply(Matrix4x4::lookAt(eye, center, up));
            
            projMatrix = projMatrix.multiply(Matrix4x4::perspective(camera->fieldOfView, camera->aspect, camera->nearClipPlane, camera->farClipPlane));

            glMultMatrixf((float *)&projMatrix.m[0][0]);
        } else {
            glOrtho(-camera->aspect, camera->aspect, -camera->aspect, camera->aspect, camera->nearClipPlane, camera->farClipPlane);
        }
    }
}


void OpenGLRenderer::drawLine(const Vector3& startV, const Vector3& endV, const Color& color, Camera* camera) {
    // setup camera
    OpenGLRendererSetupCamera(camera);

    // set color
    glColor3f(color.r, color.g, color.b);

    glMatrixMode(GL_MODELVIEW); 

    glBegin(GL_LINES);
        glVertex3f(startV.x, startV.y, startV.z);
        glVertex3f(endV.x, endV.y, endV.z);
    glEnd();
}

void OpenGLRendererDrawMeshData(Mesh* mesh) {
    // draw mesh
    int vCount = mesh->triangleIndexCount;

    if (mesh->uv || mesh->uv2) {
        glEnable(GL_TEXTURE_2D);
    }

    glBegin(GL_TRIANGLES);

        for (int i=0; i< vCount; i++) {
            int pos = mesh->triangleIndexs[i];

            //set texCoord
            if (mesh->uv) {
                Vector2* uv = &mesh->uv[pos];
                glTexCoord2f(uv->x, uv->y);
            }

            //set vertext
            if (mesh->vertices) {
                Vector3* v = &mesh->vertices[pos];
                glVertex3f(v->x, v->y, v->z);
            }
        }

    glEnd();

    if (mesh->uv || mesh->uv2) {
        glDisable(GL_TEXTURE_2D);
    }
}

void OpenGLRenderer::drawMesh(Mesh* mesh, const Matrix4x4& matrix, Material* material, Camera* camera) {
    // setup camera
    OpenGLRendererSetupCamera(camera);

    // setup material
    if (material != null) {
        // setup color
        Color c = material->color;
        glColor3f(c.r, c.g, c.b);

        // setup texture
        Texture* mainTexture = material->mainTexture;

        if (mainTexture != null) {
            GLuint textureID = mainTexture->getNativeTextureID();

            if (textureID == 0) {
                OpenGLRendererInitTexture(mainTexture);
            } else {
                glBindTexture(GL_TEXTURE_2D, mainTexture->nativeTextureID);
            }
        }
    }

    // transform mesh
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glScalef(-1.0f, 1.0f, 1.0f); //change to left handle coordinate system
    glMultMatrixf((float *)matrix.m);

    // draw mesh
    OpenGLRendererDrawMeshData(mesh);
}

