#include "Object.h"
#include "Class.h"

Import ProjectName::lang;

Object::Object()
{
	this->clazz=null;
}

Object::~Object()
{
	finalize();
}

Class<Object>* Object::getClass()
{
	if(clazz==(P<Class<Object>>)null)
	{
		return new Class<Object>(&typeid(*this));
	}

	return this->clazz;
}

void Object::setClass(Class<Object>* clazz)
{
	this->clazz=clazz;
}

bool Object::equals(Object* obj)
{
	return false;
}

int Object::hashCode()
{
	return  (int)this;
}

String Object::toString()
{
	return String::format(L"@%d",this);
}

void Object::finalize() throw(Throwable)
{
	//if(this->clazz!=null)
	//{
	//	delete this->clazz;
	//}
}