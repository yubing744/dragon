#include "io.h"

#ifndef IO_Closeable_H 
#define IO_Closeable_H
#pragma once

BeginPackage2(ProjectName,io)

interface _DragonExport Closeable
{
public:
	virtual void close() throw(IOException) =0;
};

EndPackage2

#endif