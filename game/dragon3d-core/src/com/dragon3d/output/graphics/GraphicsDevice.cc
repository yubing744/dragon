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


#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <com/dragon3d/output/graphics/GraphicsOutputController.h>

#include <dragon/util/logging/Logger.h>


Import com::dragon3d::output::graphics;
Import dragon::util::logging;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::GraphicsDevice", INFO);

GraphicsDevice::GraphicsDevice() {
	this->controller = new GraphicsOutputController(this);
}

GraphicsDevice::~GraphicsDevice() {
	SafeDelete(this->controller);
}

//native void GraphicsDevice::init();

//native void GraphicsDevice::destroy();

int GraphicsDevice::queryStatus(int code) {
	return 0;
}

OutputController* GraphicsDevice::getOutputController() {
	return this->controller;
}

void* GraphicsDevice::getNativeData() {
	return this->nativeData;
}