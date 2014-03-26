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

#ifndef Array_Lang_Dragon_H
#define Array_Lang_Dragon_H

#include <stdio.h>

#include <dragon/config.h>
#include <dragon/lang/Object.h>

BeginPackage2(dragon, lang)

template<class T>
class Array {
public:
	Array() {
		this->count = 0;
		this->data = null;
		this->obj = new Object();
	};

	Array(int size) {
		this->count = size;
		this->data = new T[size];
		this->obj = new Object();
	};

	Array(T* data, int count) {
		this->count = count;
		this->data = data;
		this->obj = new Object();
	};

	Array(const Array& arr) {
		this->count = arr.count;
		this->data = arr.data;
		this->obj = null;

		if (arr.obj != null) {
			this->obj = arr.obj; 
			this->obj->retain();
		}
	};

	Array(T* data, int count, bool freeData) {
		this->count = count;
		this->data = data;
		this->obj = null;

		if (freeData) {
			this->obj = new Object();
		} 
	};

	~Array() {
		this->release();
	};

public: // reference countting
	void retain() {
		if (this->obj != null) {
			this->obj->retain();
		}
	}

	void release() {
		if (this->obj != null) {
			if (this->obj->getRefCount() <= 0) {
				SafeDeleteArray(this->data);
			}
			
			this->obj->release();
			this->obj = null;
		}

		this->data = null;
		this->count = 0;
	}

	int getRefCount() {
		if (this->obj != null) {
			return this->obj->getRefCount();
		}

		return 0;
	}

public:
	Array& operator=(const Array& arr) {
		this->release();

		this->count = arr.count;
		this->data = arr.data;

		if (arr.obj != null) {
			this->obj = arr.obj;
			this->obj->retain();
		}

		return *this;
	};

	T& operator[](int index) {
		return this->data[index];
	};

	const T& operator[](int index) const {
		return this->get(index);
	};

	operator const T*() const {
		return this->raw();
	};

public:
	const T& get(int index) const {
		return this->data[index];
	};

	void set(int index, const T& t) {
		this->data[index] = t;
	};

	void add(const T& t) {
		T* tmp = new T[this->count + 1];
		memcpy(tmp, this->data, sizeof(T) * this->count);
		tmp[this->count] = t;
		free(this->data);

		this->data = tmp;
	};

	void add(const T* data, int count) {
		T* tmp = new T[this->count + count];
		memcpy(tmp, this->data, sizeof(T) * this->count);

		for (int i=0; i<count; i++) {
			tmp[this->count + i] = data[i];
		}

		free(this->data);

		this->data = tmp;
	};

	void add(const Array<T>& arr) {
		this->add(arr.raw(), arr.size());
	};

	int size() const {
		return this->count;
	};

	int length() const {
		return this->count;
	};

	const T* raw() const {
		return this->data;
	};

private:
	Object* obj;
	int count;
	T* data;
};

EndPackage2//(dragon, lang)

#endif//Array_Lang_Dragon_H


/*
#ifndef Array_Lang_Dragon_H
#define Array_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/gc/Reference.h>

BeginPackage2(dragon, lang)

Import dragon::lang::gc;

template<class T>
class Array {
public:
	Array() {
		this->count = 0;
		this->data = null;
	};

	Array(int count) {
		this->count = count;

		const T* data = new T[count];
		this->data = Reference<T>(const_cast<T*>(data), DestructorNormal<T>::notDestruct);
	};

	Array(const T* data, int count) {
		this->count = count;
		this->data = Reference<T>(const_cast<T*>(data), DestructorNormal<T>::notDestruct);
	};

	Array(const Array& arr) {
		this->count = arr.count;

		const T* data = arr.data.raw();
		this->data = Reference<T>(const_cast<T*>(data), DestructorNormal<T>::notDestruct);
	};

	Array(const T* data, int count, bool gcData) {
		this->count = count;

		if (gcData) {
			this->data = Reference<T>(const_cast<T*>(data), DestructorNormal<T>::destructArray);
		} else {
			this->data = Reference<T>(const_cast<T*>(data), DestructorNormal<T>::notDestruct);
		}
	};

public:
	Array& operator=(const Array& arr) {
		this->count = arr.count;
		this->data = arr.data;

		return *this;
	};

	T& operator[](dg_int index) {
		return this->data[index];
	};

	const T& operator[](dg_int index) const {
		return this->get(index);
	};

	operator const T*() const {
		return this->raw();
	};

public:
	const T& get(int index) const {
		return this->data[index];
	};

	void set(int index, const T& t) {
		this->data[index] = t;
	};

	int size() const {
		return this->count;
	};

	int length() const {
		return this->count;
	};

	const T* raw() const {
		return this->data.raw();
	};

	void release() {
		const T* data = this->data.raw();
		SafeDeleteArray(data);
	}
private:
	Reference<T> data;
	int count;
};

EndPackage2//(dragon, lang)

#endif//Array_Lang_Dragon_H
*/