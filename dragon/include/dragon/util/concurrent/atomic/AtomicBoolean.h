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


#ifndef AtomicBoolean_Atomic_Concurrent_Util_Dragon_H
#define AtomicBoolean_Atomic_Concurrent_Util_Dragon_H

#include <dragon/config.h>

BeginPackage4(dragon, util, concurrent, atomic)

Import dragon::util::concurrent::atomic;

/**
 * can update the value by atomic way.
 * 
 */
class _DragonExport AtomicBoolean {
public:
	/**
	 * init false to create atomic
	 */
	AtomicBoolean();

	/**
	 * init with given init value
	 */
	AtomicBoolean(bool initialValue);

	/**
	 * destruct
	 */
	virtual ~AtomicBoolean();

public:
	/**
	 * if the current value == expect, then update the value with
	 * update
	 * 
	 * @param  expect [expect value]
	 * @param  update [to update]
	 * @return        [if success, then return true.]
	 */
	bool compareAndSet(bool expect, bool update);

	/**
	 * return the current value.
	 * 
	 * @return [description]
	 */
	bool get();

	/**
	 * set new value by atomic way, and return the old value.
	 * 
	 * @param  newValue [description]
	 * @return          [description]
	 */
	bool getAndSet(bool newValue);

	/**
	 * Unconditionally sets to the given value. 
	 * 
	 * @param newValue [description]
	 */
	void set(bool newValue);

protected:
	/**
	 * the inner value
	 */
	DRAGON_ALIGN(4) volatile dg_int value;

};//AtomicBoolean

EndPackage4 //(dragon, util, concurrent, atomic)

#endif //AtomicBoolean_Atomic_Concurrent_Util_Dragon_H
