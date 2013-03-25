#include "Thread.h"

Import ProjectName::lang;

Thread::Thread()
{
	mpTarget=null;
}

Thread::Thread(Runnable* target)
{
	mpTarget=target;
}

Thread::Thread(String& name)
{
	mpName=&name;
}

Thread::Thread(Runnable* target,String& name)
{
	mpTarget=target;
	mpName=&name;
}

void Thread::run()
{
	

	if(mpTarget!=null)
	{
		//wcout<<L"Thread Begin Run."<<endl;
		mpTarget->run();
	}
	else
	{
		wcout<<L"Default thread runing..."<<endl;
	}
}

void Thread::start()
{
	DWORD dwThreadId, dwThrdParam = 1; 

    mhThread = CreateThread( 
        NULL,							// default security attributes 
        0,								// use default stack size  
		Thread::ThreadFunc,                  // thread function 
        this,							// argument to thread function 
        0,								// use default creation flags 
        &dwThreadId);					// returns the thread identifier 
  
}

DWORD WINAPI Thread::ThreadFunc(LPVOID lpThreadParameter)
{
	PMF pmf=&Thread::run;

	Thread* self=(Thread*)lpThreadParameter;

	(self->*pmf)();

	return 0;
}

void Thread::sleep(long millis)
{
	Sleep(millis);
}