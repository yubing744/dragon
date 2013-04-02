#include "io.h"

#ifndef IO_IOException_H 
#define IO_IOException_H
#pragma once

BeginPackageIO

class _DragonExport IOException :public Exception
{
public:
	IOException();
	IOException(const Char* message);
};

EndPackageIO

#endif