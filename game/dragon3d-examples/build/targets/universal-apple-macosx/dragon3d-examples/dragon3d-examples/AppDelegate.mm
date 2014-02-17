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
#include <com/dragon3d/examples/audio/AudioDemo.h>

Import com::dragon3d::examples::audio;
Import com::dragon3d::examples::helloworld;

@implementation AppDelegate
    {
        HelloWorld* helloworld;
        AudioDemo* audioDemo;
    }

	-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
	{
        helloworld = new HelloWorld();
        audioDemo = new AudioDemo();
        
        //Dragon3DLaunchApp(helloworld);
        Dragon3DLaunchApp(audioDemo);
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
	{
        //Dragon3DTerminateApp(helloworld);
        Dragon3DTerminateApp(audioDemo);
        
		return YES;
	}

	-(void) dealloc
	{
        [super dealloc];
        
        SafeDelete(helloworld);
        SafeDelete(audioDemo);
	}

@end