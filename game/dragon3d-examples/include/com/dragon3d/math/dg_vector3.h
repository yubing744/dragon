#pragma once

#include "dg_config.h"

#if !defined(DG_VECTOR3)
#define DG_VECTOR3

#include <string>
using std::string;

class DGVector3
{
public:
	DGVector3(void);
	DGVector3(DGfloat x, DGfloat y, DGfloat z);

public:
	string toString();

public:
	DGfloat x;
	DGfloat y;
	DGfloat z;

public:
	static const DGVector3 zero; //Shorthand for writing Vector3(0, 0, 0)
	static const DGVector3 one; //Shorthand for writing Vector3(1, 1, 1)

	static const DGVector3 forward; //Shorthand for writing Vector3(0, 0, 1)
	static const DGVector3 up; //Shorthand for writing Vector3(0, 1, 0)
	static const DGVector3 right; //Shorthand for writing Vector3(1, 0, 0)
};

//typedef DGVector3 Vector3;

#endif