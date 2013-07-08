#pragma once

#include "dg_game.h"
#include "dg_object.h"

#if !defined(DG_COMPONENT)
#define DG_COMPONENT

#include <string>
using std::string;

class DGTransform;
class DGGameObject;

class DGComponent
{
public:
	DGComponent(void);
	DGComponent(const char* name);

	virtual ~DGComponent(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

	virtual string getName();
	virtual DGboolean isActive();
	virtual void setActive(DGboolean active);

public:
    DGGameObject* gameObject;
    DGTransform* transform;
	
protected:
	string name;
	DGboolean active;
};

#endif
