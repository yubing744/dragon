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
 * Created:     2013/09/21
 **********************************************************************/


#include <dragon/util/concurrent/CountDownLatch.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;
Import dragon::util::concurrent;

CountDownLatch::CountDownLatch(int initCount) 
	:count(initCount) {
	this->semaphoreHandle = InitSemaphore(0);
}

CountDownLatch::~CountDownLatch() {
	this->count = 0;
	FreeSemaphore(semaphoreHandle);
}

void CountDownLatch::await() {
	while(this->count > 0) {
		WaitSemaphore(this->semaphoreHandle);
		this->count--;
	}
}

bool CountDownLatch::await(dg_long timeout) {
	while(this->count > 0) {
		WaitSemaphore(this->semaphoreHandle, timeout);
		this->count--;
	}
}

void CountDownLatch::countDown() {
	SignalSemaphore(this->semaphoreHandle);
}

int CountDownLatch::getCount() {
	return this->count;
}

String* CountDownLatch::toString() {
	return String::format("Count = %d", this->count);
}
