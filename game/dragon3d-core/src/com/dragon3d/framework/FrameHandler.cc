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

#include <dragon/lang/Thread.h>
#include <dragon/lang/gc/Reference.h>

#include <com/dragon3d/framework/FrameHandler.h>
#include <dragon/util/concurrent/CountDownLatch.h>

Import dragon::lang;
Import dragon::lang::gc;
Import dragon::util::concurrent;

Import com::dragon3d::framework;

Logger* FrameHandler::logger = Logger::getLogger("com::dragon3d::framework::FrameHandler");

FrameHandler::FrameHandler() 
	:timeoutSeconds(3) {
	this->timer = new Timer();
	this->updaters = new ArrayList<Updater>();
	this->outputs = new ArrayList<Output>();
}

FrameHandler::FrameHandler(Timer* timer)
	:timeoutSeconds(3) {
	this->timer = (Timer*)timer->retain();
	this->updaters = new ArrayList<Updater>();
	this->outputs = new ArrayList<Output>();
}

FrameHandler::~FrameHandler() {
	SafeRelease(this->timer);
	SafeRelease(this->updaters);
	SafeRelease(this->outputs);
}

void FrameHandler::init() {
	// init updaters
	Ref<Iterator<Updater> > it = this->updaters->iterator();

	while (it->hasNext()) {
		Ref<Updater> updater = it->next();
		updater->init();
	}

	this->timer->reset();
}


void FrameHandler::updateFrame(Scene* scene) {
	// 1. update timer
	this->timer->update();

	// 2. call updater
	Ref<Iterator<Updater> > it = this->updaters->iterator();

	while (it->hasNext()) {
		Ref<Updater> updater = it->next();
		updater->update(scene, this->timer);
	}

	// 3. draw outputs
	int numOutputs = this->outputs->size();
	Ref<Iterator<Output> > itc = this->outputs->iterator();

	Ref<CountDownLatch> latch = new CountDownLatch(numOutputs);

	while (itc->hasNext()) {
		Ref<Output> output = itc->next();
		output->output(scene, latch);
	}

	bool success = latch->await(this->timeoutSeconds * 1000);

    if (!success) {
        logger->warn("updateFrame Timeout while waiting for renderers");
    }
}

void FrameHandler::addUpdater(Updater* updater) {
	if (!this->updaters->contains(updater)) {
		this->updaters->add(updater);
	}
}

void FrameHandler::removeUpdater(Updater* updater) {
	this->updaters->remove(updater);
}

void FrameHandler::addOutput(Output* output){
	if (!this->outputs->contains(output)) {
		this->outputs->add(output);
	}
}

bool FrameHandler::removeOutput(Output* output){
	this->outputs->remove(output);
	return true;
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