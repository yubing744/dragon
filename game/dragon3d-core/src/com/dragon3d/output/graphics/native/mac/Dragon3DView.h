//
//  Dragon3DView.h
//  dragon3d-examples
//
//  Created by Wu CongWen on 13-10-1.
//  Copyright (c) 2013年 Wu CongWen. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface Dragon3DView : NSOpenGLView {
	void*       app_;

	BOOL        isFullScreen_;    
    float       frameZoomFactor_;
}

@property (nonatomic, readonly) BOOL isFullScreen;
@property (nonatomic, readwrite) float frameZoomFactor;

- (id) initWithFrame:(NSRect)frameRect;
- (id) initWithFrame:(NSRect)frameRect withApp:(void*) app;
- (id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context withApp:(void*) app;
- (id) initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format withApp:(void*) app;

-(void) lockOpenGLContext;
-(void) unlockOpenGLContext;

- (NSUInteger) depthFormat;

- (void) setFrameZoomFactor:(float)frameZoomFactor;

-(int) getWidth;
-(int) getHeight;
-(void) swapBuffers;

-(void) setFullScreen:(BOOL)fullscreen;

@end
