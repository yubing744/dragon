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
#import <QuartzCore/QuartzCore.h>

#include "AppLauncher.h"
#include <dragon/lang/Throwable.h>
#include <com/dragon3d/launcher/AppLauncher.h>

#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/framework/Application.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>

#include <com/dragon3d/output/audio/Speaker.h>

Import dragon::lang;
Import dragon::util::logging;
Import com::dragon3d::input;
Import com::dragon3d::output;
Import com::dragon3d::framework;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::audio;

static Logger* logger = Logger::getLogger("com::dragon3d::launcher::AppLauncher#ios", INFO);

@implementation GameLoop

- (id) initWithApp:(void*)app {
    if ((self = [super init])) {
        _app = app;
    }

    return self;
}

- (void) runLoop {    
    Application* app = (Application*)_app;

    try {
        app->runLoop();
    } catch (Throwable* t) {
        logger->errorT("Throwable caught in MainThread - exiting", t);
        t->printStackTrace();
        SafeDelete(t);
    }
}

@end


void Dragon3DLaunchApp(Application* app) {
    logger->info("launch app");

    // input
    InputManager* inputManager = new InputManager(); 
    app->setInputManager(inputManager);

    // ouput
    OutputManager* outputManager = new OutputManager();

    {
        // add graphics device
        GraphicsDevice* graphicsDevice = new GraphicsDevice();
        outputManager->registerDevice(graphicsDevice);

        // add audio device
        Speaker* speaker = new Speaker();
        outputManager->registerDevice(speaker);
    }

    app->setOutputManager(outputManager);

    // start app
    app->onStart();


    GameLoop* loop = [[GameLoop alloc] initWithApp: app];

    NSString *reqSysVer = @"3.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];

    if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending) {
        CADisplayLink* displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:loop selector:@selector(runLoop)];
        [displayLink setFrameInterval:1];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    } else {
        NSTimer* animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0) * 1) target:loop selector:@selector(runLoop) userInfo:nil repeats:TRUE];
    }
}

/**
 * terminate a app.
 * 
 * @param app [description]
 */
void Dragon3DTerminateApp(Application* app) {
    logger->info("terminate app");
    app->onStop();
}

