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


#include <dragon/util/concurrent/atomic/AtomicBoolean.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;
Import dragon::util::concurrent::atomic;

AtomicBoolean::AtomicBoolean() 
	:value(0) {

}

AtomicBoolean::AtomicBoolean(bool initialValue) 
	:value(initialValue?1:0) {

}

AtomicBoolean::~AtomicBoolean() {
	this->value = false;
}

bool AtomicBoolean::compareAndSet(bool expect, bool update) {
	dg_int e = expect ? 1 : 0;
	dg_int u = update ? 1 : 0;

	return AtomicCompareAndSwap((dg_int*)&this->value, e, u);
}

bool AtomicBoolean::get() {
	return this->value != 0;
}

bool AtomicBoolean::getAndSet(bool newValue) {
	for (;;) {
		bool current = get();

		if (compareAndSet(current, newValue)) {
			return current;
		}
	}
}

void AtomicBoolean::set(bool newValue) {
	this->value = newValue ? 1 : 0;
}

