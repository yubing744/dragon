#include "dg_file_resource.h"


DGFileResource::DGFileResource(const char* path){
	this->path = path;
	this->pFile = NULL;
}


DGFileResource::~DGFileResource(void){

}


int DGFileResource::read(void *buffer, size_t size, size_t count){
	return fread(buffer, size, count, pFile);
}

long DGFileResource::tell() {
	return ftell(pFile);
}


int DGFileResource::seek(long offset, int fromwhere){
	return fseek(pFile, offset, fromwhere);
}

DGuint DGFileResource::length() {
	int result = 0;

	int curPos = ftell(pFile);
	fseek(pFile, 0, SEEK_END);
	result = ftell(pFile);
	fseek(pFile, curPos, SEEK_SET);

	return result;
}

DGboolean DGFileResource::open(){
	if ((pFile = fopen(this->path.data(), "rb")) != NULL) {
		return DG_TRUE;
	}

	return DG_FALSE;
}

void DGFileResource::close(){
	if (pFile) {
		fclose(pFile);
	}
}