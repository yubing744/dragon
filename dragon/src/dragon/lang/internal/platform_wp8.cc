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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
	#include <libloaderapi.h>
	#include <synchapi.h>
	#include <processthreadsapi.h>
#else
	#include <process.h>
	#include <Dbghelp.h>
	#pragma comment(lib,"Dbghelp.lib")
#endif

// ----------------------------------------------------------------
// Private API 
#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP

#define GET_MODULE_HANDLE_EX_FLAG_PIN                 (0x00000001)
#define GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT  (0x00000002)
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS        (0x00000004)

// Hack for Private API
PIMAGE_NT_HEADERS WINAPI ImageNtHeader(PVOID Base) {
	return (PIMAGE_NT_HEADERS)
		((LPBYTE) Base + ((PIMAGE_DOS_HEADER) Base)->e_lfanew);
}

PIMAGE_SECTION_HEADER WINAPI RtlImageRvaToSection( const IMAGE_NT_HEADERS *nt,
                                                   HMODULE module, DWORD_PTR rva ) {
    int i;
    const IMAGE_SECTION_HEADER *sec;

    sec = (const IMAGE_SECTION_HEADER*)((const char*)&nt->OptionalHeader +
                                        nt->FileHeader.SizeOfOptionalHeader);

    for (i = 0; i < nt->FileHeader.NumberOfSections; i++, sec++) {
        if ((sec->VirtualAddress <= rva) && (sec->VirtualAddress + sec->SizeOfRawData > rva))
            return (PIMAGE_SECTION_HEADER)sec;
    }

    return NULL;
}

PVOID WINAPI RtlImageRvaToVa( const IMAGE_NT_HEADERS *nt, HMODULE module,
                              DWORD_PTR rva, IMAGE_SECTION_HEADER **section ) {
    IMAGE_SECTION_HEADER *sec;

    if (section && *section)  /* try this section first */
    {
        sec = *section;
        if ((sec->VirtualAddress <= rva) && (sec->VirtualAddress + sec->SizeOfRawData > rva))
            goto found;
    }

    if (!(sec = RtlImageRvaToSection( nt, module, rva ))) return NULL;

 found:
    if (section) *section = sec;
    return (char *)module + sec->PointerToRawData + (rva - sec->VirtualAddress);
}

PVOID WINAPI ImageDirectoryEntryToDataEx( PVOID base, BOOLEAN image, USHORT dir, PULONG size, PIMAGE_SECTION_HEADER *section ) {
    const IMAGE_NT_HEADERS *nt;
    DWORD_PTR addr;

    *size = 0;
    if (section) *section = NULL;

    if (!(nt = ImageNtHeader( base ))) return NULL;
    if (dir >= nt->OptionalHeader.NumberOfRvaAndSizes) return NULL;
    if (!(addr = nt->OptionalHeader.DataDirectory[dir].VirtualAddress)) return NULL;

    *size = nt->OptionalHeader.DataDirectory[dir].Size;
    if (image || addr < nt->OptionalHeader.SizeOfHeaders) return (char *)base + addr;

    return RtlImageRvaToVa( nt, (HMODULE)base, addr, section );
}

// == Windows API GetProcAddress
void *PeGetProcAddressA(void *Base, LPCSTR Name) {
	DWORD Tmp;

	IMAGE_NT_HEADERS *NT = ImageNtHeader(Base);
	IMAGE_EXPORT_DIRECTORY *Exp = (IMAGE_EXPORT_DIRECTORY*)ImageDirectoryEntryToDataEx(Base, TRUE, IMAGE_DIRECTORY_ENTRY_EXPORT, &Tmp, 0);

	if(Exp==0 || Exp->NumberOfFunctions==0) {
		SetLastError(ERROR_NOT_FOUND);
		return 0;
	}

	DWORD *Names=(DWORD*)(Exp->AddressOfNames+(DWORD_PTR)Base);
	WORD *Ordinals=(WORD*)(Exp->AddressOfNameOrdinals+(DWORD_PTR)Base);
	DWORD *Functions=(DWORD*)(Exp->AddressOfFunctions+(DWORD_PTR)Base);

	FARPROC Ret=0;

	if((DWORD_PTR)Name<65536) {
		if((DWORD_PTR)Name-Exp->Base<Exp->NumberOfFunctions)
			Ret=(FARPROC)(Functions[(DWORD_PTR)Name-Exp->Base]+(DWORD_PTR)Base);
	} else {
		for(DWORD i=0; i<Exp->NumberOfNames && Ret==0; i++) {
			char *Func = (char*)(Names[i]+(DWORD_PTR)Base);
			if(Func && strcmp(Func, Name) == 0)
				Ret=(FARPROC)(Functions[Ordinals[i]]+(DWORD_PTR)Base);
		}
	}

	if(Ret) {
		DWORD ExpStart=NT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress+(DWORD)Base;
		DWORD ExpSize=NT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

		if((DWORD)Ret>=ExpStart && (DWORD)Ret<=ExpStart+ExpSize) {
			// Forwarder
			return 0;
		}

		return Ret;
	}

	return 0;	
}

