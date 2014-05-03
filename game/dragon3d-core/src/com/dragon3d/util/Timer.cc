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


#include <dragon/lang/System.h>
#include <com/dragon3d/util/Timer.h>

Import dragon::lang;
Import com::dragon3d::util;

#define TIMER_RESOLUTION 1000000
#define INVERSE_TIMER_RESOLUTION (1.0/TIMER_RESOLUTION)

Timer::Timer() 
	:paused(false) {
	this->reset();
}

Timer::~Timer() {

}

double Timer::getTimeInSeconds() {
	return getTime() * INVERSE_TIMER_RESOLUTION;
}

dg_long Timer::getTime() {
	if (this->paused) {
		this->startTime = System::nanoTime() - this->previousTime;
		return this->previousTime;
	} else {
		return System::nanoTime() - this->startTime;
	}
}

dg_long Timer::getResolution() {
	return TIMER_RESOLUTION;
}

double Timer::getFrameRate() {
	return this->fps;
}

double Timer::getDeltaTime() {
	return this->tps;
}	

// ---------------------------------------
void Timer::update() {
	dg_long curTime = getTime();

	this->tps = (curTime - this->previousTime) * INVERSE_TIMER_RESOLUTION;
	this->fps = 1.0 / this->tps;

	this->previousTime = curTime;
}

void Timer::pause() {
	this->paused = true;
}

void Timer::resume() {
	this->paused = false;
}

void Timer::reset() {
	this->startTime = System::nanoTime();
	this->previousTime = getTime();
}

