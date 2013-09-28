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


#include <dragon/util/concurrent/atomic/AtomicInteger.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;
Import dragon::util::concurrent::atomic;


AtomicInteger::AtomicInteger() 
	:value(0) {

}

AtomicInteger::AtomicInteger(dg_int initialValue) 
	:value(initialValue) {

}

AtomicInteger::~AtomicInteger() {
	this->value = 0;
}


int AtomicInteger::get() {
	return this->value;
}

void AtomicInteger::set(int newValue) {
	this->value = newValue;
}

int AtomicInteger::getAndSet(int newValue) {
	for (;;) {
		int current = get();

		if (compareAndSet(current, newValue)) {
			return current;
		}
	}
}

bool AtomicInteger::compareAndSet(int expect, int update) {
	return AtomicCompareAndSwap((dg_int*)&this->value, (dg_int)expect, (dg_int)update);
}

int AtomicInteger::getAndIncrement() {
	for (;;) {
		int current = get();
		int next = current + 1;

		if (compareAndSet(current, next)) {
			return current;
		}
	}
}

int AtomicInteger::getAndDecrement() {
	for (;;) {
		int current = get();
		int next = current - 1;

		if (compareAndSet(current, next)) {
			return current;
		}
	}
}

int AtomicInteger::getAndAdd(int delta) {
	for (;;) {
		int current = get();
		int next = current + delta;

		if (compareAndSet(current, next)) {
			return current;
		}
	}
}

int AtomicInteger::incrementAndGet() {
	for (;;) {
		int current = get();
		int next = current + 1;

		if (compareAndSet(current, next)) {
			return next;
		}
	}
}

int AtomicInteger::decrementAndGet() {
	for (;;) {
		int current = get();
		int next = current - 1;

		if (compareAndSet(current, next)) {
			return next;
		}
	}
}

int AtomicInteger::addAndGet(int delta) {
	for (;;) {
		int current = get();
		int next = current + delta;

		if (compareAndSet(current, next)) {
			return next;
		}
	}
}

//--------- Implements dragon::lang::Number --------------
dg_int AtomicInteger::intValue() {
	return get();
}

dg_long AtomicInteger::longValue() {
	return (dg_long)get();
}

dg_float AtomicInteger::floatValue() {
	return (dg_float)get();
}

dg_double AtomicInteger::doubleValue() {
	return (dg_double)get();
}
