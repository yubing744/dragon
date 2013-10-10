//
//  AppDelegate.m
//  dragon3d-examples
//
//  Created by Wu CongWen on 13-9-29.
//  Copyright (c) 2013年 Wu CongWen. All rights reserved.
//

#import "AppDelegate.h"

#include <com/dragon3d/launcher/native/osx/AppLauncher.h>
#include <com/dragon3d/examples/helloworld/HelloWorld.h>

Import com::dragon3d::examples::helloworld;

@implementation AppDelegate
    {
        AppLauncher* launcher; // 指针!会在alloc时初始为NULL.
        HelloWorld* helloworld;
    }

	-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
	{
        helloworld = new HelloWorld();
        
        launcher = [[AppLauncher alloc] init];
        [launcher launchApp:helloworld];
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
	{
		return [launcher applicationShouldTerminateAfterLastWindowClosed:theApplication];
	}

	-(void) dealloc
	{
         SafeDelete(helloworld);
        [launcher dealloc];
		[super dealloc];
	}

@end