#pragma once

#include "dg_component.h"

#if !defined(DG_BEHAVIOR)
#define DG_BEHAVIOR

class DGBehaviour :
    public DGComponent
{
public:
    DGBehaviour(void);
    virtual ~DGBehaviour(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
    virtual void start();

public:
    DGboolean enabled;
};

#endif