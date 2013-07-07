#pragma once

#include "dg_config.h"

#if !defined(DG_Script_Behaviour)
#define DG_Script_Behaviour

#include "dg_behaviour.h"

class DGScriptBehaviour
	:public DGBehaviour
{
public:
	DGScriptBehaviour(void);
	~DGScriptBehaviour(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
    virtual void start();

private:
	static DGLog* LOG;
};

#endif