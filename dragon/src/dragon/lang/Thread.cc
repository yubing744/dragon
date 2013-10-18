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

#include <dragon/lang/Thread.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang;
Import dragon::lang::internal;

//typedef dragon::lang::internal::Thread InternalThread;
//static Map<String, InternalThread*>* defaultThreads = new HashMap<String, InternalThread*>();
//static List<InternalThread*>* DefaultThreads = new ArrayList<InternalThread*>();
#define DEFAULT_STACK_SIZE 1024 * 1024 * 1

Thread::Thread(){
	init(null, "Thread", DEFAULT_STACK_SIZE);
}

Thread::Thread(Runnable* target){
	init(target, "Thread", DEFAULT_STACK_SIZE);
}

Thread::Thread(const char* name){
	init(null, name, DEFAULT_STACK_SIZE);
}

Thread::Thread(Runnable* target, const char* name){
	init(target, name, DEFAULT_STACK_SIZE);
}

Thread::Thread(Runnable* target, const char* name, int stackSize){
	init(target, name, stackSize);
}

Thread::~Thread() {
	SafeDelete(this->name);
}

void Thread::init(Runnable* target, const char* name, int stackSize) {
	this->target = target;
	this->name = new String(name);
	this->id = 1;
	this->stackSize = stackSize;
}

//----------------------------------------------------
int Thread::getId() {
	return this->id;
}

String* Thread::getName() {
	return this->name;
}

void Thread::setName(const char* name) {
	SafeDelete(this->name);
	this->name = new String(name);
}


//----------------------------------------------------
void Thread::run() {
	if (this->target != null) {
		this->target->run();
	}
}

//----------------------------------------------------
typedef void (*ThreadEntryPoint)(void*);

void Thread::entryPoint(void* userData) {
	Thread* thread = (Thread*)userData;
	thread->run();
}

void Thread::start() {
	ThreadEntryPoint entryPoint = &Thread::entryPoint;
	this->threadHandle = CreateThread(this->stackSize, this, cast_void(entryPoint));
}

void Thread::interrupt() {

}

void Thread::join() {
	JoinThread(this->threadHandle);
}

void Thread::join(long millis) {

}

void Thread::join(long millis, int nanos) {

}


//----------------------------------------------------
void Thread::sleep(long millis) {
	SleepThread(millis);
}

Thread* Thread::currentThread(){
	return null;
}

void Thread::yield(){
	YieldThread();
}