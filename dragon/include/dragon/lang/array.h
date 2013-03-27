#include "lang.h"

#if !defined(Lang_Array_H)
#define Lang_Array_H
#pragma once

BeginPackage2(ProjectName,lang)

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

EndPackage2

#endif