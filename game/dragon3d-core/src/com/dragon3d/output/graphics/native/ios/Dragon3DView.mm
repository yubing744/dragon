//
//  Dragon3DView.m
//  dragon3d-examples
//
//  Created by Wu CongWen on 13-10-1.
//  Copyright (c) 2013年 Wu CongWen. All rights reserved.
//

#import <OpenGLES/EAGL.h>

#import <CoreFoundation/CoreFoundation.h>
#import <QuartzCore/QuartzCore.h>

#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import "Dragon3DView.h"

@implementation Dragon3DView

// You must implement this method
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id) initWithFrame:(CGRect)frame {    
    if ((self = [super initWithFrame:frame])) {
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
    }
    
    return self;
}

- (void) dealloc
{
    [super dealloc];
}

@end
