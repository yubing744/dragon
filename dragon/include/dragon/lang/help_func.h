#include "lang.h"

#ifndef Lang_HelpFunc_H 
#define Lang_HelpFunc_H
#pragma once

#include "String.h"

BeginPackage2(dragon,lang)

inline int MsgBox(String* msg)
{
	return MessageBox( NULL,*msg,L"Message!", MB_ICONQUESTION|MB_OKCANCEL);
}

inline int MsgBox(const Char* msg)
{
	return MessageBox( NULL,msg,L"Message!", MB_ICONQUESTION|MB_OKCANCEL);
}

inline int MsgBox(const Char* msg,Char* title)
{
	return MessageBox( NULL,msg,title, MB_ICONQUESTION|MB_OKCANCEL);
}

inline int MsgBox(String* msg,String* title)
{
	return MessageBox( NULL,*msg,*title, MB_ICONQUESTION|MB_OKCANCEL);
}


template <typename E, int N>
inline int Lenth(E (&arr)[N]){
    return N;
}     

inline int Lenth(void* p)
{
	int* pSize=(int*)p;
	pSize--;
	return *pSize;
}

template<class Type>
inline bool InstanceOf(Object* pObj)
{
	Type* pType=dynamic_cast<Type*>(pObj);
	return pType?true:false;
}

template<class Type,class E>
inline bool InstanceOf(Collection<E>* pList)
{
	Type* pType=dynamic_cast<Type*>(pList);
	return pType?true:false;
}

template<class Type>
void* ployCast(Type* p)
{
	void* pObj=dynamic_cast<void*>(p);
	if(pObj==null) pObj=p;
	return pObj;
}

struct TypeInfo
{
	TypeInfo(){};

	template<class Type>
	TypeInfo(Type* value)
	{
		this->typeSize=sizeof(Type);
		this->pValue=value;
	};

	TypeInfo(int size,void* value)
	{
		this->typeSize=size;
		this->pValue=value;
	};

	TypeInfo(P<Class<Object>> clazz,void* value)
	{
		this->typeSize=clazz->getSize();
		this->pValue=value;
	};

	int typeSize;
	void* pValue;
};

inline DWORD Invoke(void* p,FARPROC func,TypeInfo *argv,int argc)
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

	return result;
} 


inline DWORD Invoke(void* p,FARPROC func,...)
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

	return result;
}

inline DWORD Invoke(FARPROC func,...)
{
	va_list args;
	va_start(args,func);

	return Invoke(null,func,args);
}


EndPackage2

#endif