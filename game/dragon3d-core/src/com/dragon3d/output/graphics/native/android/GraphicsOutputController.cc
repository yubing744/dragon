/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http//www.apache.org/licenses/LICENSE-2.0
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


#include <com/dragon3d/output/graphics/GraphicsOutputController.h>

#include <dragon/util/ArrayList.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/scene/model/Model.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/output/graphics/renderer/OpenGLES2Renderer.h>

Import dragon::util;

Import dragon::util::logging;
Import com::dragon3d::scene::model;
Import com::dragon3d::scene::camera;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::GraphicsOutputController#osx", INFO);

GraphicsOutputController::GraphicsOutputController(GraphicsDevice* graphicsDevice) {
    this->graphicsDevice = graphicsDevice;
	this->graphicsRenderer = new OpenGLES2Renderer(graphicsDevice);

    this->placementGrid = new PlacementGrid();
    this->showPlacementGrid = true;
}

GraphicsOutputController::~GraphicsOutputController() {
    SafeDelete(this->placementGrid);
}

