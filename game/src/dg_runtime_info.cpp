#include "dg_runtime_info.h"


DGRuntimeInfo::DGRuntimeInfo(void)
{
}


DGRuntimeInfo::~DGRuntimeInfo(void)
{
}


void DGRuntimeInfo::start(){

}

void DGRuntimeInfo::update(DGContext* ctx){

}


void DGRuntimeInfo::draw(DGContext* ctx){
	DGGUIText* gui = ctx->getGUIText();
	DGScreen* screen = ctx->getScreen();
	DGApplication* app = ctx->getApp();

	gui->print(screen->getWidth() - 200, screen->getHeight() - 10, "frameInterval: %ld", app->frameInterval);
}