#pragma once

#include "dg_config.h"

#if !defined(DG_MATHF)
#define DG_MATHF

class DGMathf
{
public:
	DGMathf(void);

public:
    static DGint Min(DGint x, DGint y) {
        return x > y ? y : x;
    }

public:
	static const DGfloat PI;
	static const DGfloat EPSILON;
};

#endif