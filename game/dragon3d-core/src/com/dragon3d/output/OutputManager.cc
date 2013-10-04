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


#include <com/dragon3d/output/OutputManager.h>
#include <com/dragon3d/output/OutputController.h>

#include <dragon/util/HashMap.h>
#include <dragon/util/ArrayList.h>

#include <dragon/util/logging/Logger.h>
 
#include <dragon/lang/System.h>
#include <dragon/lang/Throwable.h>

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::output;
Import dragon::util::logging;
Import com::dragon3d::framework;

static Logger* logger = Logger::getLogger("com::dragon3d::output::OutputManager", INFO);

OutputManager::OutputManager() {
	this->outputDevices = new ArrayList<OutputDevice>();
}

OutputManager::~OutputManager() {
	this->outputDevices->clear();
	SafeDelete(this->outputDevices);
}

void OutputManager::init() {
	logger->info("init");

	Iterator<OutputDevice>* it = this->outputDevices->iterator();

	while(it->hasNext()) {
		OutputDevice* device = it->next();
		
		if (device != null) {
			device->init();
		}
	}
}

void OutputManager::output(Scene* scene, CountDownLatch* latch) {
	Iterator<OutputDevice>* it = this->outputDevices->iterator();

	while(it->hasNext()) {
		OutputDevice* device = it->next();
		
		if (device != null) {
			OutputController* controller = device->getOutputController();
			ASSERT(controller != null);
			controller->output(scene);
		}
	}

	latch->countDown();
}

void OutputManager::destroy() {
	logger->info("destroy");

	Iterator<OutputDevice>* it = this->outputDevices->iterator();

	while(it->hasNext()) {
		OutputDevice* device = it->next();
		
		if (device != null) {
			device->destroy();
		}
	}
}

void OutputManager::registerDevice(OutputDevice* outputDevice) {
	this->outputDevices->add(outputDevice);
}
