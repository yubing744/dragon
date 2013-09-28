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
 * Created:     2013/09/19
 **********************************************************************/


#include <gtest/gtest.h>

#include <dragon/lang/Thread.h>
#include <dragon/lang/internal/platform.h>
#include <dragon/util/concurrent/Semaphore.h>
#include <dragon/util/concurrent/CountDownLatch.h>
#include <dragon/util/concurrent/locks/SynchLock.h>

#include <dragon/util/logging/Logger.h>

Import dragon::lang;
Import dragon::lang::internal;

Import dragon::util::logging;
Import dragon::util::concurrent;
Import dragon::util::concurrent::locks;

static Logger* logger = Logger::getLogger("ThreadTest", DEBUG);


TEST(Dragon_Lang_ThreadTest, New) {
	Thread* o = new Thread();
	o->start();

	// wait sub thread ower!
	o->join();

	SafeDelete(o);
}


// multi thread Lock test
int TEST_THREAD_COUNT = 5;
int TEST_THREAD_WAIT_MS = 10;

Semaphore* sem = NULL;
SynchLock* synLock = NULL;
int Flag = 0;

class LockTest implements(Runnable) {
public:
	void run() {
		logger->debug("lock test run");

		synLock->lock();
		logger->debug("entry lock resource %d", Flag);

		int val = Flag;
		Thread::sleep(TEST_THREAD_WAIT_MS);
		Flag = val + 1;

		logger->debug("out lock resource %d", Flag);
		synLock->unlock();

		sem->release();
	}
};

TEST(Dragon_Lang_ThreadTest, ThreadLockTest) {
	LockTest* lockTest = new LockTest();
	synLock = new SynchLock();
	sem = new Semaphore(0);

	Array<Thread*> threads(TEST_THREAD_COUNT);
	logger->debug("[main thread] start %d thread!", TEST_THREAD_COUNT);

	for (int i=0; i<TEST_THREAD_COUNT; i++) {
		threads[i] = new Thread(lockTest);
		threads[i]->start();
	}

	logger->debug("[main thread] wait thread over!");
	sem->tryAcquire(TEST_THREAD_COUNT);
	logger->debug("[main thread] all thread over!");

	EXPECT_EQ(TEST_THREAD_COUNT, Flag);

	SafeDelete(sem);
	SafeDelete(synLock);
	SafeDelete(lockTest);
}

// Mulit Semaphore Test
// 
CountDownLatch* latch = null;
Object* res = null;
int semFlag = 0;

class SemaphoreTest implements(Runnable) {
public:
	void run() {
		logger->debug("semaphore test run");

		res->wait();
		logger->debug("get resource %d", semFlag);

		int val = semFlag;
		Thread::sleep(TEST_THREAD_WAIT_MS);
		semFlag = val + 1;

		logger->debug("release resource %d", semFlag);
		res->notify();

		latch->countDown();
	}
};

TEST(Dragon_Lang_ThreadTest, ThreadSemaphoreTest) {
	SemaphoreTest* semaphoreTest = new SemaphoreTest();
	res = new Object();
	latch = new CountDownLatch(TEST_THREAD_COUNT);

	Array<Thread*> threads(TEST_THREAD_COUNT);
	logger->debug("[main thread] start %d thread!", TEST_THREAD_COUNT);

	for (int i=0; i<TEST_THREAD_COUNT; i++) {
		threads[i] = new Thread(semaphoreTest);
		threads[i]->start();
	}

	logger->debug("[main thread] wait thread over!");
	latch->await();
	logger->debug("[main thread] all thread over!");

	EXPECT_EQ(TEST_THREAD_COUNT, semFlag);

	SafeDelete(latch);
	SafeDelete(res);
	SafeDelete(semaphoreTest);
}

