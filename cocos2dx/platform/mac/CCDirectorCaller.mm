/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#import <Foundation/Foundation.h>
#import "CCDirectorCaller.h"
#import "CCDirector.h"
#import "EAGLView.h"
#import "CCEventDispatcher.h"
#include "CCAutoreleasePool.h"

static id s_sharedDirectorCaller = [[CCDirectorCaller alloc] init];;

@implementation CCDirectorCaller

@synthesize interval;

+(id) sharedDirectorCaller
{
	return s_sharedDirectorCaller;
}

-(void) alloc
{
    interval = 1;
}

-(void) dealloc
{
    s_sharedDirectorCaller = nil;
    CCLOG("cocos2d: deallocing CCDirectorCaller %x", self);
	[super dealloc];
}

- (void)timerFired:(id)sender
{
	// When app close button clicked, the frame buffer object sometimes may be altered.
	// So check FBO state before use.
	GLuint state = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (state != GL_FRAMEBUFFER_COMPLETE) return;

    // It is good practice in a Cocoa application to allow the system to send the -drawRect:
    // message when it needs to draw, and not to invoke it directly from the timer.
    // All we do here is tell the display it needs a refresh
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
	// get the opengl view
	EAGLView* openGLView = [EAGLView sharedEGLView];
	[openGLView lockOpenGLContext];
	
	// run the main cocos2d loop
	cocos2d::CCDirector::sharedDirector()->mainLoop();
    
	// flush buffer (this line is very important!)
	[[openGLView openGLContext] flushBuffer];
	
	[openGLView unlockOpenGLContext];
    
	[pool release];
}

-(void) startMainLoop
{
	// NSTimer
	[renderTimer invalidate];
	renderTimer = nil;
    
	renderTimer = [NSTimer timerWithTimeInterval:self.interval/60.0f   //a 1ms time interval
                                          target:self
                                        selector:@selector(timerFired:)
                                        userInfo:nil
                                         repeats:YES];
    
    [[NSRunLoop currentRunLoop] addTimer:renderTimer
                                 forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop] addTimer:renderTimer
                                 forMode:NSEventTrackingRunLoopMode]; //Ensure timer fires during resize
}

-(void) end
{
	[renderTimer invalidate];
	renderTimer = nil;
	[self release];
	[[EAGLView sharedEGLView] closeAllWindows];
}

-(void) setAnimationInterval:(double)intervalNew
{
	self.interval = 60.0 * intervalNew;
	[renderTimer invalidate];
	renderTimer = nil;
	renderTimer = [NSTimer timerWithTimeInterval:self.interval/60.0f   //a 1ms time interval
										  target:self
										selector:@selector(timerFired:)
										userInfo:nil
										 repeats:YES];
	
	[[NSRunLoop currentRunLoop] addTimer:renderTimer 
								 forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:renderTimer 
								 forMode:NSEventTrackingRunLoopMode];
}

@end
