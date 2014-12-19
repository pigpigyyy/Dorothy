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

#import "AccelerometerDelegateWrapper.h"

@implementation AccelerometerDispatcher

static AccelerometerDispatcher* s_pAccelerometerDispatcher;

@synthesize delegate_;
@synthesize acceleration_;

+ (id) sharedAccelerometerDispather
{
    if (s_pAccelerometerDispatcher == nil) {
        s_pAccelerometerDispatcher = [[self alloc] init];
    }
    
    return s_pAccelerometerDispatcher;
}

- (id) init
{
    acceleration_ = new cocos2d::CCAcceleration();
	motionManager_ = [[CMMotionManager alloc] init];
	motionManager_.accelerometerUpdateInterval = 1.0/60;
	[motionManager_ startAccelerometerUpdatesToQueue: [[NSOperationQueue alloc] init]
		withHandler:^(CMAccelerometerData *data, NSError *error) {
			dispatch_async(dispatch_get_main_queue(), ^{
				if (!delegate_)
				{
					return;
				}
				acceleration_->x = data.acceleration.x;
				acceleration_->y = data.acceleration.y;
				acceleration_->z = data.acceleration.z;
				acceleration_->timestamp = data.timestamp;
				double tmp = acceleration_->x;
				switch ([[UIApplication sharedApplication] statusBarOrientation])
				{
					case UIInterfaceOrientationLandscapeRight:
						acceleration_->x = -acceleration_->y;
						acceleration_->y = tmp;
						break;
					case UIInterfaceOrientationLandscapeLeft:
						acceleration_->x = acceleration_->y;
						acceleration_->y = -tmp;
						break;
					case UIInterfaceOrientationPortraitUpsideDown:
						acceleration_->x = -acceleration_->y;
						acceleration_->y = -tmp;
						break;
					case UIInterfaceOrientationPortrait:
						break;
					default:
						break;
				}
				delegate_->didAccelerate(acceleration_);
			});
		}
	];
    return self;
}

- (void) dealloc
{
	motionManager_ = 0;
    s_pAccelerometerDispatcher = 0;
    delegate_ = 0;
    delete acceleration_;
    [super dealloc];
}

- (void) addDelegate: (cocos2d::CCAccelerometerDelegate *) delegate
{
    delegate_ = delegate;
}

-(void) setAccelerometerInterval:(float)interval
{
	motionManager_.accelerometerUpdateInterval = interval;
}

@end
