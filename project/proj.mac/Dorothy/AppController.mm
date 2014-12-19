//
//  AppDelegate.m
//  Dorothy
//
//  Created by Li Jin on 14/11/24.
//  Copyright (c) 2014年 Li Jin. All rights reserved.
//

#import "AppController.h"
#import "CCDirectorCaller.h"

@interface AppController ()

@property (weak) IBOutlet NSWindow* window;
@property (weak) IBOutlet EAGLView* view;
@end

@implementation AppController

@synthesize window = _window;
@synthesize view = _view;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	[_view initWithFrame:
		NSRect{NSPoint{0,0},[_window contentLayoutRect].size}
		shareContext:(NSOpenGLContext *)[_view openGLContext]];
	_app = new AppDelegate();
	_app->run();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
	[[CCDirectorCaller sharedDirectorCaller] end];
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication *) theApplication
{
	return YES;
}

- (void)dealloc
{
	delete _app;
	[super dealloc];
}

@end
