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

	int size() {
		return this->count;
	};

	int length() {
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