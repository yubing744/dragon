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

#include <OpenGL/gl.h>

Import dragon::util::logging;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::renderer::OpenGLRenderer", INFO);

OpenGLRenderer::OpenGLRenderer(GraphicsDevice* graphicsDevice) {
    this->graphicsDevice = graphicsDevice;
}

OpenGLRenderer::~OpenGLRenderer() {

}

void OpenGLRenderer::init() {
	logger->info("init");
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