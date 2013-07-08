#pragma once

#include "dg_config.h"

#if !defined(DG_MESH_RENDERER)
#define DG_MESH_RENDERER

#include "dg_mesh.h"
#include "dg_renderer.h"
#include "dg_material.h"

class DGMeshRenderer :
	public DGRenderer
{
public:
	DGMeshRenderer(void);
	DGMeshRenderer(DGMesh* mesh);
	virtual ~DGMeshRenderer(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
	DGMesh* mesh;
	DGMaterial* material;
};

#endif