#include "Property.h"

Import Reflect;


Property::Property(String name,String type,P<Method> setter,P<Method> getter)
	:Field(name,type)
{
	this->setter=setter;
	this->getter=getter;
}

void Property::setSetter(P<Method> setter)
{
	this->setter=setter;
}

void Property::setGetter(P<Method> getter)
{
	this->getter=getter;
}

P<Method> Property::getGetter()
{
	return this->getter;
}

P<Method> Property::getSetter()
{
	return this->setter;
}
