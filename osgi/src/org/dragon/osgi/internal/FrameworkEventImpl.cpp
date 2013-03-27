#include "FrameworkEventImpl.h"

Import OSGIInternal;

FrameworkEventImpl::FrameworkEventImpl(){}


FrameworkEventImpl::FrameworkEventImpl(int type, P<Bundle> bundle, String message, P<Throwable> throwable)
{
	this->bundle = bundle;
	this->throwable = throwable;
	this->type = type;
	this->message = message;
}

FrameworkEvent::TYPE FrameworkEventImpl::getType()
{
	return FrameworkEvent::TYPE::STARTED;
}

String FrameworkEventImpl::getMessage()
{
	return this->message;
}

P<Throwable> FrameworkEventImpl::getThrowable()
{
	return this->throwable;
}

P<Bundle> FrameworkEventImpl::getBundle()
{
	return this->bundle;
}