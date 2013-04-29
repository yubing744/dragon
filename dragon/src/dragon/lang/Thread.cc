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
#include <dragon/util/util.h>

#include "internal/platform.h"

Import dragon::lang;
Import dragon::util;

typedef dragon::lang::internal::Thread InternalThread;

//static Map<String, InternalThread*>* defaultThreads = new HashMap<String, InternalThread*>();
static List<InternalThread*>* DefaultThreads = new ArrayList<InternalThread*>();


Thread::Thread(){
	this->target = this;
	this->name = String(L"Dragon Thread");
	this->id = DefaultThreads->size();
	DefaultThreads->add(new InternalThread(InternalThread::Options()));
}

Thread::Thread(Runnable* target){

}

Thread::Thread(const String& name){

}

Thread::Thread(Runnable* target, const String& name){

}

void Thread::getId() {

}

String Thread::getName() {

}

void Thread::setName(const String& name) {

}

void Thread::run() {

}

void Thread::start() {

}

void Thread::interrupt() throw(InterruptedException) {

}

void Thread::join() throw(InterruptedException) {

}

void Thread::join(long millis) throw(InterruptedException) {

}

void Thread::join(long millis,int nanos) throw(InterruptedException) {

}

void Thread::sleep(long millis) throw(InterruptedException){

}

Thread* Thread::currentThread(){

}

void Thread::yield(){

}