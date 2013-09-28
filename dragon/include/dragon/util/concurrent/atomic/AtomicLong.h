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


#ifndef AtomicLong_Atomic_Concurrent_Util_Dragon_H
#define AtomicLong_Atomic_Concurrent_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Number.h>

BeginPackage4(dragon, util, concurrent, atomic)

Import dragon::lang;
Import dragon::util::concurrent::atomic;

class _DragonExport AtomicLong extends(Number) {
public:
	/**
	 * Creates a new AtomicInteger with initial value 0.
	 */
	AtomicLong();

	/**
	 * Creates a new AtomicInteger with the given initial value. 
	 * 
	 */
	AtomicLong(dg_int initialValue);

	/**
	 * destruct
	 */
	virtual ~AtomicLong();

public:
	/**
	 * Gets the current value. 
	 * 
	 * @return the current value
	 */
	dg_long get();

	/**
	 * Sets to the given value. 
	 * 
	 * @param newValue the new value
	 */
	void set(dg_long newValue);

	/**
	 * Atomically sets to the given value and returns the old value.
	 * 
	 * @param  newValue the new value 
	 * @return          the previous value
	 */
	dg_long getAndSet(dg_long newValue);

	/**
	 * Atomically sets the value to the given updated value if the current value == the expected value. 
	 * 
	 * @param  expect the expected value
	 * @param  update the new value 
	 * @return        
	 * 		rue if successful. False return indicates that the actual 
	 * 		value was not equal to the expected value.
	 */
	bool compareAndSet(dg_long expect, dg_long update);

	/**
	 * Atomically increments by one the current value. 
	 * 
	 * @return the previous value
	 */
	dg_long getAndIncrement();

	/**
	 * Atomically decrements by one the current value. 
	 * 
	 * @return the previous value
	 */
	dg_long getAndDecrement();

	/**
	 * Atomically adds the given value to the current value. 
	 * 
	 * @param  delta [description]
	 * @return       [description]
	 */
	dg_long getAndAdd(dg_long delta);

	/**
	 * Atomically increments by one the current value. 
	 * 
	 * @return the updated value
	 */
	dg_long incrementAndGet();

	/**
	 * Atomically decrements by one the current value. 
	 * 
	 * @return the updated value
	 */
	dg_long decrementAndGet();

	/**
	 * Atomically adds the given value to the current value. 
	 * 
	 * @param  delta the value to add
	 * @return       the updated value
	 */
	dg_long addAndGet(dg_long delta);

public: //Implements Number
    virtual dg_int intValue();
    virtual dg_long longValue();
    virtual dg_float floatValue();
    virtual dg_double doubleValue();

protected:
	/**
	 * the inner value
	 */
	DRAGON_ALIGN(8) volatile dg_long value;
	
};//AtomicLong

EndPackage4 //(dragon, util, concurrent, atomic)

#endif //AtomicLong_Atomic_Concurrent_Util_Dragon_H
