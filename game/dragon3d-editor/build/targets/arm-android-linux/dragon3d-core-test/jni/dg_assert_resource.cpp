#include "dg_assert_resource.h"

DGLog* DGAssertResource::LOG = new DGLog("dg_assert_resource");

DGAssertResource::DGAssertResource(AAssetManager* mgr, const char* path){
	this->mgr = mgr;
	this->path = path;
	this->asset = NULL;
	this->cursor = 0;
}


DGAssertResource::~DGAssertResource(void){

}


int DGAssertResource::read(void *buffer, size_t size, size_t count){
	int readCount = AAsset_read(asset, buffer, size * count); 
	this->cursor += readCount;
	return readCount;
}

int DGAssertResource::seek(long offset, int fromwhere){
	this->cursor = offset;
	return AAsset_seek(asset, offset, fromwhere);
}

DGuint DGAssertResource::length() {
	return AAsset_getLength(asset);
}

DGboolean DGAssertResource::open(){
	LOG->debug("try open file %s", path.data());
	
	if ((asset = AAssetManager_open(mgr, path.data(), AASSET_MODE_UNKNOWN)) != NULL) {
		this->cursor = 0;
		off_t bufferSize = AAsset_getLength(asset); 
		LOG->debug("open file %s and size %d", path.data(), bufferSize);
		return DG_TRUE;
	}

	return DG_FALSE;
}

long DGAssertResource::tell() {
	return this->cursor;
}


void DGAssertResource::close(){
	if (asset) {
		AAsset_close(asset);
		this->asset = NULL;
		this->cursor = 0;
	}
}