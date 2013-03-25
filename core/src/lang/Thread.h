#include "lang.h"

#if !defined(Lang_Thread_H)
#define Lang_Thread_H
#pragma once

#include "Runnable.h"
#include "InterruptedException.h"

BeginPackage2(ProjectName,lang)

class _DragonExport Thread :public Object,public Runnable
{

	typedef void (Thread::*PMF)();

public:
	Thread();
	Thread(Runnable* target);
	Thread(String& name);
	Thread(Runnable* target,String& name);

public:
	virtual void run();
	virtual void start();
private:
	static DWORD WINAPI ThreadFunc(LPVOID lpThreadParameter);
public:
	static void sleep(long millis) throw(InterruptedException);
protected:
	Runnable* mpTarget;
	String* mpName;
	HANDLE  mhThread;
};

EndPackage2

#endif