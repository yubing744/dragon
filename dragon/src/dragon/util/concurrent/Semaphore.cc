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
 * Created:     2013/09/20
 **********************************************************************/


#include <dragon/util/concurrent/Semaphore.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;
Import dragon::util::concurrent;

Semaphore::Semaphore(int permits) {
	this->semaphoreHandle = InitSemaphore(permits);
}

Semaphore::~Semaphore() {
	FreeSemaphore(semaphoreHandle);
}

void Semaphore::acquire() {
	WaitSemaphore(this->semaphoreHandle);
}

bool Semaphore::tryAcquire(int permits) {
	for (int i=0; i<permits; i++) {
		WaitSemaphore(this->semaphoreHandle);
	}
}

bool Semaphore::tryAcquire(int permits, long timeout) {
	for (int i=0; i<permits; i++) {
		WaitSemaphore(this->semaphoreHandle, timeout);
	}
}

void Semaphore::release() {
	SignalSemaphore(this->semaphoreHandle);
}

