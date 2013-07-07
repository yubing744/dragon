#include "dg_material.h"

const DGMaterial DGMaterial::DEFAULT_MATERIAL = DGMaterial(DGColor::white);

DGMaterial::DGMaterial(void){
	this->color = DGColor::white;
	this->mainTexture = NULL;
}

DGMaterial::DGMaterial(const DGColor& color){
	this->color = color;
	this->mainTexture = NULL;
}

DGMaterial::DGMaterial(const DGColor& color, DGTexture* mainTexture){
	this->color = color;
	this->mainTexture = mainTexture;
}

DGMaterial::~DGMaterial(void){

}