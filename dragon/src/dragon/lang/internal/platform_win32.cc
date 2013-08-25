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

ParamInfo::ParamInfo(double doubleVal)
    :category(CATEGORY_SSE), typeName("double"), size(sizeof(double))
{
	double* buf = (double*)malloc(sizeof(double));
	*buf = doubleVal;
    this->value = buf;
}

ParamInfo::~ParamInfo(){
	if (this->size > CPU_BYTE_LEN) {
		//SafeFree(this->value);
	}
}

void ReturnInfo::setValue(double doubleVal) {
	double* buf = (double*)malloc(sizeof(double));
	*buf = doubleVal;
    this->value = buf;
}


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


// ----------------------------------------------------------------------------
// Some Help Func
/*
void* Invoke(void* p,Func_FarProc func, TypeInfo *argv, int argc)
{   
	DWORD result;
	DWORD argSize,tSize,sumSize=0;
	TypeInfo arg;

	//push arg into stack
	for(int i=argc-1;i>=0;i--)
	{
		arg=argv[i];
		argSize=arg.typeSize;
		void* value=arg.pValue;

		sumSize+=argSize;
		tSize=argSize/4;

		__asm{
			mov			eax,argSize;
			sub         esp,eax;

			mov         ecx,tSize;
			mov         esi,value;
			mov         edi,esp;
			rep movs    dword ptr es:[edi],dword ptr [esi];
		}

	}

	//call object p's method func
	__asm{
			mov			ecx,p; 
			call		func;
			mov         result,eax;
	}

	if(p==null)
	{
		__asm{
			mov			eax,sumSize;
			add         esp,eax;
		}		
	}

	return (void*)result;
} 


void* Invoke(void* p, Func_FarProc func, ...)
{
	DWORD result;

	va_list ap;
	va_start(ap,func);

	__asm{
		mov			ebx,esp;
		sub         esp,0x100;

		mov         ecx,0x40;
		mov         esi,ap;
		mov         edi,esp;
		rep movs    dword ptr es:[edi],dword ptr [esi];

		mov			ecx,p; 
		call		func;
		mov         result,eax;

		mov			esp,ebx;
	}

	return (void*)result;
}
*/