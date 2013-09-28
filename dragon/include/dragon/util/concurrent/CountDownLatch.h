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


#ifndef CountDownLatch_Concurrent_Util_Dragon_H
#define CountDownLatch_Concurrent_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>

BeginPackage3(dragon, util, concurrent)

Import dragon::lang;

/**
 * A synchronization aid that allows one or more threads to wait until a set of
 * operations being performed in other threads completes. 
 */
class _DragonExport CountDownLatch extends(Object) {
public:
	CountDownLatch(int count);
	virtual ~CountDownLatch();

public:
	/**
	 * Causes the current thread to wait until the latch has counted down to zero, 
	 * unless the thread is interrupted. 
	 */
	virtual void await();

	/**
	 * Causes the current thread to wait until the latch has counted down to zero, 
	 * unless the thread is interrupted, or the specified waiting time elapses. 
	 * 
	 * @param  timeout [description]
	 * @return         [description]
	 */
	virtual bool await(dg_long timeout);

	/**
	 * Decrements the count of the latch, releasing all waiting threads if the count reaches zero. 
	 * 
	 */
	virtual void countDown();

	/**
	 * Returns the current count. 
	 * 
	 * @return [description]
	 */
	virtual int getCount();

	/**
	 * Returns a string identifying this latch, as well as its state. The state, in brackets, 
	 * includes the String "Count =" followed by the current count. 
	 * 
	 * @return [description]
	 */
	virtual String* toString();

protected:
	/**
	 * count of wait.
	 */
	int count;

	/**
	 * the handle of semaphore.
	 * 
	 */
	void* semaphoreHandle;

};//CountDownLatch

EndPackage3 //(dragon, util, concurrent)

#endif //CountDownLatch_Concurrent_Util_Dragon_H
