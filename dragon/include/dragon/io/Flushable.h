#include "io.h"

#ifndef IO_Flushable_H 
#define IO_Flushable_H
#pragma once

BeginPackage2(ProjectName,io)
 
interface _DragonExport Flushable
{
public:
	virtual void flush() throw(IOException) =0;
};

EndPackage2

#endif