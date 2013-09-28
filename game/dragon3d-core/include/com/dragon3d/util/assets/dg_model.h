#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#include "dg_mesh.h"
#include "dg_material.h"
#include "dg_matrix4x4.h"

#if !defined(DG_MODEL)
#define DG_MODEL

class DGModel : public DGGameObject
{
public:
	DGModel();
	virtual ~DGModel(void);

public:
	virtual void init(DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
	virtual void addPart(DGMesh* mesh, DGMaterial* material);


private:
	static DGLog* LOG;
};

#endif
