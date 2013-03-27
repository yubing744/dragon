#include "BundleException.h"

Import dragon::lang;
Import dragon::io;
Import OSGIFramework;

BundleException::BundleException()
{
	mMsg=new String(L"BundleException");
}

BundleException::BundleException(const Char* message)
{
	mMsg=new String(message);
}