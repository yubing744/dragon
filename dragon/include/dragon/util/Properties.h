#include "util.h"

#ifndef Util_Properties_H
#define Util_Properties_H
#pragma once


BeginPackage2(dragon,util)

Import dragon::lang;


class _DragonExport Properties:public Object
{
public:
	Properties();

public:
	virtual String getProperty(String key);
	virtual P<List<String>> propertyNames();
	virtual void load(P<Reader> reader) throw(IOException);

private:
	void addEnity(String entity);

private:
	P<Map<String,String>> props;

};

EndPackage2

#endif