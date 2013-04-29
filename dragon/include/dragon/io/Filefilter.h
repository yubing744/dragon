#include "io.h"

#ifndef IO_FileFilter_H 
#define IO_FileFilter_H
#pragma once

BeginPackage2(ProjectName,io)

interface _DragonExport FileFilter
{
public:
	virtual bool accept(File pathname) =0;
};

EndPackage2

#endif