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


#include <dragon/lang/internal/platform_posix.h>

#include <semaphore.h>
#include <signal.h>

#include <errno.h>
#include <time.h>
#include <inttypes.h>

Import dragon::lang::internal;

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Atomic Operation
// 

bool dragon::lang::internal::AtomicCompareAndSwap(DRAGON_ATOMICS_VOLATILE dg_int *value, dg_int valueToCompare, dg_int newValue) {
	return __sync_bool_compare_and_swap((volatile int32_t*)value, valueToCompare, newValue);
}

bool dragon::lang::internal::AtomicCompareAndSwap(DRAGON_ATOMICS_VOLATILE dg_long *value, dg_long valueToCompare, dg_long newValue) {
#ifdef DRAGON_64BIT_ATOMICS
	return __sync_bool_compare_and_swap((volatile int64_t*)value, valueToCompare, newValue);
#else
	throw "not support 64bit atomics";
#endif
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
	sem_t* psem = (sem_t*)malloc(sizeof(sem_t));
    sem_init(psem, 0, count); 
    return psem;
}

/**
 * wait
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::WaitSemaphore(void* semaphore) {
	sem_t* psem = (sem_t*)semaphore;

	while (true) {
	  	int result = sem_wait(psem);
	    if (result == 0) return;  // Successfully got semaphore.
	    ASSERT(result == -1);  // Signal caused spurious wakeup.
	}
}

# define DRAGON_TIMEVAL_TO_TIMESPEC(tv, ts) {                                  \
        (ts)->tv_sec = (tv)->tv_sec;                                    \
        (ts)->tv_nsec = (tv)->tv_usec * 1000;                           \
}

/**
 * wait with timeout
 * 
 * @param semaphore [description]
 * @param timeout    [description]
 */
bool dragon::lang::internal::WaitSemaphore(void* semaphore, int timeout) {
	sem_t* psem = (sem_t*)semaphore;

	const long kOneSecondMicros = 1000000;  // NOLINT

	// Split timeout into second and nanosecond parts.
	struct timeval delta;
	delta.tv_usec = timeout % kOneSecondMicros;
	delta.tv_sec = timeout / kOneSecondMicros;

	struct timeval current_time;
	// Get the current time.
	if (gettimeofday(&current_time, NULL) == -1) {
		return false;
	}

	// Calculate time for end of timeout.
	struct timeval end_time;
	timeradd(&current_time, &delta, &end_time);

	struct timespec ts;
	DRAGON_TIMEVAL_TO_TIMESPEC(&end_time, &ts);

	// Wait for semaphore signalled or timeout.
	while (true) {
		int result = sem_timedwait(psem, &ts);

		if (result == 0) return true;  // Successfully got semaphore.
		if (result > 0) {
		  	// For glibc prior to 2.3.4 sem_timedwait returns the error instead of -1.
		  	errno = result;
		  	result = -1;
		}

		if (result == -1 && errno == ETIMEDOUT) return false;  // Timeout.
		ASSERT(result == -1 && errno == EINTR);  // Signal caused spurious wakeup.
	}
}

/**
 * notify continue
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::SignalSemaphore(void* semaphore) {
	sem_t* psem = (sem_t*)semaphore;
	sem_post(psem);
}

/**
 * free semaphore
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::FreeSemaphore(void* semaphore) {
	sem_t* psem = (sem_t*)semaphore;
	sem_destroy(psem);
    SafeFree(psem);
}


