#include "NumberFormatException.h"

Import ProjectName::lang;

NumberFormatException::NumberFormatException()
{
	mMsg=new String(L"NumberFormatException");
	mpCause=null;
}

NumberFormatException::NumberFormatException(String& message)
{
	mMsg=new String(message);
	mpCause=null;
}