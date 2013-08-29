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

/*
const int SINGLE_MEMFUNCPTR_SIZE = sizeof(void (detail::GenericClass::*)());

template <int N>
struct GenericMemFuncX {
  template <class GenericMemFuncType>
  inline static detail::GenericClass *Convert(void* pthis, void* function_to_bind, 
    GenericMemFuncType &bound_func) { 
    // Unsupported member function type -- force a compile failure.
      // (it's illegal to have a array with negative size).
    typedef char ERROR_Unsupported_member_function_pointer_on_this_compiler[N-100];
    return 0; 
  }
};

template <>
struct GenericMemFuncX<SINGLE_MEMFUNCPTR_SIZE> {
  template <class GenericMemFuncType>
  inline static detail::GenericClass *Convert(void* pthis, void* function_to_bind, 
    GenericMemFuncType &bound_func) { 
    
    union {
      GenericMemFuncType func;
      struct {
        union {
          void* __pfn;
          long int __vtable_index;
        } t;
        long int __delta;
      } s;
    } u;

    typedef char ERROR_Unsupported_member_function_pointer_on_this_compiler[sizeof(u.func)==sizeof(u.s) ? 1 : -1];

    u.s.t.__pfn = function_to_bind;
    u.s.__delta = 0;

    bound_func = u.func;

    return (detail::GenericClass*)pthis;
  }
};

template < class GenericMemFunc, class StaticFuncPtr, class UnvoidStaticFuncPtr>
class Invoker : public DelegateMemento {
public:
    inline void bindmemfunc(void *pthis, void* function_to_bind) {
        m_pthis= GenericMemFuncX<SINGLE_MEMFUNCPTR_SIZE>::Convert(pthis, function_to_bind, m_pFunction);
    }

    // These functions are required for invoking the stored function
    inline detail::GenericClass *GetInvokerThis() const { return m_pthis; }
    inline GenericMemFunc GetInvokerMemPtr() const { return reinterpret_cast<GenericMemFunc>(m_pFunction); }
};

template<class RetType>
RetType Invoke(void* pthis, void* func) {
    typedef RetType (detail::GenericClass::*GenericMemFn)();
    
    typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
    typedef DesiredRetType (*StaticFunctionPtr)();
    typedef RetType (*UnvoidStaticFunctionPtr)();

    typedef Invoker<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> InvokerType;
    InvokerType invoker;
    invoker.bindmemfunc(pthis, func);

    detail::GenericClass* gcThis = invoker.GetInvokerThis();
    GenericMemFn gmf = invoker.GetInvokerMemPtr();

    return (gcThis->*gmf)();
}

template<class Param1, class RetType>
RetType Invoke(void* pthis, void* func, Param1 p1) {
    typedef typename detail::DefaultVoidToVoid<RetType>::type DesiredRetType;
    
    typedef RetType (detail::GenericClass::*GenericMemFn)(Param1 p1);
    typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1);
    typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1);

    typedef Invoker<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> InvokerType;
    InvokerType invoker;
    invoker.bindmemfunc(pthis, func);

    detail::GenericClass* gcThis = invoker.GetInvokerThis();
    GenericMemFn gmf = invoker.GetInvokerMemPtr();

    return (gcThis->*gmf)(p1);
}
*/


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

/**
 * Invoke a object's member method
 * 
 * @param p    the object's adress
 * @param func the function pointer of member method
 * @param argv args
 * @param argc args count
 */
//_DragonExport void* InvokeV(void* p, Func_FarProc func, ...);



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


/*
const int kMaxInt = 0x7FFFFFFF;
const int kMinInt = -kMaxInt - 1;

// A macro to disallow the evil copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName)      \
  TypeName(const TypeName&);                    \
  void operator=(const TypeName&)

// ----------------------------------------------------------------------------
// Copyright 2012 the V8 project authors. All rights reserved.
//
// Thread
//
// Thread objects are used for creating and running threads. When the start()
// method is called the new thread starts running the run() method in the new
// thread. The Thread object should not be deallocated before the thread has
// terminated.

class Thread {
 public:
  // Opaque data type for thread-local storage keys.
  // LOCAL_STORAGE_KEY_MIN_VALUE and LOCAL_STORAGE_KEY_MAX_VALUE are specified
  // to ensure that enumeration type has correct value range (see Issue 830 for
  // more details).
  enum LocalStorageKey {
    LOCAL_STORAGE_KEY_MIN_VALUE = kMinInt,
    LOCAL_STORAGE_KEY_MAX_VALUE = kMaxInt
  };

  class Options {
   public:
    Options() : name_("dragon:<unknown>"), stack_size_(0) {}
    Options(const char* name, int stack_size = 0)
        : name_(name), stack_size_(stack_size) {}

    const char* name() const { return name_; }
    int stack_size() const { return stack_size_; }

   private:
    const char* name_;
    int stack_size_;
  };

  // Create new thread.
  explicit Thread(const Options& options);
  virtual ~Thread();

  // Start new thread by calling the Run() method in the new thread.
  void Start();

  // Wait until thread terminates.
  void Join();

  inline const char* name() const {
    return name_;
  }

  // Abstract method for run handler.
  virtual void Run() = 0;

  // Thread-local storage.
  static LocalStorageKey CreateThreadLocalKey();
  static void DeleteThreadLocalKey(LocalStorageKey key);
  static void* GetThreadLocal(LocalStorageKey key);
  static int GetThreadLocalInt(LocalStorageKey key) {
    return static_cast<int>(reinterpret_cast<intptr_t>(GetThreadLocal(key)));
  }
  static void SetThreadLocal(LocalStorageKey key, void* value);
  static void SetThreadLocalInt(LocalStorageKey key, int value) {
    SetThreadLocal(key, reinterpret_cast<void*>(static_cast<intptr_t>(value)));
  }
  static bool HasThreadLocal(LocalStorageKey key) {
    return GetThreadLocal(key) != NULL;
  }

#ifdef FAST_TLS_SUPPORTED
  static inline void* GetExistingThreadLocal(LocalStorageKey key) {
    void* result = reinterpret_cast<void*>(
        InternalGetExistingThreadLocal(static_cast<intptr_t>(key)));
    ASSERT(result == GetThreadLocal(key));
    return result;
  }
#else
  static inline void* GetExistingThreadLocal(LocalStorageKey key) {
    return GetThreadLocal(key);
  }
#endif

  // A hint to the scheduler to let another thread run.
  static void YieldCPU();


  // The thread name length is limited to 16 based on Linux's implementation of
  // prctl().
  static const int kMaxThreadNameLength = 16;

  class PlatformData;
  PlatformData* data() { return data_; }

 private:
  void set_name(const char* name);

  PlatformData* data_;

  char name_[kMaxThreadNameLength];
  int stack_size_;

  DISALLOW_COPY_AND_ASSIGN(Thread);
};
*/

EndPackage3//(dragon, lang, internal)

#endif//PLATFORM_Internal_Lang_Dragon_H
