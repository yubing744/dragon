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

#include <dlfcn.h>
#include <unistd.h>
#include <sys/mman.h>
#include <mach/mach_init.h>
#include <mach-o/dyld.h>
#include <mach-o/getsect.h>

#include <AvailabilityMacros.h>

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <libkern/OSAtomic.h>
#include <mach/mach.h>
#include <mach/semaphore.h>
#include <mach/task.h>
#include <mach/vm_statistics.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <dragon/lang/internal/platform_posix.h>

Import dragon::lang::internal;

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Atomic Operation

bool dragon::lang::internal::AtomicCompareAndSwap(DRAGON_ATOMICS_VOLATILE dg_int *value, dg_int oldValue, dg_int newValue) {
    return OSAtomicCompareAndSwap32Barrier((int32_t)oldValue, (int32_t)newValue, (volatile int32_t*)value);
}

bool dragon::lang::internal::AtomicCompareAndSwap(DRAGON_ATOMICS_VOLATILE dg_long *value, dg_long oldValue, dg_long newValue) {
    return OSAtomicCompareAndSwap64Barrier((int64_t)oldValue, (int64_t)newValue, (volatile int64_t*)value);
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Semaphore
// 

/**
 * init a mutex object
 * 
 * @return [description]
 */
void* dragon::lang::internal::InitSemaphore(int count) {
    semaphore_t* psemaphore = (semaphore_t*)malloc(sizeof(semaphore_t));

    int r = semaphore_create(mach_task_self(),
                 psemaphore,
                 SYNC_POLICY_FIFO,
                 count);

    ASSERT(r == KERN_SUCCESS);
    return psemaphore;
}

/**
 * wait
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::WaitSemaphore(void* semaphore) {
    semaphore_t* psemaphore = (semaphore_t*)semaphore;

    int r;

    do {
      	r = semaphore_wait(*psemaphore);
      	ASSERT(r == KERN_SUCCESS || r == KERN_ABORTED);
    } while (r == KERN_ABORTED);
}

/**
 * wait with timeout
 * 
 * @param semaphore [description]
 * @param timeout    [description]
 */
bool dragon::lang::internal::WaitSemaphore(void* semaphore, int timeout) {
    semaphore_t* psemaphore = (semaphore_t*)semaphore;

    mach_timespec_t ts;
  	ts.tv_sec = timeout / 1000000;
  	ts.tv_nsec = (timeout % 1000000) * 1000;

  	return semaphore_timedwait(*psemaphore, ts) != KERN_OPERATION_TIMED_OUT;
}

/**
 * notify continue
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::SignalSemaphore(void* semaphore) {
    semaphore_t* psemaphore = (semaphore_t*)semaphore;
    semaphore_signal(*psemaphore);
}

/**
 * free semaphore
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::FreeSemaphore(void* semaphore) {
    semaphore_t* psemaphore = (semaphore_t*)semaphore;

    int r = semaphore_destroy(mach_task_self(), *psemaphore);
    ASSERT(r == KERN_SUCCESS);

    SafeFree(psemaphore);
}

