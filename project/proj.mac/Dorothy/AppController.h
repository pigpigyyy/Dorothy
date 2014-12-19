//
//  AppDelegate.h
//  Dorothy
//
//  Created by Li Jin on 14/11/24.
//  Copyright (c) 2014年 Li Jin. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "EAGLView.h"
#include "AppDelegate.h"

@interface AppController : NSObject <NSApplicationDelegate>
{
	NSWindow* _window;
	EAGLView* _view;
	AppDelegate* _app;
}

@end

