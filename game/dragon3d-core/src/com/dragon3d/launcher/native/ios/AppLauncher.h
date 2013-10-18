//
//  Dragon3DView.h
//  dragon3d-examples
//
//  Created by Wu CongWen on 13-10-1.
//  Copyright (c) 2013年 Wu CongWen. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GameLoop : NSObject { 
    void* _app;
}

- (id) initWithApp:(void*)app;

- (void) runLoop;

@end