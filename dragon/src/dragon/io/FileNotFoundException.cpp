#include "FileNotFoundException.h"

Import ProjectName::lang;
Import ProjectName::io;

FileNotFoundException::FileNotFoundException()
{
	mMsg=new String(L"FileNotFoundException");
}

FileNotFoundException::FileNotFoundException(const Char* message)
{
	mMsg=new String(message);
}