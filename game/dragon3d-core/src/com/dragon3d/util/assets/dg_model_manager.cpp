#include "dg_model_manager.h"
#include "dg_3ds_model_loader.h"
#include "dg_lib_3ds_model_loader.h"

DGLog* DGModelManager::LOG = new DGLog("dg_model_manager");

DGModelManager::DGModelManager(void)
{
}


DGModelManager::~DGModelManager(void)
{
}

void DGModelManager::addDefaultModelLoaders(){
	//this->registerModelLoader("obj", new DGObjLoader());
	//this->registerModelLoader("3ds", new DG3DSModelLoader());
	this->registerModelLoader("3ds", new DGLib3DSModelLoader());
}

void DGModelManager::registerModelLoader(string extName, DGModelLoader* modelLoader){
	modelLoaders[extName] = modelLoader;
}

DGModel* DGModelManager::loadModel(char* modelFile){
	string mf = string(modelFile);
	int pos = mf.find_last_of(".", mf.length());
	if (pos != -1) {
		string extName = mf.substr(pos + 1, mf.length() - pos - 1);
		map<string, DGModelLoader*>::iterator iter = modelLoaders.find(extName);
		if (iter != modelLoaders.end()) { 
			DGModelLoader* loader = iter->second;

			DGModel* model = new DGModel();
			loader->loadModel(modelFile, model);
			return model;
		} else {
			LOG->error("not support model with ext name");
			return NULL;
		}
	} else {
		LOG->error("can not found extName of model file");
		return NULL;
	}
}