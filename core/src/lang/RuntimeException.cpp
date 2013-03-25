#include "RuntimeException.h"

Import ProjectName::lang;

RuntimeException::RuntimeException()
{
	mpCause=null;
}

RuntimeException::RuntimeException(String& message)
{
	Exception::Exception(message);
	mpCause=null;
}

RuntimeException::RuntimeException(Throwable* cause)
{
	Exception::Exception(cause);
	mpCause=cause;
}

RuntimeException::RuntimeException(String& message, Throwable* cause)
{
	Exception::Exception(message,cause);
	mpCause=cause;
} 