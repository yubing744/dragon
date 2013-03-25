#include "IndexOutOfBoundsException.h"

Import ProjectName::lang;

IndexOutOfBoundsException::IndexOutOfBoundsException()
{
	mMsg=new String(L"IndexOutOfBoundsException");
	mpCause=null;
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const Char* message)
{
	mMsg=new String(message);
	mpCause=null;
}
