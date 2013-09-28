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
 * Created:     2013/09/17
 **********************************************************************/


#include <com/dragon3d/framework/FrameHandler.h>
#include <dragon/util/concurrent/CountDownLatch.h>

Import com::dragon3d::framework;

Import dragon::util::concurrent;
Import dragon::util::concurrent::locks;

Logger* FrameHandler::logger = Logger::getLogger("com::dragon3d::framework.FrameHandler");

FrameHandler::FrameHandler() 
	:timeoutSeconds(3) {
	this->timer = new Timer();
	this->updaters = new ArrayList<Updater>();
	this->canvases = new ArrayList<Canvas>();
}

FrameHandler::~FrameHandler() {
	SafeDelete(this->timer);
	SafeDelete(this->updaters);
	SafeDelete(this->canvases);
}

void FrameHandler::init() {
	// init updaters
	Iterator<Updater>* it = this->updaters->iterator();

	while (it->hasNext()) {
		Updater* updater = it->next();
		updater->init();
	}

	SafeDelete(it);

	// init canvase
	Iterator<Canvas>* itc = this->canvases->iterator();

	while (itc->hasNext()) {
		Canvas* canvase = itc->next();
		canvase->init();
	}

	SafeDelete(itc);
}


void FrameHandler::updateFrame() {
	// 1. update timer
	this->timer->update();

	// 2. call updater
	Iterator<Updater>* it = this->updaters->iterator();

	while (it->hasNext()) {
		Updater* updater = it->next();
		updater->update(this->timer);
	}

	SafeDelete(it);

	// 3. draw canvases
	int numCanvases = this->canvases->size();
	Iterator<Canvas>* itc = this->canvases->iterator();

	CountDownLatch* latch = new CountDownLatch(numCanvases);

	while (itc->hasNext()) {
		Canvas* canvase = itc->next();
		canvase->draw(latch);
	}

	bool success = latch->await(this->timeoutSeconds * 1000);

    if (!success) {
        logger->warn("updateFrame Timeout while waiting for renderers");
    }

    SafeDelete(itc);
	SafeDelete(latch);
}

void FrameHandler::addUpdater(Updater* updater) {
	if (!this->updaters->contains(updater)) {
		this->updaters->add(updater);
	}
}

void FrameHandler::removeUpdater(Updater* updater) {
	this->updaters->remove(updater);
}

void FrameHandler::addCanvas(Canvas* canvas){
	if (!this->canvases->contains(canvas)) {
		this->canvases->add(canvas);
	}
}

bool FrameHandler::removeCanvas(Canvas* canvas){
	this->canvases->remove(canvas);
}

int FrameHandler::getTimeoutSeconds(){
	return this->timeoutSeconds;
}

void FrameHandler::setTimeoutSeconds(int timeoutSeconds){
	this->timeoutSeconds = timeoutSeconds;
}

Timer* FrameHandler::getTimer(){
	return this->timer;
}