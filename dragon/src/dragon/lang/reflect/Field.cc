#include "Field.h"

Import Reflect;


Field::Field(String name,String type)
{
	this->name=name;
	this->type=type;
}

void Field::setName(String name)
{
	this->name=name;
}

String Field::getName()
{
	 return this->name;
}

void Field::setType(String type)
{
	this->type=type;
}

String Field::getType()
{
	return this->type;
}
