#include "dg_quaternion.h"


DGQuaternion::DGQuaternion(void) {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

DGQuaternion::DGQuaternion(DGfloat x, DGfloat y, DGfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 0.0f;
}

DGQuaternion::DGQuaternion(DGfloat x, DGfloat y, DGfloat z, DGfloat w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

const DGQuaternion DGQuaternion::identity = DGQuaternion(0, 0, 0, 0);

string DGQuaternion::toString(){
	char buf[256];
	
	string sb;

	memset(buf, 0, sizeof(char) * 256);
	sprintf(buf, "DGQuaternion [%.2f, %.2f, %.2f, %.2f]", x, y, z, z);
	sb.append(buf);

	return sb;
}