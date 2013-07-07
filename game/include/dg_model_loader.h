#pragma once

#include "dg_config.h"

#if !defined(DG_MODEL_LOADER)
#define DG_MODEL_LOADER

#include "dg_model.h"

class DGModelLoader
{
public:
	DGModelLoader(void);
	virtual ~DGModelLoader(void);

public:
	//º”‘ÿƒ£–Õ
	virtual DGboolean loadModel(char *strFileName, DGModel* outModel) = 0;
};

#endif
