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


#ifndef AtomicInteger_Atomic_Concurrent_Util_Dragon_H
#define AtomicInteger_Atomic_Concurrent_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Number.h>

BeginPackage4(dragon, util, concurrent, atomic)

Import dragon::lang;
Import dragon::util::concurrent::atomic;

/**
 * An int value that may be updated atomically. See the java.util.concurrent.atomic package 
 * specification for description of the properties of atomic variables. 
 * An AtomicInteger is used in applications such as atomically incremented counters, and cannot
 * be used as a replacement for an Integer. However, this class does extend Number to allow 
 * uniform access by tools and utilities that deal with numerically-based classes. 
 */
class _DragonExport AtomicInteger
    extends(Number) {
public:
	/**
	 * Creates a new AtomicInteger with initial value 0.
	 */
	AtomicInteger();

	/**
	 * Creates a new AtomicInteger with the given initial value. 
	 * 
	 */
	AtomicInteger(dg_int initialValue);

	/**
	 * destruct
	 */
	virtual ~AtomicInteger();

public:
	/**
	 * Gets the current value. 
	 * 
	 * @return the current value
	 */
	int get();

	/**
	 * Sets to the given value. 
	 * 
	 * @param newValue the new value
	 */
	void set(int newValue);

	/**
	 * Atomically sets to the given value and returns the old value.
	 * 
	 * @param  newValue the new value 
	 * @return          the previous value
	 */
	int getAndSet(int newValue);

	/**
	 * Atomically sets the value to the given updated value if the current value == the expected value. 
	 * 
	 * @param  expect the expected value
	 * @param  update the new value 
	 * @return        
	 * 		rue if successful. False return indicates that the actual 
	 * 		value was not equal to the expected value.
	 */
	bool compareAndSet(int expect, int update);

	/**
	 * Atomically increments by one the current value. 
	 * 
	 * @return the previous value
	 */
	int getAndIncrement();

	/**
	 * Atomically decrements by one the current value. 
	 * 
	 * @return the previous value
	 */
	int getAndDecrement();

	/**
	 * Atomically adds the given value to the current value. 
	 * 
	 * @param  delta [description]
	 * @return       [description]
	 */
	int getAndAdd(int delta);

	/**
	 * Atomically increments by one the current value. 
	 * 
	 * @return the updated value
	 */
	int incrementAndGet();

	/**
	 * Atomically decrements by one the current value. 
	 * 
	 * @return the updated value
	 */
	int decrementAndGet();

	/**
	 * Atomically adds the given value to the current value. 
	 * 
	 * @param  delta the value to add
	 * @return       the updated value
	 */
	int addAndGet(int delta);

public: //Implements Number
    virtual dg_int intValue();
    virtual dg_long longValue();
    virtual dg_float floatValue();
    virtual dg_double doubleValue();

protected:
	/**
	 * the inner value
	 */
	DRAGON_ALIGN(4) volatile dg_int value;

};//AtomicInteger

EndPackage4 //(dragon, util, concurrent, atomic)

#endif //AtomicInteger_Atomic_Concurrent_Util_Dragon_H
