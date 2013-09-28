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


#ifndef Semaphore_Concurrent_Util_Dragon_H
#define Semaphore_Concurrent_Util_Dragon_H

#include <dragon/config.h>

BeginPackage3(dragon, util, concurrent)

Import dragon::util::concurrent;

/** 
 * A counting semaphore. Conceptually, a semaphore maintains a set of permits. 
 * Each acquire() blocks if necessary until a permit is available, and then takes it. 
 * Each release() adds a permit, potentially releasing a blocking acquirer. 
 * However, no actual permit objects are used; the Semaphore just keeps a count of 
 * the number available and acts accordingly. 
 */
class _DragonExport Semaphore {
public:

	/**
	 * Creates a Semaphore with the given number of permits and nonfair fairness setting. 
	 */
	Semaphore(int permits);
	virtual ~Semaphore();

public:
	/**
	 * Acquires a permit from this semaphore, blocking until one is available, or the thread is interrupted. 
	 */
	virtual void acquire();

	/**
	 * Acquires the given number of permits from this semaphore, only if all are available at the time of invocation. 
	 * 
	 * @param  permits [description]
	 * @return         [description]
	 */
	virtual bool tryAcquire(int permits);

	/**
	 * Acquires the given number of permits from this semaphore, if all become available within 
	 * the given waiting time and the current thread has not been interrupted. 
	 * 
	 * @param  permits [description]
	 * @param  timeout [description]
	 * @return         [description]
	 */
	virtual bool tryAcquire(int permits, long timeout);

	/**
	 * Releases a permit, returning it to the semaphore. 
	 */
	virtual void release();

protected:
	/**
	 * the handle of semaphore.
	 * 
	 */
	void* semaphoreHandle;

};//Semaphore

EndPackage3 //(dragon, util, concurrent)

#endif //Semaphore_Concurrent_Util_Dragon_H
