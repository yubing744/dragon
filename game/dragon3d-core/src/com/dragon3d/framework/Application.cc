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

 
#include <dragon/lang/System.h>
#include <dragon/lang/Throwable.h>
#include <dragon/lang/gc/Reference.h>
 
#include <dragon/util/ArrayList.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/scene/SimpleScene.h>
#include <com/dragon3d/framework/Application.h>

Import dragon::lang;
Import dragon::util;
Import dragon::util::logging;
Import com::dragon3d::framework;

Import dragon::lang::gc;

static Logger* logger = Logger::getLogger("com::dragon3d::framework::Application", INFO);

Application::Application() 
	:paused(true), exited(false) {
	this->inputManager = null;
	this->outputManager= null;

    this->currentScene = new SimpleScene();

	this->onCreate();
}

Application::~Application() {
	this->onDestroy();
    SafeRelease(this->currentScene);
}

// --------------------------------------
// application life cycle manage
// 

void Application::onCreate() {
	logger->info("on create");	
}

void Application::onStart() {
	logger->info("on start");

	// init frame handler
    logger->info("create frame handler"); 
	this->timer = new Timer();
	this->frameWork = new FrameHandler(timer);
	

    // init input and output manager
    this->inputManager->init();
    this->outputManager->init();

    this->frameWork->addUpdater(this);
    this->frameWork->addOutput(this);
    this->frameWork->addOutput(this->outputManager);

    this->frameWork->init();
    
    // init game
    this->onGameInit();
}

void Application::onResume() {
	logger->info("on resume");
	
	//this->paused = false;
	//this->timer->resume();
}

void Application::onPause() {
	logger->info("on pause");

	//this->paused = true;
	//this->timer->pause();
}

void Application::onStop() {
	logger->info("on stop");

    // destroy input and output manager
    this->inputManager->destroy();
    this->outputManager->destroy();
}

void Application::onDestroy() {
	logger->info("on destroy");	
}


// ------------------------------------------

void Application::onGameInit() {
	logger->info("on game init");
}

void Application::onGameDestroy() {
    logger->info("on game destroy");
    
    // destroy input and output manager
    this->inputManager->destroy();
    this->outputManager->destroy();
}

// ---------------------------------------

void Application::setInputManager(InputManager* inputManager) {
	this->inputManager = inputManager;
}

void Application::setOutputManager(OutputManager* outputManager) {
	this->outputManager = outputManager;
}

// --------------------------------------

Scene* Application::getCurrentScene() {
    SafeRetain(this->currentScene);
	return currentScene;
}

void Application::setNextScene(Scene* scene) {
    SafeRelease(this->currentScene);
    SafeRetain(scene);

    this->currentScene = scene;
}

// --------------------------------------

bool Application::isExit() {
    return this->exited;
}

void Application::exit() {
    logger->info("notify exit");
    this->exited = true;
}

void Application::runLoop() {
	logger->debug("run loop");

	Scene* scene = this->getCurrentScene();

    if (scene != null) {
        frameWork->updateFrame(scene);
    } else {
        logger->warn("Please setup a current scene");
        Thread::sleep(5000); // wait 5 second
    }

    SafeRelease(scene);
}

// ----------------------- simple game -----------------------

void Application::init() {
	logger->info("game scene init");

    logger->debug("init all the world");
    Ref<Scene> scene = this->getCurrentScene();

    Ref<List<GameObject> > gameObjects = scene->getAll();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();
        gameObject->init();
    }
}

void Application::update(Scene* scene, ReadOnlyTimer* timer) {
	logger->debug("game scene update");
	logger->debug("game scene fps %d", timer->getFrameRate());
	logger->debug("current time %d", System::currentTimeMillis());

    logger->debug("update all the world");

    Ref<List<GameObject> > gameObjects = scene->getAll();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();
        gameObject->update(this->inputManager, timer);
    }
}

void Application::output(Scene* scene, CountDownLatch* latch) {
	logger->debug("game scene output");

    latch->countDown();
}

void Application::destroy() {
    logger->debug("game scene destroy");

    logger->debug("destroy all the world");
    Ref<Scene> scene = this->getCurrentScene();

    Ref<List<GameObject> > gameObjects = scene->getAll();
    Ref<Iterator<GameObject> > it = gameObjects->iterator();

    while(it->hasNext()) {
        Ref<GameObject> gameObject = it->next();
        gameObject->destroy();
    }
}