void* DragonGetProcAddressA(LPCSTR funcName) {
	char *Tmp = (char*)GetTickCount64;
	Tmp =(char*)((~0xFFF)&(DWORD_PTR)Tmp);

	while(Tmp) {
		__try 
		{
			if(Tmp[0]=='M' && Tmp[1]=='Z')
				break;
		} __except(EXCEPTION_EXECUTE_HANDLER) {
		}

		Tmp-=0x1000;
	}

	if(Tmp==0)
		return NULL;

	return PeGetProcAddressA(Tmp, funcName);
}


typedef HMODULE (WINAPI *Func_LoadLibraryExA)(
    _In_ LPCSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags
    );

typedef DWORD (WINAPI *Func_GetModuleFileNameA) (
    _In_opt_ HMODULE hModule,
    _Out_writes_to_(nSize, ((return < nSize) ? (return + 1) : nSize)) LPSTR lpFilename,
    _In_ DWORD nSize
    );

typedef BOOL (WINAPI *Func_GetModuleHandleExA) (
    _In_ DWORD dwFlags,
    _In_opt_ LPCSTR lpModuleName,
    _Out_ HMODULE * phModule
    );

typedef VOID (WINAPI *Func_Sleep) (
    _In_ DWORD dwMilliseconds
    );

typedef char* (*Func_undname)(char*, const char*, int, 
    void* (*)(size_t), void (*)(void*), 
    unsigned short
    );

HMODULE WINAPI LoadLibraryExA(
    _In_ LPCSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags) {
    static Func_LoadLibraryExA funcLoadLibraryExA = NULL;

    if (funcLoadLibraryExA == NULL) {
        funcLoadLibraryExA= (Func_LoadLibraryExA)DragonGetProcAddressA("LoadLibraryExA");
        assert(funcLoadLibraryExA != NULL);
    }

    return funcLoadLibraryExA(lpLibFileName, hFile, dwFlags);
}

HMODULE WINAPI LoadLibraryA(_In_ LPCSTR lpLibFileName) {
	return LoadLibraryExA(lpLibFileName, 0, 1);
}

DWORD WINAPI GetModuleFileNameA(
    _In_opt_ HMODULE hModule,
    _Out_writes_to_(nSize, ((return < nSize) ? (return + 1) : nSize)) LPSTR lpFilename,
    _In_ DWORD nSize) {
    static Func_GetModuleFileNameA funcGetModuleFileNameA = NULL;

    if (funcGetModuleFileNameA == NULL) {
        funcGetModuleFileNameA= (Func_GetModuleFileNameA)DragonGetProcAddressA("GetModuleFileNameA");
        assert(funcGetModuleFileNameA != NULL);
    }

    return funcGetModuleFileNameA(hModule, lpFilename, nSize);
}

BOOL WINAPI GetModuleHandleExA (
    _In_ DWORD dwFlags,
    _In_opt_ LPCSTR lpModuleName,
    _Out_ HMODULE * phModule) {
    static Func_GetModuleHandleExA funcGetModuleHandleExA = NULL;

    if (funcGetModuleHandleExA == NULL) {
        funcGetModuleHandleExA = (Func_GetModuleHandleExA)DragonGetProcAddressA("GetModuleHandleExA");
        assert(funcGetModuleHandleExA != NULL);
    }

    return funcGetModuleHandleExA(dwFlags, lpModuleName, phModule);
}

VOID WINAPI Sleep (_In_ DWORD dwMilliseconds) {
    static Func_Sleep funcSleep = NULL;

    if (funcSleep == NULL) {
        funcSleep = (Func_Sleep)DragonGetProcAddressA("Sleep");
        assert(funcSleep != NULL);
    }

    funcSleep(dwMilliseconds);
}

// -------------------------------------------------------
//  UnDecorateSymbolName
#define UNDNAME_COMPLETE                 (0x0000)  // Enable full undecoration
#define UNDNAME_NO_LEADING_UNDERSCORES   (0x0001)  // Remove leading underscores from MS extended keywords
#define UNDNAME_NO_MS_KEYWORDS           (0x0002)  // Disable expansion of MS extended keywords
#define UNDNAME_NO_FUNCTION_RETURNS      (0x0004)  // Disable expansion of return type for primary declaration
#define UNDNAME_NO_ALLOCATION_MODEL      (0x0008)  // Disable expansion of the declaration model
#define UNDNAME_NO_ALLOCATION_LANGUAGE   (0x0010)  // Disable expansion of the declaration language specifier
#define UNDNAME_NO_MS_THISTYPE           (0x0020)  // NYI Disable expansion of MS keywords on the 'this' type for primary declaration
#define UNDNAME_NO_CV_THISTYPE           (0x0040)  // NYI Disable expansion of CV modifiers on the 'this' type for primary declaration
#define UNDNAME_NO_THISTYPE              (0x0060)  // Disable all modifiers on the 'this' type
#define UNDNAME_NO_ACCESS_SPECIFIERS     (0x0080)  // Disable expansion of access specifiers for members
#define UNDNAME_NO_THROW_SIGNATURES      (0x0100)  // Disable expansion of 'throw-signatures' for functions and pointers to functions
#define UNDNAME_NO_MEMBER_TYPE           (0x0200)  // Disable expansion of 'static' or 'virtual'ness of members
#define UNDNAME_NO_RETURN_UDT_MODEL      (0x0400)  // Disable expansion of MS model for UDT returns
#define UNDNAME_32_BIT_DECODE            (0x0800)  // Undecorate 32-bit decorated names
#define UNDNAME_NAME_ONLY                (0x1000)  // Crack only the name for primary declaration;
                                                                                                   //  return just [scope::]name.  Does expand template params
