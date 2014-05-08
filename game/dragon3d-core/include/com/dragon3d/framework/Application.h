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
 * Created:     2013/09/28
 **********************************************************************/


#ifndef Application_Framework_Dragon3d_Com_H
#define Application_Framework_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/lang/Thread.h>

#include <dragon/util/concurrent/Semaphore.h>
#include <dragon/util/concurrent/CountDownLatch.h>
#include <dragon/util/concurrent/locks/SynchLock.h>

#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/Timer.h>

#include <com/dragon3d/framework/Scene.h>
#include <com/dragon3d/framework/FrameHandler.h>

#include <com/dragon3d/input/InputManager.h>
#include <com/dragon3d/output/OutputManager.h>

#include <com/dragon3d/scene/GameObject.h>

BeginPackage3(com, dragon3d, framework)

Import dragon::lang;
Import dragon::util;
Import dragon::util::logging;
Import dragon::util::concurrent;
Import dragon::util::concurrent::locks;

Import com::dragon3d::framework;
Import com::dragon3d::util;
Import com::dragon3d::input;
Import com::dragon3d::output;
Import com::dragon3d::scene;

/**
 * game application.
 * 
 */
class _DragonExport Application extends(Object) 
	implements1(Updater) {
public:
	Application();
	virtual ~Application();

public: // application lifecycle callback
	/**
	 * callback when app create.
	 */
	virtual void onCreate();

	/**
	 * callback when game init.
	 */
	virtual void onStart();

	/**
	 * callback when game init.
	 */
	virtual void onInit();

	/**
	 * callback when app resume.
	 */
	virtual void onResume();

	/**
	 * callback when game update.
	 */
	virtual void onUpdate(Scene* scene, ReadOnlyTimer* timer);

	/**
	 * callback when app pause.
	 */
	virtual void onPause();

	/**
	 * callback when app stop.
	 */
	virtual void onStop();

	/**
	 * callback when app destroy.
	 */
	virtual void onDestroy();

public:
	/**
	 * set input manager.
	 * 
	 * @param inputManager [description]
	 */
	virtual void setInputManager(InputManager* inputManager);

	/**
	 * set output manager.
	 * 
	 * @param outputManager [description]
	 */
	virtual void setOutputManager(OutputManager* outputManager);

public:
	/**
	 * whether app should exit.
	 * 
	 * @return [description]
	 */
	virtual bool isStoped();

	/**
	 * app main loop
	 */
	virtual void runLoop();

public:// app control
	/**
	 * start app
	 */
	virtual void start();

	/**
	 * pause the app
	 */
	virtual void pause();

	/**
	 * resume the app
	 */
	virtual void resume();

	/**
	 * stop the app
	 */
	virtual void stop();


public: // Implements Updater
	virtual void init();
	virtual void update(Scene* scene, ReadOnlyTimer* timer);
	virtual void destroy();	

protected:
	/**
	 * get the current to render scene.
	 * 
	 * @return [description]
	 */
	virtual Scene* getCurrentScene();

	/**
	 * set next render scene.
	 * 
	 * @param scene [description]
	 */
	virtual void setNextScene(Scene* scene);

protected:
	/**
	 * application name.
	 * 
	 */
	String* name;

	/**
	 * the timer to control the fps
	 */
	Timer* timer;

	/**
	 * the game frame handler
	 */
	FrameHandler* frameWork;

	/**
	 * whether the app need exit
	 */
	bool stoped;

	/**
	 * whether the app is pause.
	 */
	bool paused;

	/**
	 * input manager
	 */
	InputManager* inputManager;

	/**
	 * output manager
	 */
	OutputManager* outputManager;

	/**
	 * current scene.
	 */
	Scene* currentScene;

};//Application

EndPackage3 //(com, dragon3d, framework)

#endif //Application_Framework_Dragon3d_Com_H