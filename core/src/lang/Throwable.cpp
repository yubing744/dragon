#include "Throwable.h"

Import ProjectName::lang;

Throwable::Throwable():mMsg()
{
	mMsg=new String(L"Throwable yubing");
	mpCause=null;
}

Throwable::Throwable(String& message)
{
	mMsg=new String(message);
	mpCause=null;
}

Throwable::Throwable(Throwable* cause)
{
	mMsg=new String();
	mpCause=cause;
}

Throwable::Throwable(String& message, Throwable* cause)
{
	mMsg=&message;
	mpCause=cause;
} 

Throwable::~Throwable()
{
	//SafeDelete(mMsg);
	//SafeDelete(mpCause);
}

String& Throwable::getMessage()
{
	return *mMsg;
}

String& Throwable::getLocalizedMessage()
{
	return *mMsg;
}

Throwable* Throwable::getCause()
{
	return mpCause;
}

Throwable* Throwable::initCause(Throwable* cause)
{
	mpCause=cause;
	return mpCause;
}

String Throwable::toString()
{
	return String::format(L"Msg:,%s",getLocalizedMessage().toCharArray());
}

void Throwable::printStackTrace()
{

}