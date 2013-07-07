#include "dg_platform.h"

DGPlatform* DGPlatform::platform = NULL;

DGPlatform* DGPlatform::getCurrent(){
	return DGPlatform::platform;
}

DGPlatform::DGPlatform(void){

}

DGPlatform::~DGPlatform(void){

}
