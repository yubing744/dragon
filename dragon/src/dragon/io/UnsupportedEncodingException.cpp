#include "UnsupportedEncodingException.h"

Import ProjectName::lang;
Import ProjectName::io;

UnsupportedEncodingException::UnsupportedEncodingException()
{
	mMsg=new String(L"FileNotFoundException");
}

UnsupportedEncodingException::UnsupportedEncodingException(const Char* message)
{
	mMsg=new String(message);
}