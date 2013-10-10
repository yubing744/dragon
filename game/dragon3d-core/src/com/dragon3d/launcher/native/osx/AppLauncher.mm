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
#include <com/dragon3d/launcher/native/osx/AppLauncher.h>

#include <com/dragon3d/framework/Application.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
//#include <dragon/util/logging/Logger.h>

//Import dragon::util::logging;
Import com::dragon3d::framework;
Import com::dragon3d::input;
Import com::dragon3d::output;
Import com::dragon3d::output::graphics;

@implementation AppLauncher
	-(void) launchApp:(void*) toLaunchApplication {
		// create Application
		Application* app = (Application*)toLaunchApplication;

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

		// start app
		app->onStart();

		_app = app;
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication {
		Application* app = (Application*)_app;
		app->onStop();

		return YES;
	}

	-(void) dealloc {
		[super dealloc];
	}

@end
