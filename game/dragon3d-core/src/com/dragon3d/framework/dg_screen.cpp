#include "dg_screen.h"


DGScreen::DGScreen(void)
{
}


DGScreen::~DGScreen(void)
{
}


DGuint DGScreen::getWidth(){
	return this->width;
}

DGuint DGScreen::getHeight(){
	return this->height;
}

void DGScreen::resize(DGuint width, DGuint height) {
	this->width = width;
	this->height = height;
}
