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

#include "lang.h"

#ifndef Thread_Lang_Dragon_H
#define Thread_Lang_Dragon_H

#include "Runnable.h"
#include "InterruptedException.h"

BeginPackage2(dragon, lang)

class _DragonExport Thread :public Object, public Runnable
{
public:
	Thread();
	Thread(Runnable* target);
	Thread(const String& name);
	Thread(Runnable* target, const String& name);

public:
	virtual void getId() = 0;
	virtual String getName() = 0;
	virtual void setName(const String& name) = 0;

	virtual void run() = 0;

	virtual void start() = 0;
	virtual void interrupt() throw(InterruptedException) = 0;

	virtual void join() throw(InterruptedException) = 0;
	virtual void join(long millis) throw(InterruptedException) = 0;
	virtual void join(long millis,int nanos) throw(InterruptedException) = 0;

public:
	static void sleep(long millis) throw(InterruptedException);
	static Thread* currentThread();
	static void yield();

protected:
	Runnable* target;
	String name;
	Integer id;
};

EndPackage2//(dragon, lang)

#endif//Thread_Lang_Dragon_H