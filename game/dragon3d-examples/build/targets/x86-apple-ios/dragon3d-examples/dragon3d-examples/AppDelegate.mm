//
//  AppDelegate.m
//  dragon3d-examples
//
//  Created by Wu CongWen on 13-10-10.
//  Copyright (c) 2013年 Wu CongWen. All rights reserved.
//

#import <OpenGLES/EAGL.h>

#import <CoreFoundation/CoreFoundation.h>
#import <QuartzCore/QuartzCore.h>

#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import "AppDelegate.h"

#import "ViewController.h"

#include <dragon/lang/System.h>
#include <com/dragon3d/launcher/AppLauncher.h>

#include <com/dragon3d/examples/audio/AudioDemo.h>
#include <com/dragon3d/examples/helloworld/HelloWorld.h>
#include <com/dragon3d/examples/texture/TextureDemo.h>
#include <com/dragon3d/examples/model/ModelDemo.h>
#include <com/dragon3d/examples/loderunner/LodeRunner.h>

Import dragon::lang;
Import com::dragon3d::examples::audio;
Import com::dragon3d::examples::helloworld;
Import com::dragon3d::examples::texture;
Import com::dragon3d::examples::model;
Import com::dragon3d::examples::loderunner;

@implementation AppDelegate
{
    //AppLauncher* launcher;
    
    Application* app;
}

- (void)dealloc
{
    SafeRelease(app);
    
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{    
    //app = new HelloWorld();
    //app = new AudioDemo();
    //app = new TextureDemo();
    //app = new ModelDemo();
    //app = new LodeRunner();
    
    Dragon3DLaunchApp(app);
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    Dragon3DTerminateApp(app);
}

@end
