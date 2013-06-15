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

#ifndef Array_Lang_H
#define Array_Lang_H

#include <dragon/config.h>

BeginPackage2(dragon, lang)

template<class T>
class Array
{
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


	Array& operator=(const Array& arr) {
		tryRelease();

		this->count = arr.count;
		this->data = arr.data;
		this->myData = dg_false;

		return *this;
	};

	const T& operator[](dg_int index) {
		return this->get(index);
	};

	const T& get(dg_int index) {
		if(index >=0 && index < this->count) {
			return data[index];
		} 

		return T();
	};

	void set(dg_int index, const T& t) {
		if(index>=0 && index<this->count) {
			this->data[index] = t;
		}
	};

	dg_int size() {
		return this->count;
	};

	dg_int length() {
		return this->count;
	};

	const T* raw() {
		return this->data;
	};

private:
	void tryRelease() {
		if(this->data!=null && this->myData) {
			delete[] this->data;
		}
	}

private:
	dg_boolean myData;
	dg_int count;
	T* data;
};

EndPackage2//(dragon, lang)

#endif//Array_Lang_H