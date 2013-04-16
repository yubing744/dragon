#include "IOException.h"

Import IO;

IOException::IOException(){}

IOException::IOException(const Char* message)
{
	mMsg=new String(message);
}