#include "dg_vector2.h"

DGVector2::DGVector2(void){
    this->x = 0;
    this->y = 0;
}

DGVector2::DGVector2(DGfloat x, DGfloat y){
    this->x = x;
    this->y = y;
};

string DGVector2::toString(){
	char buf[256];
	
	string sb;

	memset(buf, 0, sizeof(char) * 256);
	sprintf(buf, "DGVector2 [%.2f, %.2f]", x, y);
	sb.append(buf);

	return sb;
}