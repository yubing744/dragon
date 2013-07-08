#pragma once

#include "dg_game.h"
#include "dg_texture.h"

#if !defined(DG_MATERIAL)
#define DG_MATERIAL

#include <string>
using std::string;

class DGMaterial
{
public:
	DGMaterial(void);
	DGMaterial(const DGColor& color);
	DGMaterial(const DGColor& color, DGTexture* mainTexture);

	virtual ~DGMaterial(void);

public:
	string name;
	DGColor color;
	DGTexture* mainTexture;

public:
	const static DGMaterial DEFAULT_MATERIAL;
};

#endif
