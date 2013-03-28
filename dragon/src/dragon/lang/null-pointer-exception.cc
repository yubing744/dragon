#include "NullPointerException.h"

Import ProjectName::lang;

NullPointerException::NullPointerException()
{
	mMsg=new String(L"NullPointerException");
	mpCause=null;
}

NullPointerException::NullPointerException(const Char* message)
{
	mMsg=new String(message);
	mpCause=null;
}

Class<Object>* NullPointerException::getClass()
{
	return (Class<Object>*)new Class<NullPointerException>();
}