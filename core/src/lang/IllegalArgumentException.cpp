#include "IllegalArgumentException.h"

Import ProjectName::lang;

IllegalArgumentException::IllegalArgumentException()
{
	mMsg=new String(L"IllegalArgumentException");
	mpCause=null;
}

IllegalArgumentException::IllegalArgumentException(String& message)
{
	mMsg=new String(message);
	mpCause=null;
}