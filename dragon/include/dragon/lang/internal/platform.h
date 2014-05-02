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

#ifndef PLATFORM_Internal_Lang_Dragon_H
#define PLATFORM_Internal_Lang_Dragon_H

#include <dragon/config.h>

#include <stdio.h>
#include <stdarg.h>

#include <map>
#include <vector>
#include <string>
#include <stack>

#include <typeinfo>

#include <FastDelegate.h>
#include <FastDelegateBind.h>

Import std;
Import fastdelegate;

BeginPackage3(dragon, lang, internal)

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Invoke Function by address
// 

template <class OutputClass>
inline OutputClass horrible_void_cast(void* funcPtr){
    const size_t out_size = sizeof(OutputClass);

    detail::horrible_union<OutputClass, char[out_size]> u;
    memcpy(u.in, &funcPtr, out_size);

    return u.out;
}

template <class OutputClass>
inline OutputClass void_cast(void* funcPtr){
    detail::horrible_union<OutputClass, void*> u;
    u.in = funcPtr;
    return u.out;
}

template <class InputClass>
inline void* cast_void(InputClass anyClass){
    detail::horrible_union<void*, InputClass> u;
    u.in = anyClass;
    return u.out;
}

/**
 * Get a type's size
 * 
 * @param  name [description]
 * @return      [description]
 */
_DragonExport size_t GetBasicTypeSize(const char* name);


/**
 * Get Type Category
 */
#define CATEGORY_INTEGER 0
#define CATEGORY_SSE 1
#define CATEGORY_SSEUP 2
#define CATEGORY_X87 3
#define CATEGORY_X87UP 4
#define CATEGORY_COMPLEX_X87 5
#define CATEGORY_NO_CLASS 6
#define CATEGORY_MEMORY 7

_DragonExport int GetBasicTypeCategory(const char* name);


static const size_t CPU_BYTE_LEN = sizeof(void*);

/**
 * param type
 */
class _DragonExport ParamInfo {
public:
    int category; 
    size_t size;
    const char* typeName;
    void* value;

public:
    ParamInfo(bool boolVal) 
      :category(CATEGORY_INTEGER), typeName("bool"), size(sizeof(bool))
    {
        this->value = cast_void<bool>(boolVal);
    }

    ParamInfo(char charVal) 
      :category(CATEGORY_INTEGER), typeName("char"), size(sizeof(char))
    {
        this->value = cast_void<char>(charVal);
    }

    ParamInfo(short shortVal) 
      :category(CATEGORY_INTEGER), typeName("short"), size(sizeof(short))
    {
        this->value = cast_void<short>(shortVal);
    }

    ParamInfo(int intVal)
      :category(CATEGORY_INTEGER), typeName("int"), size(sizeof(int))
    {
        this->value = cast_void<int>(intVal);
    }

        
    ParamInfo(float floatVal)  
      :category(CATEGORY_SSE), typeName("float"), size(sizeof(float))
    {
        this->value = cast_void<float>(floatVal);
    }

    ParamInfo(size_t sizeTVal) 
      :category(CATEGORY_INTEGER), typeName("size_t"), size(sizeof(size_t))
    {
        this->value = cast_void<size_t>(sizeTVal);
    }

    ParamInfo(long longVal);
    ParamInfo(long long llVal);
    ParamInfo(double doubleVal);

    ParamInfo(const char* typeName, void* ptrVal)
      :category(CATEGORY_INTEGER), typeName(typeName), size(sizeof(void*))
    {
        this->value = (void*)ptrVal;
    }

    template<class T>
    ParamInfo(T* ptrVal)
      :category(CATEGORY_INTEGER), typeName(typeid(T*).name()), size(sizeof(T*))
    {
        this->value = (void*)ptrVal;
    }

	  ~ParamInfo();
};

/**
 * return type
 */
class _DragonExport ReturnInfo {
public:
    int category;
    size_t size;
    const char* typeName;
    void* value;

public:
    ReturnInfo(const char* typeName)
      :typeName(typeName), value(NULL)
    {
        this->size = GetBasicTypeSize(this->typeName);
        this->category = GetBasicTypeCategory(this->typeName);
    }

public:
	void setValue(double doubleVal);

