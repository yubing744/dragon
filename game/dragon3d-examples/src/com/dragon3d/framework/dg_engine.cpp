#include "dg_engine.h"

DGLog* DGEngine::LOG = new DGLog("dg_engine");

DGEngine::DGEngine(void){
	

	this->platform = NULL;
	this->glib = NULL;

    this->screen = new DGScreen();
	this->inputManager = new DGInputManager();
	this->modelManager = new DGModelManager();
}

DGEngine::~DGEngine(void){
	// Destroy all scenes
	int size = scenes.size();
	for(int i=0; i<size; i++) {
		DGScene* scene = scenes[i];
		dgDelete(scene);
	}

	// Out variable don't release
	if (this->platform) {
		this->platform = NULL;
	}

	// Release graphice library
	if (this->glib) {
		this->glib = NULL;
	}

    dgDelete(this->screen);
	dgDelete(this->inputManager);
	dgDelete(this->modelManager);
}

DGboolean DGEngine::init(DGPlatform* platform, const char* title, DGuint width, DGuint height){
	// Set platform
	this->platform = platform;

	// Initialize graphice library
	if (!platform->createWin(title, width, height)) {	
		return DG_FALSE;
	}

	this->glib = platform->getGraphicsLib();
    if (!this->glib) {
        return DG_FALSE;
    }

    this->screen->resize(width, height);

	if (this->platform) {
		this->platform->setCallback(this);
	}

	this->modelManager->addDefaultModelLoaders();

	return DG_TRUE;
}


void DGEngine::run() {
	this->start();
	platform->showWin();
}

void DGEngine::start(){
	LOG->debug("start");

	this->glib->init();
	this->resize(screen->getWidth(), screen->getHeight());

	DGContext ctx(this);

    int size = scenes.size();
	for(int i=0; i<size; i++) {
		DGScene* scene = scenes[i];
		scene->init(&ctx);
	}
}

void DGEngine::draw(){
	DGGraphicsLib* gl = this->glib;

	DGContext ctx(this);

	gl->reset();

	int cameraSize = cameras.size();
	for(int i=0; i<cameraSize; i++) {
		DGCamera* camera = cameras[i];
		camera->setup(&ctx);
	}

	int size = scenes.size();
	for(int i=0; i<size; i++) {
		DGScene* scene = scenes[i];
		scene->draw(&ctx);
	}
}

void DGEngine::update(DGfloat deltaTime){
	this->frameInterval = deltaTime;

	DGContext ctx(this);

	int size = scenes.size();
	for(int i=0; i<size; i++) {
		DGScene* scene = scenes[i];
		scene->update(&ctx);
	}
}

void DGEngine::resize(DGuint width, DGuint height) {
	LOG->debug("resize %d %d", width, height);

	DGGraphicsLib* gl = this->glib;
	this->screen->resize(width, height);

	gl->viewport(0, 0, width, height);
	gl->perspective(60.0f,  this->screen->getWidth() * 1.0f / this->screen->getHeight(), 0.1f, 1000.0f);
}

void DGEngine::key(DGubyte charCode, DGboolean pressed, DGuint wParam, DGuint lParam){
	if (pressed) {
		this->inputManager->handleKeyDown(charCode);
	} else {
		this->inputManager->handleKeyUp(charCode);
	}
}

DGScene* DGEngine::createScene(){
	DGScene* scene = new DGScene();
	scenes.push_back(scene);
	return scene;
}

void DGEngine::setupCamera(DGCamera* camera) {
	this->cameras.push_back(camera);
}