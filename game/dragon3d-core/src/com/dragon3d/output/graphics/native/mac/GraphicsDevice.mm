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

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::GraphicsDevice#mac", INFO);

// mine thread handle
typedef struct NativeData {
  	NSAutoreleasePool *pool;
  	NSWindow* window;
  	Dragon3DView* dgView;
};

void GraphicsDevice::init() {
	logger->info("init");

	NativeData* data = new NativeData();

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];   

	// create the window
	// note that using NSResizableWindowMask causes the window to be a little
	// smaller and therefore ipad graphics are not loaded
	NSRect rect = NSMakeRect(0, 0, 320, 480);
	NSWindow* window = [[NSWindow alloc] initWithContentRect:rect
		styleMask:( NSClosableWindowMask | NSTitledWindowMask )
		backing:NSBackingStoreBuffered
		defer:YES];
	
	// allocate our GL view
	// (isn't there already a shared EAGLView?)
	Dragon3DView* dgView = [[Dragon3DView alloc] initWithFrame:rect];

	// set window parameters
	[window becomeFirstResponder];
	[window setContentView:dgView];
	[window setTitle:@"dragon3d-examples2"];
	[window makeKeyAndOrderFront:nil];
	[window setAcceptsMouseMovedEvents:NO];

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

	SafeDelete(this->nativeData);
}


/*

#include "dg_screen.h"


DGScreen::DGScreen(void)
{
}


DGScreen::~DGScreen(void)
{
}


DGuint DGScreen::getWidth(){
	return this->width;
}

DGuint DGScreen::getHeight(){
	return this->height;
}

void DGScreen::resize(DGuint width, DGuint height) {
	this->width = width;
	this->height = height;
}


 */