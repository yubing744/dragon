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
 * Created:     2013/03/31
 **********************************************************************/

#include <typeinfo>

#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/lang/Class.h>
#include <dragon/lang/ClassLoader.h>

#include <dragon/lang/internal/platform.h>
#include <dragon/lang/CloneNotSupportedException.h>

Import dragon::lang;
Import dragon::lang::internal;


Object::Object() 
	:semaphoreHandle(NULL), refCount(0), clazz(null) {

}

Object::~Object() {
	if (this->semaphoreHandle != NULL) {
		FreeSemaphore(semaphoreHandle);
	}

	finalize();
}

//-------------------------------------------
Object* Object::retain() {
	for (;;) {
		int current = this->refCount;
		int next = current + 1;

		if (AtomicCompareAndSwap((dg_int*)&this->refCount, (dg_int)current, (dg_int)next)) {
			return this;
		}
	}
}

void Object::release() {
	if (this->refCount <= 0) {
		delete this;
	} else {
		for (;;) {
			int current = this->refCount;
			int next = current - 1;

			if (AtomicCompareAndSwap((dg_int*)&this->refCount, (dg_int)current, (dg_int)next)) {
				break;
			}
		}
	}
}

int Object::getRefCount() {
	return this->refCount;
}

//------------------------------------------
Object* Object::clone() const {
	Class* clazz = const_cast<Class*>(this->getClass());
	size_t size = clazz->getSize();

	Object* newObj = (Object*)malloc(size);
	memcpy(newObj, this, size);
	
	newObj->refCount = 0;
	newObj->semaphoreHandle = NULL;

	return newObj;
}

const Class* Object::getClass() const {
	Object* self = const_cast<Object*>(this);

	if (self->clazz == null) {
		ClassLoader* classLoader = ClassLoader::getSystemClassLoader();
		const char* className = Demangle(typeid(*this).name());
		self->clazz = const_cast<Class*>(classLoader->loadClass(className));
	}

	return self->clazz;
}

bool Object::equals(const Object* obj) {
	return this == obj;
}

int Object::hashCode() {
	int* p = (int*)(this);
	return (int)(*p);
}

String* Object::toString() const {
	return String::format(L"@%d", this);
}

void Object::finalize(){}


// ---------------------------------------------
#define SEM_TMP_VAL 1

void* Object::getSemaphore() {
	bool ret = AtomicCompareAndSwap((dg_int*)&this->semaphoreHandle, NULL, SEM_TMP_VAL);
	
	if (ret) {
		this->semaphoreHandle = InitSemaphore(1);
	}

	// wait semaphoreHandle ok
	while(this->semaphoreHandle == (void*)SEM_TMP_VAL) {
		YieldThread();
	}

	return this->semaphoreHandle;
}

void Object::wait() {
	WaitSemaphore(this->getSemaphore());
}

void Object::wait(long timeout) {
	WaitSemaphore(this->getSemaphore(), timeout);
}

void Object::notify() {
	SignalSemaphore(this->getSemaphore());
}

void Object::notifyAll() {
	SignalSemaphore(this->getSemaphore());
}