	template<class T>
	T getValue() {
		if (sizeof(T) <= CPU_BYTE_LEN) {
			return horrible_void_cast<T>(this->value);
		} else {
			return *(T*)(this->value);
		} 
	}
};

/**
 * Invoke a object's member method
 * 
 * @param p    the object's adress
 * @param func the function pointer of member method
 * @param argv args
 * @param argc args count
 */
_DragonExport void Invoke(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc);

/**
 * Invoke a object's member method
 * 
 * @param p    the object's adress
 * @param func the function pointer of member method
 * @param argv args
 * @param argc args count
 */
_DragonExport void* Invoke(void* pthis, void* func, ParamInfo *argv, int argc);


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Symbol Mangling and Demangle Function
// 

/**
 * lib export class symbol test
 * 
 */
class _DragonExport SymTestBean {
public:
    static dg_int classLocationFlag;

public:
    SymTestBean();
    SymTestBean(dg_int testVal);
    virtual ~SymTestBean();

public: // basic type symbol test
    void test(dg_byte byteVal);
    void test(dg_short shortVal);
    void test(dg_int intVal);
    void test(dg_long longVal);
    void test(dg_float floatVal);
    void test(dg_double doubleVal);

    void test(dg_char charVal);
    void test(dg_boolean booleanVal);

    void test(SymTestBean* bean);

    void test();
public:
    dg_int getTestVal();
    void setTestVal(dg_int val);

private:
    dg_int testVal;
    dg_int testArray[1024];
};

typedef void (SymTestBean::*SymTestBean_TestByte_MemberMethod)(dg_byte);
typedef void (SymTestBean::*SymTestBean_TestShort_MemberMethod)(dg_short);
typedef void (SymTestBean::*SymTestBean_TestInt_MemberMethod)(dg_int);
typedef void (SymTestBean::*SymTestBean_TestLong_MemberMethod)(dg_long);
typedef void (SymTestBean::*SymTestBean_TestFloat_MemberMethod)(dg_float);
typedef void (SymTestBean::*SymTestBean_TestDouble_MemberMethod)(dg_double);
typedef void (SymTestBean::*SymTestBean_TestChar_MemberMethod)(dg_char);
typedef void (SymTestBean::*SymTestBean_TestBoolean_MemberMethod)(dg_boolean);
typedef void (SymTestBean::*SymTestBean_TestObjectPtr_MemberMethod)(SymTestBean*);

typedef void (SymTestBean::*SymTestBean_TestVoid_MemberMethod)();

typedef dg_int (SymTestBean::*SymTestBean_TestGetter_MemberMethod)();
typedef void (SymTestBean::*SymTestBean_TestSetter_MemberMethod)(dg_int);

typedef dg_int (*SymTestBean_TestGetter_MemberMethod2)(void* pthis);

/**
 *  get current lib's path.
 *    
 */
_DragonExport const char* GetLocalLibPath();

/**
 *  get dragon lib's path.
 *    
 */
_DragonExport const char* GetDragonLibPath();

/**
 * search library in Lib Path.
 * 
 * @param  libName [description]
 * @return         [description]
 */
_DragonExport const char* SearchLibraryPathByName(const char* libName);

/**
 * get library path by address.
 * 
 * @param  address [description]
 * @return         [description]
 */
_DragonExport const char* GetLibraryPathByAddress(void* address);

/**
 *  show current lib's laod infomation.
 *    
 */
_DragonExport void ShowLocalLibInfo();

/**
 * mangling the function signature to local symbol
 * 
 * @param funSignature [description]
 * @param localSymbol  [description]
 */
_DragonExport string Mangling(const char* funSignature);

/**
 * demangle a symbol
 * 
 * @param  symbol [description]
 * @return        [description]
 */
_DragonExport char* Demangle(const char* symbol);


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Utils Function
// 

/**
 * split the text by sep.
 * 
 */
