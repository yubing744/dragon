#pragma once

#include "dg_config.h"

#if !defined(DG_QUATERNION)
#define DG_QUATERNION

#include <string>
using std::string;

class DGQuaternion
{
public:
	DGQuaternion(void);
	DGQuaternion(DGfloat x, DGfloat y, DGfloat z);
	DGQuaternion(DGfloat x, DGfloat y, DGfloat z, DGfloat w);

public:
	string toString();

public:
	DGfloat x;
	DGfloat y;
	DGfloat z;
	DGfloat w;

public:
	static const DGQuaternion identity;
};

#endif