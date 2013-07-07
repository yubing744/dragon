#include "dg_context.h"
#include "dg_engine.h"

DGPlatform* DGContext::getPlatform() {
    return engine->getPlatform();
};

DGGraphicsLib* DGContext::getGraphicsLib() {
    return engine->getGraphicsLib();
};

DGScreen* DGContext::getScreen() {
    return engine->getScreen();
};

DGfloat DGContext::getFrameInterval() {
    return engine->frameInterval;
};

DGInput* DGContext::getInput(){
	return engine->getInput();
}