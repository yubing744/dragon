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


#include <dragon/util/concurrent/atomic/AtomicLong.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;
Import dragon::util::concurrent::atomic;

AtomicLong::AtomicLong() 
	:value(0) {

}

AtomicLong::AtomicLong(dg_int initialValue) 
	:value(initialValue) {

}

AtomicLong::~AtomicLong() {
	this->value = 0;
}


dg_long AtomicLong::get() {
	return this->value;
}

void AtomicLong::set(dg_long newValue) {
	this->value = newValue;
}

dg_long AtomicLong::getAndSet(dg_long newValue) {
	for (;;) {
		dg_long current = get();

		if (compareAndSet(current, newValue)) {
			return current;
		}
	}
}

bool AtomicLong::compareAndSet(dg_long expect, dg_long update) {
	return AtomicCompareAndSwap((dg_int*)&this->value, (dg_int)expect, (dg_int)update);
}

dg_long AtomicLong::getAndIncrement() {
	for (;;) {
		dg_long current = get();
		dg_long next = current + 1;

		if (compareAndSet(current, next)) {
			return current;
		}
	}
}

dg_long AtomicLong::getAndDecrement() {
	for (;;) {
		dg_long current = get();
		dg_long next = current - 1;

		if (compareAndSet(current, next)) {
			return current;
		}
	}
}

dg_long AtomicLong::getAndAdd(dg_long delta) {
	for (;;) {
		dg_long current = get();
		dg_long next = current + delta;

		if (compareAndSet(current, next)) {
			return current;
		}
	}
}

dg_long AtomicLong::incrementAndGet() {
	for (;;) {
		dg_long current = get();
		dg_long next = current + 1;

		if (compareAndSet(current, next)) {
			return next;
		}
	}
}

dg_long AtomicLong::decrementAndGet() {
	for (;;) {
		dg_long current = get();
		dg_long next = current - 1;

		if (compareAndSet(current, next)) {
			return next;
		}
	}
}

dg_long AtomicLong::addAndGet(dg_long delta) {
	for (;;) {
		dg_long current = get();
		dg_long next = current + delta;

		if (compareAndSet(current, next)) {
			return next;
		}
	}
}

//--------- Implements dragon::lang::Number --------------
dg_int AtomicLong::intValue() {
	return (dg_int)get();
}

dg_long AtomicLong::longValue() {
	return (dg_long)get();
}

dg_float AtomicLong::floatValue() {
	return (dg_float)get();
}

dg_double AtomicLong::doubleValue() {
	return (dg_double)get();
}
