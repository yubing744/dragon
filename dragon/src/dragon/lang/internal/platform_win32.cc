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

#include <windows.h>
#include <process.h>
#include <Dbghelp.h>

#pragma comment(lib,"Dbghelp.lib")


#include <string>
#include <map>

#include <dragon/lang/internal/platform.h>

Import std;
Import dragon::lang::internal;

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Invoke
//

void* dragon::lang::internal::Invoke(void* pthis, void* func, ParamInfo *argv, int argc) {
	ReturnInfo ret("void*");
	Invoke(pthis, func, &ret, argv, argc);
	return ret.getValue<void*>();
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Local Library
// 

const char* dragon::lang::internal::GetLocalLibPath() {
	char* szPath =(char*)malloc(1024);

    if(!GetModuleFileNameA(NULL, szPath, 1024 )) {
        return NULL;
    }

	return szPath;
}


/**
 *  get dragon lib's path.
 *    
 */
const char* dragon::lang::internal::GetDragonLibPath() {
	char* szPath =(char*)malloc(1024);

	HMODULE hSysLib;
	LPCTSTR address = (LPCTSTR)&SymTestBean::classLocationFlag;
	if(!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, address, &hSysLib)){
		return NULL;
	}

    if(!GetModuleFileNameA(hSysLib, szPath, 1024 )) {
        return NULL;
    }

	return szPath;
}


void dragon::lang::internal::ShowLocalLibInfo() {
	
}

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// SymbolMangling Implements 
//

string dragon::lang::internal::Mangling(const char* fun_signature) {
	vector<string> sb;
	return Join(sb, "");
}

