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

// Implements AppLauncher 
// 
#include <com/dragon3d/launcher/AppLauncher.h>

#include <com/dragon3d/framework/Application.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <dragon/lang/Throwable.h>
#include <dragon/util/ArrayList.h>
#include <dragon/util/logging/Logger.h>

Import dragon::lang;
Import dragon::util::logging;
Import com::dragon3d::framework;
Import com::dragon3d::input;
Import com::dragon3d::output;
Import com::dragon3d::output::graphics;

static Logger* logger = Logger::getLogger("com::dragon3d::launcher::AppLauncher#osx", INFO);

/**
 * game loop
 */
class GameLoop implements(Runnable){
public:
    GameLoop(Application* app) {
        this->app = app;
    }

public:
    void run() {
        try {
            // start app
            app->onStart();

            while (!app->isExit()) {
                app->runLoop();
            }

            // stop app
            app->onStop();
        } catch (Throwable* t) {
            logger->error("Throwable caught in MainThread - exiting");
            t->printStackTrace();
            SafeDelete(t);
        }
    }

protected:
    Application* app;
};

/**
 * launch a app.
 * 
 * @param app [description]
 */
void Dragon3DLaunchApp(Application* app) {
    // input
    InputManager* inputManager = new InputManager(); 
    app->setInputManager(inputManager);

    // ouput
    OutputManager* outputManager = new OutputManager();

    {
        // add graphics device
        GraphicsDevice* graphicsDevice = new GraphicsDevice();
        outputManager->registerDevice(graphicsDevice);
    }

    app->setOutputManager(outputManager);

    // start new thread to run game.
    GameLoop* loop = new GameLoop(app);
    Thread* thread = new Thread(loop);
    thread->start();
}

/**
 * terminate a app.
 * 
 * @param app [description]
 */
void Dragon3DTerminateApp(Application* app) {
    app->exit();
}