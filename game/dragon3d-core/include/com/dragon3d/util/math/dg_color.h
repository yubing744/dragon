#pragma once

#include "dg_config.h"

#if !defined(DG_COLOR)
#define DG_COLOR


class DGColor
{
public:
	DGColor(void);

	DGColor(DGfloat r, DGfloat g, DGfloat b);
	DGColor(DGfloat r, DGfloat g, DGfloat b, DGfloat a);

	DGColor(DGuint r, DGuint g, DGuint b);
	DGColor(DGuint r, DGuint g, DGuint b, DGuint a);

	DGColor(DGubyte r, DGubyte g, DGubyte b);
	DGColor(DGubyte r, DGubyte g, DGubyte b, DGubyte a);

	DGColor(const char* hexColor);

public:
	DGfloat r;
	DGfloat g;
	DGfloat b;
	
	DGfloat a; //透明度

public:
	static DGColor hexColor(const char* hexColor);

public:
	static const DGColor white;
	static const DGColor red;
	static const DGColor green;
	static const DGColor blue;
	static const DGColor black;
};

#endif