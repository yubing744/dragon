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

#include "platform.h"

Import dragon::lang::internal;

/*
// ----------------------------------------------------------------------------
// Some Help Func
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


void* Invoke(void* p, Func_FarProc func,...)
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
