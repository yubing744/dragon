#include "lang.h"

#ifndef Lang_Object_H
#define Lang_Object_H
#pragma once

BeginPackage2(ProjectName,lang)

class _DragonExport Object
{
	template<class Type>
	friend class Class;

public:
	Object();
	virtual ~Object();

public:
	virtual bool equals(Object* obj);
	virtual int hashCode();
	virtual String toString();
	virtual Class<Object>* getClass();

private:
	virtual void setClass(Class<Object>* clazz);

protected:
	virtual void finalize();

protected:
	P<Class<Object>> clazz;
};

EndPackage2

#endif

