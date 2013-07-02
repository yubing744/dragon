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

BeginPackage2(dragon, lang)

template<class T>
class Array {
public:
	Array() {
		this->count = 0;
		this->data = null;
		this->myData = dg_true;
	};

	Array(dg_int count) {
		this->count = count;
		this->data = new T[count];
		this->myData = dg_true;
	};

	Array(const Array& arr) {
		this->count = arr.count;
		this->data = arr.data;
		this->myData = dg_false;
	};

	Array(const T* data, dg_int count) {
		this->count = count;
		this->data = const_cast<T*>(data);
		this->myData = dg_false;
	};


	~Array() {
		tryRelease();
	};

public:
	Array& operator=(const Array& arr) {
		tryRelease();

		this->count = arr.count;
		this->data = arr.data;
		this->myData = dg_false;

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
	const T& get(dg_int index) const {
		return this->data[index];
	};

	void set(dg_int index, const T& t) {
		this->data[index] = t;
	};

	dg_int size() {
		return this->count;
	};

	dg_int length() {
		return this->count;
	};

	const T* raw() const {
		return this->data;
	};

	void release() {
		SafeDeleteArray(this->data);
		this->count = 0;
	}

private:
	void tryRelease() {
		if(this->myData) {
			this->release();
		}
	}

private:
	dg_boolean myData;
	dg_int count;
	T* data;
};

EndPackage2//(dragon, lang)

#endif//Array_Lang_Dragon_H