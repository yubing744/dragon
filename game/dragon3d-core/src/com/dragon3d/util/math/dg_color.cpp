#include "dg_color.h"

static int HexMap[] = {
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,1,2,3, 4,5,6,7, 8,9,0,0, 0,0,0,0,

	0,10,11,12, 13,14,15,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,10,11,12, 13,14,15,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
};

DGColor DGColor::hexColor(const char* hexColor){
	if (hexColor[0] == '#') {
		hexColor++;
	}

	int lenght = strlen(hexColor);

	if (lenght >= 6) {
		int offset = -1;
		DGuint r = (HexMap[hexColor[offset + 1]] * 16) + HexMap[hexColor[offset + 2]];
		DGuint g = (HexMap[hexColor[offset + 3]] * 16) + HexMap[hexColor[offset + 4]];
		DGuint b = (HexMap[hexColor[offset + 5]] * 16) + HexMap[hexColor[offset + 6]];

		if (lenght < 8) {
			return DGColor(r, g, b);
		} else {
			DGuint a = (HexMap[hexColor[offset + 7]] * 16) + HexMap[hexColor[offset + 8]];
			return DGColor(r, g, b, a);
		}
	}

	return DGColor::black;
}

const DGColor DGColor::white = DGColor(1.0f, 1.0f, 1.0f);
const DGColor DGColor::red = DGColor(1.0f, 0.0f, 0.0f);
const DGColor DGColor::green = DGColor(0.0f, 1.0f, 0.0f);
const DGColor DGColor::blue = DGColor(0.0f, 0.0f, 1.0f);
const DGColor DGColor::black = DGColor(0.0f, 0.0f, 0.0f);

DGColor::DGColor(void) {
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
	this->a = 0.0f;
}

DGColor::DGColor(DGfloat r, DGfloat g, DGfloat b){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 0.0f;
}

DGColor::DGColor(DGfloat r, DGfloat g, DGfloat b, DGfloat a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

DGColor::DGColor(DGuint r, DGuint g, DGuint b){
	this->r = r / 256.0f;
	this->g = g / 256.0f;
	this->b = b / 256.0f;
	this->a = 0.0f;
}

DGColor::DGColor(DGuint r, DGuint g, DGuint b, DGuint a){
	this->r = r / 256.0f;
	this->g = g / 256.0f;
	this->b = b / 256.0f;
	this->a = a / 256.0f;
}

DGColor::DGColor(DGubyte r, DGubyte g, DGubyte b){
	this->r = r / 256.0f;
	this->g = g / 256.0f;
	this->b = b / 256.0f;
	this->a = 0.0f;
}

DGColor::DGColor(DGubyte r, DGubyte g, DGubyte b, DGubyte a){
	this->r = r / 256.0f;
	this->g = g / 256.0f;
	this->b = b / 256.0f;
	this->a = a / 256.0f;
}

DGColor::DGColor(const char* hexColor){
	*this = DGColor::hexColor(hexColor);
}