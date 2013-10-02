//
//  AppDelegate.m
//  dragon3d-examples
//
//  Created by Wu CongWen on 13-9-29.
//  Copyright (c) 2013年 Wu CongWen. All rights reserved.
//

#import "AppDelegate.h"

#include <com/dragon3d/launcher/native/mac/AppLauncher.h>

@implementation AppDelegate
    {
        AppLauncher* launcher; // 指针!会在alloc时初始为NULL.
    }

	-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
	{
        launcher = [[AppLauncher alloc] init];
        [launcher applicationDidFinishLaunching:aNotification];
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
	{
		return [launcher applicationShouldTerminateAfterLastWindowClosed:theApplication];
	}

	-(void) dealloc
	{
        [launcher dealloc];
		[super dealloc];
	}

@end