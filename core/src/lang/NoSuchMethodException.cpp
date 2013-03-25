#include "NoSuchMethodException.h"

Import ProjectName::lang;

NoSuchMethodException::NoSuchMethodException()
{
	mMsg=new String(L"NoSuchMethodException");
	mpCause=null;
}

NoSuchMethodException::NoSuchMethodException(String& message)
{
	mMsg=new String(message);
	mpCause=null;
}