#include "dg_vector3.h"


DGVector3::DGVector3(void){
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

DGVector3::DGVector3(DGfloat x, DGfloat y, DGfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

const DGVector3 DGVector3::zero = DGVector3(0, 0 ,0);
const DGVector3 DGVector3::one = DGVector3(1, 1 ,1);

const DGVector3 DGVector3::forward = DGVector3(0, 0 ,1);
const DGVector3 DGVector3::up = DGVector3(0, 1 ,0);
const DGVector3 DGVector3::right = DGVector3(1, 0 ,0);

string DGVector3::toString(){
	char buf[256];
	
	string sb;

	memset(buf, 0, sizeof(char) * 256);
	sprintf(buf, "DGVector3 [%.2f, %.2f, %.2f]", x, y, z);
	sb.append(buf);

	return sb;
}