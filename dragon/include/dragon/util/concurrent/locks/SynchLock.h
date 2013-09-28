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
 * Created:     2013/09/17
 **********************************************************************/


#ifndef SynchLock_Locks_Concurrent_Util_Dragon_H
#define SynchLock_Locks_Concurrent_Util_Dragon_H

#include <dragon/config.h>
#include <dragon/util/concurrent/locks/Lock.h>

BeginPackage4(dragon, util, concurrent, locks)

Import dragon::util::concurrent::locks;

class _DragonExport SynchLock 
	implements(Lock) {
public:
	SynchLock();
	virtual ~SynchLock();

public: // implements interface Lock
	void lock();
	bool tryLock();
	void unlock();

private:
	void* mutex;
};//SynchLock

EndPackage4 //(dragon, util, concurrent, locks)

#endif //SynchLock_Locks_Concurrent_Util_Dragon_H
