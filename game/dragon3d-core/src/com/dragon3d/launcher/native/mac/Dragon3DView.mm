//
//  Dragon3DView.m
//  dragon3d-examples
//
//  Created by Wu CongWen on 13-10-1.
//  Copyright (c) 2013年 Wu CongWen. All rights reserved.
//

#import "Dragon3DView.h"

#include <OpenGL/gl.h>

#include <com/dragon3d/framework/Application.h>

Import com::dragon3d::framework;

@implementation Dragon3DView

@synthesize isFullScreen = isFullScreen_, frameZoomFactor=frameZoomFactor_;

- (id) initWithFrame:(NSRect)frameRect withApp:(void*) app {
    NSLog(@"initWithFrame frameRect app");

    self = [self initWithFrame:frameRect shareContext:nil withApp:app];
    return self;
}

- (id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context withApp:(void*) app  {
    NSLog(@"initWithFrame frameRect context app");

    NSOpenGLPixelFormatAttribute attribs[] = {
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, 24,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
    
    if (!pixelFormat)
        NSLog(@"No OpenGL pixel format");
    
    if((self = [self initWithFrame:frameRect pixelFormat:[pixelFormat autorelease] withApp:app])) {
        if( context )
            [self setOpenGLContext:context];
    }
    
    //cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize(frameRect.size.width, frameRect.size.height);
    
    frameZoomFactor_ = 1.0f;
    
    return self;
}

- (id) initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format withApp:(void*) app {
    NSLog(@"initWithFrame frameRect format app");

    app_ = app;

    frameZoomFactor_ = 1.0f;
    
    [super initWithFrame:frameRect pixelFormat:format];

    return self;
}

- (void) update {
    [super update];

    NSLog(@"ELView update");

    // Application* app = (Application*)app_;
    // app->onUpdate();
}

- (void) prepareOpenGL {
    // XXX: Initialize OpenGL context
    [super prepareOpenGL];
    
    // Make this openGL context current to the thread
    // (i.e. all openGL on this thread calls will go to this context)
    [[self openGLContext] makeCurrentContext];
    
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];  
}

- (NSUInteger) depthFormat {
    return 24;
}

- (void) setFrameZoomFactor:(float)frameZoomFactor {
    frameZoomFactor_ = frameZoomFactor;
    
    NSRect winRect = [[self window] frame];
    NSRect viewRect = [self frame];
    
    // compute the margin width and margin height
    float diffX = winRect.size.width - viewRect.size.width;
    float diffY = winRect.size.height - viewRect.size.height;
    
    // new window width and height
    float newWindowWidth = (int)(viewRect.size.width * frameZoomFactor + diffX);
    float newWindowHeight = (int)(viewRect.size.height * frameZoomFactor + diffY);
    
    // display window in the center of the screen
    NSRect screenRect = [[NSScreen mainScreen] frame];
    float originX = (screenRect.size.width - newWindowWidth) / 2;
    float originY = (screenRect.size.height - newWindowHeight) / 2;
    
    [[self window] setFrame:NSMakeRect(originX, originY, newWindowWidth, newWindowHeight) display:true];
}

- (void) reshape {
    [self lockOpenGLContext];

    NSLog(@"ELView reshape");
    
    //app_->onUpdate();
    
    [self unlockOpenGLContext];
}

-(void) lockOpenGLContext {
    NSOpenGLContext *glContext = [self openGLContext];
    [glContext makeCurrentContext];

    CGLLockContext((CGLContextObj)[glContext CGLContextObj]);
}

-(void) unlockOpenGLContext {
    NSOpenGLContext *glContext = [self openGLContext];
    CGLUnlockContext((CGLContextObj)[glContext CGLContextObj]);
}

- (void) dealloc {
    [super dealloc];
}
    
-(int) getWidth {
    NSSize bound = [self bounds].size;
    return bound.width;
}

-(int) getHeight {
    NSSize bound = [self bounds].size;
    return bound.height;
}

-(void) swapBuffers {

}

- (void) setFullScreen:(BOOL)fullscreen
{

}

@end
