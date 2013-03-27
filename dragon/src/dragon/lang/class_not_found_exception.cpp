#include "ClassNotFoundException.h"

Import ProjectName::lang;

ClassNotFoundException::ClassNotFoundException()
{
	mMsg=new String(L"ClassNotFoundException");
	mpCause=null;
}

ClassNotFoundException::ClassNotFoundException(String& message)
{
	mMsg=new String(message);
	mpCause=null;
}