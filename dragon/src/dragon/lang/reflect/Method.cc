#include "Method.h"

Import Reflect;

Method::Method():self(null){}

Method::operator const Char*()
{
	return this->getFullName().toCharArray();
}

void Method::setPackageName(String packageName)
{
	this->packageName=packageName;
}

void Method::setClassName(String className)
{
	this->className=className;
}
void Method::setName(String name)
{
	this->name=name;
}

void Method::setParameterTypes(Array<String>* parameterTypes)
{
	this->parameterTypes=parameterTypes;
}

void Method::build()
{
	String method;

	method.append(this->packageName);
	method.append(L"::");
	method.append(this->className);
	method.append(L"::");
	method.append(this->name);
	method.append(L"(");

	int len=this->parameterTypes->size();
	for(int i=0;i<len-1;i++)
	{
		method.append(this->parameterTypes->get(i));
		method.append(L",");
	}

	if(len>0)
	{
		method.append(this->parameterTypes->get(len-1));
		method.append(L")");
	}
	else
	{
		method.append(L"void)");
	}

	this->fullName=method;
}

void Method::setFullName(String fullName)
{
	this->fullName=fullName;
}

void Method::setProcAddress(FARPROC procAddress)
{
	this->procAddress=procAddress;
}

FARPROC Method::getProcAddress()
{
	return this->procAddress;
}

String Method::getFullName()
{
	if(this->fullName.equals(L""))
	{
		this->build();
	}

	return this->fullName;
}

void Method::setThis(void* base)
{
	this->self=base;
}

void* Method::getThis()
{
	return this->self;
}

void* Method::invoke()
{
	if(self==null)
	{
		Method0 method=(Method0)this->procAddress;
		return method();
	}

	return invoke(self);
}

void* Method::invoke(void* pThis)
{
	Method1 method=(Method1)this->procAddress;
	return method(pThis);
}

void* Method::invoke(void* pThis,Array<void*>& args)
{
	int argsNum=args.size()>=6?6:args.size();

	if(argsNum==1)
	{
		AgrsMethod1 method1=(AgrsMethod1)this->procAddress;
		return method1(pThis,args[0]);
	}
	else if(argsNum==2)
	{
		AgrsMethod2 method2=(AgrsMethod2)this->procAddress;
		return method2(pThis,args[0],args[1]);
	}
	else if(argsNum==3)
	{
		AgrsMethod3 method3=(AgrsMethod3)this->procAddress;
		return method3(pThis,args[0],args[1],args[2]);
	}

	return null;
}