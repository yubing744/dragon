#include "io.h"

#ifndef IO_Appendable_H 
#define IO_Appendable_H
#pragma once

BeginPackage2(ProjectName,io)

interface _DragonExport Appendable
{
public:
	virtual Appendable* append(Char c) throw(IOException) =0;
	virtual Appendable* append(CharSequence* csq) throw(IOException) =0;
	virtual Appendable* append(CharSequence* csq,int start,int end) throw(IOException) =0;
};

EndPackage2

#endif