static vector<string> Split(const char* text, const char* sep) {
  vector<string> results;

  string src(text);
  string flag(sep);


  size_t from = 0;
  size_t p1 = src.find(flag);

  while (p1 != string::npos) {
    string seg = src.substr(from, p1 - from);
    results.push_back(seg);

    from = p1 + flag.length();
    p1 = src.find(flag, from);
  }

  if (from < src.length()) {
    string last_seg = src.substr(from, src.length());
    results.push_back(last_seg);
  }

  return results;   
}

/**
 * join the vector string into a string
 * 
 * @param  strs [description]
 * @param  sep  [description]
 * @return      [description]
 */
static string Join(vector<string> strs, const char* sep) {
  string results;
  string flag(sep);

  for(size_t i=0; i<strs.size(); i++) {
    results.append(strs[i]);
    results.append(flag);
  }

  if (strs.size() > 0) {
    results = results.substr(0, results.length() - flag.length());
  }

  return results;
}


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Library export Function
// 

/**
 * get a function address by the function signature.
 * 
 * @param libPath   [description]
 * @param libPath   [description]
 * @param signature [description]
 */
_DragonExport void* GetFuncAddress(const char* libPath, const char* signature);

/**
 * get a local dragon lib function address by the function signature.
 * 
 * @param signature [description]
 */
_DragonExport void* GetFuncAddress(const char* signature);


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Time
// 

/**
 * get the system time,  unit  us 
 * 
 * @return [description]
 */
_DragonExport dg_long GetSystemTime();

// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Atomic Operation
// 

/**
 * atomic compare and set new value.
 * 
 * @param  value [description]
 * @param  valueToCompare [description]
 * @param  newValue [description]
 * @return          [description]
 */
_DragonExport bool AtomicCompareAndSwap(DRAGON_ATOMICS_VOLATILE dg_int *value, dg_int valueToCompare, dg_int newValue);
_DragonExport bool AtomicCompareAndSwap(DRAGON_ATOMICS_VOLATILE dg_long *value, dg_long valueToCompare, dg_long newValue);


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
_DragonExport void* InitMutex();

/**
 *  lock the mutex
 * 
 * @return [description]
 */
_DragonExport void LockMutex(void* mutex);

/**
 *  try lock the mutex
 * 
 * @return [description]
 */
_DragonExport bool TryLockMutex(void* mutex);

/**
 *  unlock the mutex
 * 
 * @return [description]
 */
_DragonExport void UnlockMutex(void* mutex);

/**
 * free mutex object
 * 
 * @return [description]
 */
_DragonExport void FreeMutex(void* mutex);


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Semaphore
// 

/**
 * init a mutex object
 * 
 * @param count [description]
 */
_DragonExport void* InitSemaphore(int count);

/**
 * wait
 * 
 * @param semaphore [description]
 */
_DragonExport void WaitSemaphore(void* semaphore);

/**
 * wait with timeout
 * 
 * @param semaphore [description]
 * @param timeout    [description]
 * @return 
 */
_DragonExport bool WaitSemaphore(void* semaphore, int timeout);

/**
 * notify continue
 * 
 * @param semaphore [description]
 */
_DragonExport void SignalSemaphore(void* semaphore);

/**
 * free semaphore
 * 
 * @param semaphore [description]
 */
_DragonExport void FreeSemaphore(void* semaphore);


// -----------------------------------------------------------------------
// Copyright 2013 the dragon project authors. All rights reserved.
// 
// Thread
// 

/**
 * create a new thread, and return thread handle
 *
 * @param stackSize the stack size for thread
 * @param target the target object for invoke method
 * @param entryFunc the entry function for thread
 */
_DragonExport void* CreateThread(int stackSize, void* target, void* entryFunc);

/**
 * join the thread
 * 
 * @param threadHandle [description]
 */
_DragonExport void JoinThread(void* threadHandle);

/**
 * close the thread
 * 
 * @param threadHandle [description]
 */
_DragonExport void CloseThread(void* threadHandle);

/**
 * yield the thread
 * 
 * @param threadHandle [description]
 */
_DragonExport void YieldThread();

/**
 * sleep current thread
 * 
 */
_DragonExport void SleepThread(long millis);


EndPackage3//(dragon, lang, internal)

#endif//PLATFORM_Internal_Lang_Dragon_H
