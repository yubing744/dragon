#include "lang.h"
#include "IndexOutOfBoundsException.h"

#if !defined(Lang_CharSequence_H)
#define Lang_CharSequence_H
#pragma once

BeginPackage2(ProjectName,lang)

interface _DragonExport CharSequence
{
public:
	virtual int length()=0;
	virtual Char charAt(int index)=0;
	virtual CharSequence* subSequence(int start,int end) throw(IndexOutOfBoundsException) =0;
	virtual String toString() =0;

};

EndPackage2

#endif