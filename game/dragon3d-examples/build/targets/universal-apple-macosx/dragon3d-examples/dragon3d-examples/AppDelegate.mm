//
//  AppDelegate.m
//  dragon3d-examples
//
//  Created by Wu CongWen on 13-9-29.
//  Copyright (c) 2013年 Wu CongWen. All rights reserved.
//

#import "AppDelegate.h"

#include <com/dragon3d/launcher/AppLauncher.h>
#include <com/dragon3d/examples/helloworld/HelloWorld.h>

Import com::dragon3d::examples::helloworld;

@implementation AppDelegate
    {
        HelloWorld* helloworld;
    }

	-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
	{
        helloworld = new HelloWorld();
        Dragon3DLaunchApp(helloworld);
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
	{
        Dragon3DTerminateApp(helloworld);
		return YES;
	}

	-(void) dealloc
	{
        [super dealloc];
        SafeDelete(helloworld);
	}

@end