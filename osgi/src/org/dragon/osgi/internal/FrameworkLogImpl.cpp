#include "FrameworkLogImpl.h"

Import OSGIInternal;

FrameworkLogImpl::FrameworkLogImpl()
{
	this->level = WARN;
};

FrameworkLogImpl::FrameworkLogImpl(P<Framework> framework)
{
	this->framework = framework;
	this->level = WARN;
}

void FrameworkLogImpl::setLevel(int level)
{
	this->level=level;
}

void FrameworkLogImpl::info(String message)
{
	if (this->level >= INFO)
	{
		this->log(String(L"Info: ") + message);
	}
}

void FrameworkLogImpl::debug(String message)
{
	if (this->level >= DEBUG)
	{
		this->log(String(L"Debug: ") + message);
	}
}

void FrameworkLogImpl::warn(String message)
{
	if (this->level >= WARN)
	{
		this->log(String(L"Warning: ") + message);
	}
}

void FrameworkLogImpl::error(String message)
{
	if (this->level >= ERR)
	{
		this->log(String(L"Error: ") + message);
	}
}

void FrameworkLogImpl::log(String message)
{
	wcout<<message<<endl<<endl;
}

void FrameworkLogImpl::setWriter(P<Writer> newWriter, bool append)
{
	if (!append)
	{
		getWriters()->clear();
	}

	getWriters()->add(newWriter);
}

P<List<P<Writer>>> FrameworkLogImpl::getWriters()
{
	if (this->writers == (P<List<P<Writer>>>)null)
		this->writers = new ArrayList<P<Writer>>();

	return this->writers;
}