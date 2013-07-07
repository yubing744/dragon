#pragma once

#include "dg_config.h"

#if !defined(DG_MODEL_MANAGER)
#define DG_MODEL_MANAGER

#include "dg_model.h"
#include "dg_model_loader.h"

#include <map>
#include <string>

using std::map;
using std::string;


class DGModelManager
{
public:
	DGModelManager(void);
	virtual ~DGModelManager(void);

public:
	DGModel* loadModel(char* modelFile);

public:
	//注册一个模型加载器
	void registerModelLoader(string extName, DGModelLoader* modelLoader);

public:
	void addDefaultModelLoaders();

private:
	map<string, DGModelLoader*> modelLoaders;

private:
	static DGLog* LOG;
};

#endif
