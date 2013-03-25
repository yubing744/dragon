#include "Exception.h"

Import ProjectName::lang;

Exception::Exception()
{
	mMsg=new String(L"Exception");
	mpCause=null;
}

Exception::Exception(String& message)
{
	mMsg=new String(message);
	mpCause=null;
}

Exception::Exception(Throwable* cause)
{
	mpCause=cause;
}

Exception::Exception(String& message, Throwable* cause)
{
	mMsg=new String(message);
	mpCause=cause;
} 