#define UNDNAME_NO_ARGUMENTS             (0x2000)  // Don't undecorate arguments to function
#define UNDNAME_NO_SPECIAL_SYMS          (0x4000)  // Don't undecorate special names (v-table, vcall, vector xxx, metatype, etc)


static void* und_alloc(size_t len) { return HeapAlloc(GetProcessHeap(), 0, len); }
static void und_free (void* ptr) { HeapFree(GetProcessHeap(), 0, ptr); }

DWORD WINAPI UnDecorateSymbolName(PCSTR DecoratedName, PSTR UnDecoratedName, 
    DWORD UndecoratedLength, DWORD Flags) {
    Func_undname p_undname = NULL;
    static const char szMsvcrt[] = {'m','s','v','c','r','t','.','d','l','l',0};

    HMODULE hMsvcrt = NULL;

    if (!p_undname){
        if (!hMsvcrt) hMsvcrt = LoadLibraryA(szMsvcrt);
        if (hMsvcrt) p_undname = (Func_undname)GetProcAddress(hMsvcrt, "__unDName");
        if (!p_undname) return 0;
    }

    if (!UnDecoratedName) return 0;

    if (!p_undname(UnDecoratedName, DecoratedName, UndecoratedLength, und_alloc, und_free, Flags))
        return 0;

    return strlen(UnDecoratedName);
}

#endif

// ----------------------------------------------------------------


#include <string>
#include <map>

#include <thread> //C++09 header

#include <dragon/lang/internal/platform.h>

Import std;

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
	LPCSTR address = (LPCSTR)&SymTestBean::classLocationFlag;

	// Private API
	if(!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, address, &hSysLib)){
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

static LARGE_INTEGER* frequency = NULL;

// 1s / 10000000
dg_long dragon::lang::internal::GetSystemTime() {
	LARGE_INTEGER currentTime;

	if (frequency == NULL) {
		frequency = new LARGE_INTEGER();

		if (!QueryPerformanceFrequency(frequency)) {
		    assert(FALSE);
		}
	}

    if (!QueryPerformanceCounter(&currentTime)) {
        assert(FALSE);
    }

    return static_cast<dg_long>(static_cast<double>(currentTime.QuadPart) * 1000000/ static_cast<double>(frequency->QuadPart));
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
	
	#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
		InitializeCriticalSectionEx(pcs, 1, CRITICAL_SECTION_NO_DEBUG_INFO);
	#else
    	InitializeCriticalSection(pcs);
    #endif

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

	#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
		*psem = ::CreateSemaphoreExW(NULL, count, 0x7fffffff, NULL, 0, SYNCHRONIZE);
	#else
    	*psem = ::CreateSemaphoreA(NULL, count, 0x7fffffff, NULL);
    #endif

    return psem;
}

/**
 * wait
 * 
 * @param semaphore [description]
 */
void dragon::lang::internal::WaitSemaphore(void* semaphore) {
	HANDLE* psem = (HANDLE*)semaphore;
	
	#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
		WaitForSingleObjectEx(*psem, INFINITE, TRUE);
	#else
    	WaitForSingleObject(*psem, INFINITE);
    #endif
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

	#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
		return WaitForSingleObjectEx(*psem, millis_timeout, TRUE) != WAIT_TIMEOUT;
	#else
    	return WaitForSingleObject(*psem, millis_timeout) != WAIT_TIMEOUT;
    #endif
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
  	DWORD thread_id;
} _ThreadHandle;

// thread entry func
typedef unsigned int (__stdcall *ThreadEntryFunc)(void *);
typedef unsigned int (__cdecl *cppThreadEntryFunc)();

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

    #if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
    	cppThreadEntryFunc func = void_cast<cppThreadEntryFunc>(entryFunc);
		std::thread thr(func);
    #else
		ThreadEntryFunc func = void_cast<ThreadEntryFunc>(entryFunc);

	  	handle->thread = reinterpret_cast<HANDLE>(
	      _beginthreadex(NULL,
	                     static_cast<unsigned>(stackSize),
	                     func,
	                     target,
	                     0,
	                     &handle->thread_id));
  	#endif

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
	    
	    #if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
			WaitForSingleObjectEx(handle->thread, INFINITE, TRUE);
		#else
	    	WaitForSingleObject(handle->thread, INFINITE);
	    #endif
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

void dragon::lang::internal::GetSysEnvVariable(const char* varName, char* outBuf, size_t size) {
    return GetEnvironmentVariable(varName, outBuf, size);
}