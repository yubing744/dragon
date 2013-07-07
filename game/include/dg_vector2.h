#pragma once

#include "dg_config.h"

#if !defined(DG_VECTOR2)
#define DG_VECTOR2

#include <string>
using std::string;

class DGVector2
{
public:
    DGVector2(void);
    DGVector2(DGfloat x, DGfloat y);

public:
	string toString();

public:
	DGfloat x;
	DGfloat y;
};

#endif