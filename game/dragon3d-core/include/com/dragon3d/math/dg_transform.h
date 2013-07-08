#pragma once

#include "dg_game.h"

#if !defined(DG_TRANSFORM)
#define DG_TRANSFORM

enum DGSpace {
	World,
	Self
};

class DGTransform
{
public:
	DGTransform(void);
	virtual ~DGTransform(void);

public:
    void translate(const DGVector3& translation, DGSpace relativeTo);
    void rotate(const DGVector3& eulerAngles, DGSpace relativeTo);
	void rotate(DGfloat xAngle, DGfloat yAngle, DGfloat zAngle, DGSpace relativeTo);

    void translate(const DGVector3& translation);
    void rotate(const DGVector3& eulerAngles);
	void rotate(DGfloat xAngle, DGfloat yAngle, DGfloat zAngle);

public:
	// transform in world space
	DGVector3 position;
	DGQuaternion rotation;
	DGVector3 scale;

	// transform relative to the parent transform.
	DGVector3 localPosition;
	DGQuaternion localRotation;
	DGVector3 localScale;
};

#endif