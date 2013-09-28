/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/15
 **********************************************************************/


#include <com/dragon3d/framework/Application.h>
#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;
Import com::dragon3d::framework;


Application::Application() {

}

Application::~Application() {

}

void Application::startup() {
	//Timer* timer = new Timer();
	//FrameHandler* frameWork = new FrameHandler(timer);
}


/*

#include "dg_application.h"

#include "dg_game.h"
#include "dg_engine.h"
#include "dg_mesh_renderer.h"
#include "dg_cuboid.h"
#include "dg_behaviour.h"
#include "dg_script_behaviour.h"
#include "dg_first_person_controller.h"

#include "dg_texture.h"
#include "dg_material.h"

class DGCuboidBehaviour
    :public DGBehaviour {
public:
    DGCuboidBehaviour(){
		this->log = DGPlatform::getCurrent()->getLogger("dg_cuboid_behaviour_lib");
        this->angle = 45.0f;
    };

public:
    virtual void update(DGContext* ctx){
        transform->rotate(ctx->getFrameInterval() * 40.0f, ctx->getFrameInterval() * 40.0f, ctx->getFrameInterval() * 40.0f, DGSpace::World);
		//transform->rotate(0, ctx->getFrameInterval() * 40.0f, 0);
		
		//angle += (ctx->getFrameInterval() * 40.0f);
		//if(angle >= 360.0f) {
		//	angle -= 360.0f;
		//}

		//log->debug(transform->rotation.toString().data());
    };

public:
    DGfloat angle;
	DGLog* log;
};


DGCuboid* cuboid = NULL;
DGFirstPersonController* personController = NULL;
DGTexture* texture = NULL;
DGMaterial* material = NULL;

void DGApplication::startup(DGEngine* engine){

	DGScene* scene = engine->createScene();

	DGFirstPersonController person;

	texture = new DGTexture("Textures/basemap.tga");
	material = new DGMaterial(DGColor::white, texture);

	cuboid = new DGCuboid();
	cuboid->setMaterial(material);

	//Setup Camera
	personController = new DGFirstPersonController();
	scene->addChild(personController);

	//cuboid->setColor(DGColor(0.0f, 1.0f, 0.0f));

    DGGameObject* clue = new DGGameObject();
    clue->addComponent(cuboid);
    clue->addComponent(new DGCuboidBehaviour());
    clue->transform->position = DGVector3(-1, 0.5f, -6.0f);
    scene->addChild(clue);

    DGGameObject* clue2 = new DGGameObject();
    clue2->addComponent(cuboid);
    clue2->addComponent(new DGScriptBehaviour());
    clue2->transform->position = DGVector3(1, 0.5f, -6.0f);
    scene->addChild(clue2);

	// Load Model
	DGModelManager* modelManager = engine->getModelManager();
	DGModel* testModel = modelManager->loadModel("Data/model/tire.3ds");
	testModel->addComponent(new DGCuboidBehaviour());

	testModel->transform->localScale = DGVector3(0.001f, 0.001f, 0.001f);
	testModel->transform->localPosition = DGVector3(0, 1.0f, 1.0f);
	testModel->transform->rotate(-90, 0, 180);

	if (testModel != NULL) {
		scene->addChild(testModel);
	}
}

void DGApplication::end(DGEngine* engine) {
	dgDelete(cuboid);
	dgDelete(personController);
	//dgDelete(texture);
	//dgDelete(material);
}


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


 */