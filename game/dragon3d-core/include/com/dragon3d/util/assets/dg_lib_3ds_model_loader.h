#pragma once

#if !defined(DG_LIB_3DS_MODEL_LOADER)
#define DG_LIB_3DS_MODEL_LOADER

#include "dg_game.h"
#include "dg_texture.h"
#include "dg_material.h"
#include "dg_model_loader.h"

#include <map>
#include <string>

using std::map;
using std::string;


class DGLib3DSModelLoader
	:public DGModelLoader
{
public:
	DGLib3DSModelLoader(void);
	virtual ~DGLib3DSModelLoader(void);

public:
	virtual DGboolean loadModel(char *strFileName, DGModel* outModel);

private:
	DGboolean loadModel(DGResource* res, DGModel* outModel);

public:
	static DGLog* LOG;
};

#endif