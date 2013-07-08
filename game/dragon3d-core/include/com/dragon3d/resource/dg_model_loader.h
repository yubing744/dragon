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
	//樓婥耀倰
	virtual DGboolean loadModel(char *strFileName, DGModel* outModel) = 0;
};

#endif