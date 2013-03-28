#include "InterruptedException.h"

Import ProjectName::lang;

InterruptedException::InterruptedException()
{
	Exception::Exception();
	mpCause=null;
}

InterruptedException::InterruptedException(String& message)
{
	mMsg=new String(message);
	mpCause=null;
}