#include "util.h"

#ifndef Util_TemplateType_H
#define Util_TemplateType_H
#pragma once


BeginPackage2(dragon,util)

Import dragon::lang;


class _DragonExport TemplateType:public Object
{
public:
	TemplateType();
	TemplateType(String typeText);

public:
	virtual void parser(String typeText);
	virtual String getRawType();
	virtual String getMainType();
	virtual int getArgsCount();
	virtual P<TemplateType> getArgType(int index);

protected:
	virtual int getNextPos(String& typeText,int posBegin,int posEnd);
	virtual void findArg(String& typeText,int posBegin,int posCurrent,int posComma,int posEnd);

protected:
	String rawType;
	String mainType;
	P<List<P<TemplateType>>> argTypes;
};

EndPackage2

#endif