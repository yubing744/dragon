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

#ifndef Thread_Lang_Dragon_H
#define Thread_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Runnable.h>
#include <dragon/lang/String.h>

BeginPackage2(dragon, lang)

class _DragonExport Thread 
	implements(Runnable)
{
public:
	Thread();
	Thread(Runnable* target);
	Thread(const char* name);
	Thread(Runnable* target, const char* name);
	Thread(Runnable* target, const char* name, int stackSize);

	virtual ~Thread();

public: // implements interface Runnable
	virtual void run();

public:
	virtual int getId();
	virtual String* getName();
	virtual void setName(const char* name);

	virtual void start();
	virtual void interrupt();

	virtual void join();
	virtual void join(long millis);
	virtual void join(long millis, int nanos);

public:
	static void sleep(long millis);
	static Thread* currentThread();
	static void yield();

protected:
	void init(Runnable* target, const char* name, int stackSize);

public: // Thread entry point
	static void entryPoint(void* userData);

protected:
	Runnable* target;
	String* name;
	int id;
	int stackSize;

	void* threadHandle;
};


EndPackage2//(dragon, lang)

#endif//Thread_Lang_Dragon_H