char* dragon::lang::internal::Demangle(const char* symbol) {
	char* szPath =(char*)malloc(1024);

	DWORD Flags = UNDNAME_COMPLETE;
	Flags |= UNDNAME_NO_ALLOCATION_LANGUAGE;
	Flags |= UNDNAME_NO_ACCESS_SPECIFIERS;
	Flags |= UNDNAME_NO_ALLOCATION_MODEL;
	Flags |= UNDNAME_NO_FUNCTION_RETURNS;
	Flags |= UNDNAME_NO_MEMBER_TYPE;
	Flags |= UNDNAME_NO_MS_KEYWORDS;
	Flags |= UNDNAME_NO_MS_THISTYPE;
	Flags |= UNDNAME_NO_THROW_SIGNATURES;
	Flags |= UNDNAME_NO_THISTYPE;
	Flags |= UNDNAME_NO_RETURN_UDT_MODEL;

	if (UnDecorateSymbolName(symbol, szPath, 1024, Flags)) {
	    return szPath;
	}

	return NULL;
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Library export Function
// 

typedef int (DRAGON_STDCALL *Func_FarProc)();
typedef int (DRAGON_STDCALL *Func_GetClassSize)(void);

void* dragon::lang::internal::GetFuncAddress(const char* libPath, const char* signature) {
	HINSTANCE hDLL;               // Handle to DLL
	Func_FarProc lpfnDllFunc1;    // Function pointer

	hDLL = LoadLibraryA(libPath);

	if (hDLL != NULL) {
	   	lpfnDllFunc1 = (Func_FarProc)GetProcAddress(hDLL, signature);

	   	if (!lpfnDllFunc1) {
	      	FreeLibrary(hDLL);
	     	return NULL;
	   	}

	    return (void*)lpfnDllFunc1;
	}

	return NULL;
}

void* dragon::lang::internal::GetFuncAddress(const char* signature) {
	const char* localLibPath = GetLocalLibPath();
	return GetFuncAddress(localLibPath, signature);
}

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Time
// 

/**
 * get the system time
 * 
 * @return [description]
 */
dg_long dragon::lang::internal::GetSystemTime() {
	/*
	struct _timeb t;

	#ifdef _INC_TIME_INL
	_ftime_s(&t);
	#else
	_ftime(&t);
	#endif

	return (((dg_long) t.time) * 1000 + t.millitm) * 1000;
	*/

	LARGE_INTEGER fc;

    if (!QueryPerformanceFrequency(&fc)) {
        assert(FALSE);
    }

    UINT64 frequency = fc.QuadPart;

    if (!QueryPerformanceCounter(&fc)) {
        assert(FALSE);
    }

    UINT64 c = fc.QuadPart;
    UINT64 s = (c) / (frequency / 1000 / 1000 / 1000);

    return s;
}



// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Lock
// 

/**
 * init a mutex object
 * 
 * @return [description]
 */
void* dragon::lang::internal::InitMutex() {
	CRITICAL_SECTION* pcs = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
	InitializeCriticalSection(pcs);
	return pcs;
}

/**
 *  lock the mutex
 * 
 * @return [description]
 */
void dragon::lang::internal::LockMutex(void* mutex) {
	CRITICAL_SECTION* pcs = (CRITICAL_SECTION*)mutex;
	EnterCriticalSection(pcs);
}

/**
 *  try lock the mutex
 * 
 * @return [description]
 */
bool dragon::lang::internal::TryLockMutex(void* mutex) {
	CRITICAL_SECTION* pcs = (CRITICAL_SECTION*)mutex;
	return TryEnterCriticalSection(pcs);
}

/**
 *  unlock the mutex
 * 
 * @return [description]
 */
void dragon::lang::internal::UnlockMutex(void* mutex) {
	CRITICAL_SECTION* pcs = (CRITICAL_SECTION*)mutex;
	LeaveCriticalSection(pcs);
}

/**
 * free mutex object
 * 
 * @return [description]
 */
void dragon::lang::internal::FreeMutex(void* mutex) {
	CRITICAL_SECTION* pcs = (CRITICAL_SECTION*)mutex;
	SafeFree(pcs);
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
	HANDLE* psem = (HANDLE*)malloc(sizeof(HANDLE));
    *psem = ::CreateSemaphoreA(NULL, count, 0x7fffffff, NULL);
    return psem;
}

/**
 * wait
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::WaitSemaphore(void* semaphore) {
	HANDLE* psem = (HANDLE*)semaphore;
	WaitForSingleObject(*psem, INFINITE);
}

/**
 * wait with timeout
 * 
 * @param semaphore [description]
 * @param timeout    [description]
 */
bool dragon::lang::internal::WaitSemaphore(void* semaphore, int timeout) {
	HANDLE* psem = (HANDLE*)semaphore;
	DWORD millis_timeout = timeout / 1000;
    return WaitForSingleObject(*psem, millis_timeout) != WAIT_TIMEOUT;
}

/**
 * notify continue
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::SignalSemaphore(void* semaphore) {
	HANDLE* psem = (HANDLE*)semaphore;
	LONG dummy;
    ReleaseSemaphore(*psem, 1, &dummy);
}

/**
 * free semaphore
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::FreeSemaphore(void* semaphore) {
	HANDLE* psem = (HANDLE*)semaphore;
	CloseHandle(*psem);
    SafeFree(psem);
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Thread
// 

// mine thread handle
typedef struct ThreadHandle{
  	HANDLE thread;
  	unsigned thread_id;
};

// thread entry func
typedef unsigned int (__stdcall *ThreadEntryFunc)(void *);

// Definition of invalid thread handle and id.
static const HANDLE kNoThread = INVALID_HANDLE_VALUE;

/**
 * create a new thread, and return thread handle
 *
 * @param stackSize the stack size for thread
 * @param entryFunc the entry function for thread
 */
void* dragon::lang::internal::CreateThread(int stackSize, void* target, void* entryFunc) {
	struct ThreadHandle* handle = (struct ThreadHandle*)malloc(sizeof(struct ThreadHandle*));

    ThreadEntryFunc func = void_cast<ThreadEntryFunc>(entryFunc);
  	handle->thread = reinterpret_cast<HANDLE>(
      _beginthreadex(NULL,
                     static_cast<unsigned>(stackSize),
                     func,
                     target,
                     0,
                     &handle->thread_id));
  	return handle;
}

/**
 * join the thread
 * 
 * @param threadHandle [description]
 */
void dragon::lang::internal::JoinThread(void* threadHandle) {
	struct ThreadHandle* handle = (struct ThreadHandle*)threadHandle;

	if (handle->thread_id != GetCurrentThreadId()) {
	    WaitForSingleObject(handle->thread, INFINITE);
	}
}

/**
 * yield the thread
 * 
 * @param threadHandle [description]
 */
void dragon::lang::internal::YieldThread() {
	Sleep(0);
}

/**
 * close the thread
 * 
 * @param threadHandle [description]
 */
void dragon::lang::internal::CloseThread(void* threadHandle) {
	struct ThreadHandle* handle = (struct ThreadHandle*)threadHandle;

  	if (handle->thread != kNoThread) {
  		CloseHandle(handle->thread);
  	}

  	SafeFree(handle);	
}

void dragon::lang::internal::SleepThread(long millisecs) {
    Sleep(millisecs);
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Atomic Operation
//
 
bool dragon::lang::internal::AtomicCompareAndSwap(DRAGON_ATOMICS_VOLATILE dg_int *value, dg_int valueToCompare, dg_int newValue) {
	return InterlockedCompareExchange((volatile long*)value, (long)newValue, (long)valueToCompare);
}

bool dragon::lang::internal::AtomicCompareAndSwap(DRAGON_ATOMICS_VOLATILE dg_long *value, dg_long valueToCompare, dg_long newValue) {
	return InterlockedCompareExchange64((volatile __int64*)value, (__int64)newValue, (__int64)valueToCompare);
}
