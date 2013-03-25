#include "io.h"

#ifndef IO_FileNotFoundException_H 
#define IO_FileNotFoundException_H
#pragma once

#include "IOException.h"

BeginPackage2(ProjectName,io)

class _DragonExport FileNotFoundException :public IOException
{
public:
	FileNotFoundException();
	FileNotFoundException(const Char* message);
};

EndPackage2

#endif