#pragma once

#include "dg_config.h"

#if !defined(DG_MATRIX4X4)
#define DG_MATRIX4X4

#include "dg_mathf.h"
#include <string>
using std::string;

class DGMatrix4x4
{
public:
	DGMatrix4x4(void);
    DGMatrix4x4(DGfloat* f4x4);
    DGMatrix4x4(
        DGfloat x11, DGfloat x12, DGfloat x13, DGfloat x14,
        DGfloat x21, DGfloat x22, DGfloat x23, DGfloat x24,
        DGfloat x31, DGfloat x32, DGfloat x33, DGfloat x34,
        DGfloat x41, DGfloat x42, DGfloat x43, DGfloat x44
    );

public:
	void identity();
	DGMatrix4x4 multiply(const DGMatrix4x4& matrix);
	DGboolean inverse();

	string toString();

public:
	static DGMatrix4x4 Multiply(const DGMatrix4x4& matrixA, const DGMatrix4x4& matrixB);

public:
    const static DGMatrix4x4 IDENTITY;

public:
	DGfloat m[4][4];
};

#endif