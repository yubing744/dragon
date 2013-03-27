#include "io.h"

#ifndef IO_UnsupportedEncodingException_H 
#define IO_UnsupportedEncodingException_H
#pragma once

#include "IOException.h"

BeginPackage2(ProjectName,io)

class _DragonExport UnsupportedEncodingException :public IOException
{
public:
	UnsupportedEncodingException();
	UnsupportedEncodingException(const Char* message);
};

EndPackage2

#endif