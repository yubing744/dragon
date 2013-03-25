#include "lang.h"

#if !defined(Lang_Throwable_H)
#define Lang_Throwable_H
#pragma once

BeginPackage2(ProjectName,lang)

class _DragonExport Throwable :public Object
{
public:
	Throwable();
	Throwable(String& message);
	Throwable(Throwable* cause);
	Throwable(String& message, Throwable* cause);
	virtual ~Throwable();

public:
	virtual String& getMessage();
	virtual String& getLocalizedMessage();
	virtual Throwable* getCause();
	virtual Throwable* initCause(Throwable* cause);
	virtual String toString();
	virtual void printStackTrace();

protected:
	P<String> mMsg;
	Throwable* mpCause;
};

EndPackage2

#endif