#include "SecurityException.h"

Import ProjectName::lang;

SecurityException::SecurityException(){}
SecurityException::SecurityException(Char* message)
{
	mMsg=new String(message);
}