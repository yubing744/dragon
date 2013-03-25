#include "UnsupportedOperationException.h"

Import ProjectName::lang;

UnsupportedOperationException::UnsupportedOperationException()
{
	mMsg=new String(L"UnsupportedOperationException");
	mpCause=null;
}

UnsupportedOperationException::UnsupportedOperationException(String& message)
{
	mMsg=new String(message);
	mpCause=null;
}