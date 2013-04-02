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

BeginPackage2(dragon, lang)

template<class T>
class  Array :public Object
{
public:
	Array()
	{
		msize=0;
		data=null;
	};

	Array(int size){
		msize=size;
		data=new T[size];
	};

	Array(const Array& arr)
	{
		msize=arr.msize;
		data=new T[msize];

		for ( int i = 0; i < msize; ++i )
		{
			data[i]=arr.data[i];
		}
	};

	~Array()
	{
		if(data!=null)
		{
			delete[] data;
		}
	};


	Array& operator=(const Array& arr)
	{
		msize=arr.msize;
		data=arr.data;
		return *this;
	};

	T& operator[](int index)
	{
		if(index<msize)
		{
			return data[index];
		}
		return data[msize-1];
	}

	T& get(int index)
	{
		if(index<msize)
		{
			return data[index];
		}
		return data[msize-1];
	}

	void set(int index,const T& t)
	{
		if(index<msize)
		{
			data[index]=t;
		}
	}

	int size()
	{
		return msize;
	}

private:
	int msize;
	T* data;
};

EndPackage2//(dragon, lang)

#endif//Array_Lang_H