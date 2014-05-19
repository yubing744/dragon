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

#ifndef Object_Lang_Dragon_H
#define Object_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/reflect/Type.h>

BeginPackage2(dragon, lang)

class Class;
class String;

Import dragon::lang::reflect;

/**
 * Class Object is the root of the class hierarchy. Every class has Object as a superclass. 
 * All objects, including arrays, implement the methods of this class. 
 */
class _DragonExport Object {
public:
	Object();
	virtual ~Object();

public:
	/**
	 * Creates and returns a copy of this object. 
	 * 
	 * @return [description]
	 */
	virtual Object* clone() const;

	/**
	 * Indicates whether some other object is "equal to" this one.
	 * 
	 * @param  obj [description]
	 * @return     [description]
	 */
	virtual bool equals(const Object* obj);

	/**
	 * Returns a hash code value for the object. This method is supported for the benefit 
	 * of hashtables such as those provided by dragon.util.Hashtable. 
	 * @return [description]
	 */
	virtual int hashCode();

	/**
	 * Returns a string representation of the object. 
	 * 
	 * @return [description]
	 */
	virtual String* toString() const;

	/**
	 * Returns the runtime class of this Object. 
	 * 
	 * @return [description]
	 */
	virtual const Class* getClass() const;

public:
	/**
	 * Causes the current thread to wait until another thread invokes the notify() method 
	 * or the notifyAll() method for this object. In other words, this method behaves exactly
	 * as if it simply performs the call wait(0). 
	 * 
	 */
	virtual void wait();

	/**
	 * Causes the current thread to wait until either another thread invokes the notify() 
	 * method or the notifyAll() method for this object, or a specified amount of time has elapsed. 
	 * 
	 * @param timeout [description]
	 */
	virtual void wait(long timeout);

	/**
	 * Wakes up a single thread that is waiting on this object's monitor. If any threads are waiting 
	 * on this object, one of them is chosen to be awakened. The choice is arbitrary and occurs at 
	 * the discretion of the implementation. A thread waits on an object's monitor by calling one of 
	 * the wait methods. 
	 * 
	 */
	virtual void notify();

	/**
	 * Wakes up all threads that are waiting on this object's monitor. A thread waits on an object's 
	 * monitor by calling one of the wait methods. 
	 * 
	 */
	virtual void notifyAll();

public: // reference countting
	/**
	 * retain the reference count
	 */
    virtual Object* retain();

    /**
     * reduce the reference count, and release object when refCount == 0
     */
	virtual void release();

	/**
	 * get the current reference count
	 * 
	 * @return [description]
	 */
	virtual int getRefCount();

protected:
	/**
	 * Called by the garbage collector on an object when garbage collection determines that there 
	 * are no more references to the object. A subclass overrides the finalize method to dispose of 
	 * system resources or to perform other cleanup. 
	 */
	virtual void finalize();

// -----------------------------------------
private:
	void* getSemaphore();

private:
	
	/**
	 * the handle of semaphore.
	 */
	DRAGON_ALIGN(4) void* semaphoreHandle;

	/**
	 * the reference count of this object
	 */
	DRAGON_ALIGN(4) dg_int refCount;

	/**
	 * the class of object
	 */
	DRAGON_ALIGN(4) Class* clazz;
};


template<class T>
inline T* Clone(T* type) {
    int size = sizeof(T);
    T* newObj = (T*)malloc(size);
    memcpy(newObj, type, size);

    return newObj;
}

EndPackage2//(dragon, lang)

#endif//Object_Lang_Dragon_H

