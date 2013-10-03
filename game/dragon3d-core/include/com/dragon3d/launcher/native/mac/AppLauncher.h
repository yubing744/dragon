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


#ifndef AppLauncher_Launcher_Dragon3d_Com_H
#define AppLauncher_Launcher_Dragon3d_Com_H

#import <Cocoa/Cocoa.h>

@interface AppLauncher : NSObject <NSApplicationDelegate> {
	void* _app;
}

@end

#endif //AppLauncher_Launcher_Dragon3d_Com_H


/*

#pragma once

#include "dg_config.h"

#ifndef DG_PLATFORM
#define DG_PLATFORM

#include "dg_log.h"
#include "dg_graphics_lib.h"
#include "dg_platform_callback.h"
#include "dg_resource.h"

class DGPlatform
{
public:
	DGPlatform(void);
	virtual ~DGPlatform(void);

public:
	virtual void setCallback(DGPlatformCallback* callback) = 0;

	virtual DGboolean createWin(const char *title, DGuint width, DGuint height) = 0;
	virtual void showWin() = 0;

	virtual DGGraphicsLib* getGraphicsLib() = 0;

	virtual DGResource* openResource(const char* path) = 0;
	virtual void closeResource(DGResource* resource) =0;

    virtual DGLog* getLogger(const char* tagName) = 0;

public:
	static DGPlatform* getCurrent();

protected:
	static DGPlatform* platform;
};

#endif


#pragma once

#include "dg_config.h"

#ifndef DG_PLATFORM_CALLBACK
#define DG_PLATFORM_CALLBACK

class DGPlatformCallback
{
public:
	DGPlatformCallback(void);
	virtual ~DGPlatformCallback(void);

public:
	virtual void start() = 0;
	virtual void draw() = 0;
	virtual void resize(DGuint width, DGuint height) = 0;
	virtual void update(DGfloat deltaTime) = 0;
	virtual void key(DGubyte charCode, DGboolean pressed, DGuint wParam, DGuint lParam) = 0;
};

#endif

 */