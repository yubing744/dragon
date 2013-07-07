#pragma once

#include "dg_config.h"

#ifndef DG_RENDERER
#define DG_RENDERER

#include "dg_component.h"

class DGRenderer
	:public DGComponent
{
public:
	DGRenderer(void);
	virtual ~DGRenderer(void);

public:
    virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();
};

#endif