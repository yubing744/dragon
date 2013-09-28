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


#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/lang/ClassLoader.h>
#include <dragon/lang/internal/platform.h>

#include <typeinfo>

Import dragon::lang;
Import dragon::lang::internal;


Object::Object() 
	:semaphoreHandle(NULL) {

}

Object::~Object() {
	if (this->semaphoreHandle != NULL) {
		FreeSemaphore(semaphoreHandle);
	}

	finalize();
}

Class* Object::getClass() {
	ClassLoader* classLoader = ClassLoader::getSystemClassLoader();
	return classLoader->loadClass(typeid(*this).name());
}

dg_boolean Object::equals(const Object* obj) {
	return this == obj;
}

dg_int Object::hashCode() {
	dg_int* p = (dg_int*)(this);
	return (dg_int)(*p);
}

String* Object::toString() {
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
