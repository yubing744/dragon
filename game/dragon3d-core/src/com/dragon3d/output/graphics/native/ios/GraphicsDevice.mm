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

// Launch Helper
#include "Dragon3DView.mm"

#include <com/dragon3d/output/graphics/GraphicsDevice.h>

#include <dragon/util/logging/Logger.h>

Import com::dragon3d::output::graphics;
Import dragon::util::logging;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::GraphicsDevice#ios", DEBUG);

// mine thread handle
typedef struct {
  	NSAutoreleasePool *pool;
  	UIWindow* window;
  	Dragon3DView* dgView;
} NativeData;

void GraphicsDevice::init() {
	logger->info("init");

	NativeData* data = new NativeData();

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];   

    CGRect screenBounds = [[UIScreen mainScreen] bounds]; 

	// create the window
	// note that using NSResizableWindowMask causes the window to be a little
	// smaller and therefore ipad graphics are not loaded
	UIWindow* window = [[UIWindow alloc] initWithFrame: screenBounds];
	window.backgroundColor = [UIColor whiteColor];

	// allocate our GL view
	// (isn't there already a shared EAGLView?)
	Dragon3DView* dgView = [[[Dragon3DView alloc] initWithFrame: screenBounds] autorelease];

 	// Use RootViewController manage EAGLView 
    UIViewController* viewController = [[UIViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = dgView;

    // Set RootViewController to window
    if ([[UIDevice currentDevice].systemVersion floatValue] < 6.0) {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
        logger->debug("bind view with window.addSubView");
    } else {
        // use this method on ios6
        [window setRootViewController:viewController];
        logger->debug("bind view with window.setRootViewController");
    }
    
    [window makeKeyAndVisible];

    // set default height
    this->width = screenBounds.size.width;
    this->height = screenBounds.size.height;

	// store the window to nativeDisplay.
	data->pool = pool;
	data->window = window;
	data->dgView = dgView;

	this->nativeData = data;
    
    // init the controller
    this->controller->init();
}

void GraphicsDevice::destroy() {
	logger->info("destroy");

	// init the controller
    this->controller->destroy();

    // destroy native data
	NativeData* data = (NativeData*)this->nativeData;
	
	[data->pool release];

	SafeDelete(data);
}
