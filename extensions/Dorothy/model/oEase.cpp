/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oEase.h"
#include <math.h>

NS_DOROTHY_BEGIN

static float Linear(float t, float b, float c)
{
	return b + t*c;
}
static float InQuad(float t, float b, float c)
{
	return c*t*t + b;
}
static float OutQuad(float t, float b, float c)
{
	return -c *t*(t-2) + b;
}
static float InOutQuad(float t, float b, float c)
{
	if ((t*=2) < 1) return (c/2)*t*t + b;
    --t;
	return (-c/2) * (t*(t-2) - 1) + b;
}
static float InCubic(float t, float b, float c)
{
	return c*t*t*t + b;
}
static float OutCubic(float t, float b, float c)
{
	--t;
	return c*(t*t*t + 1) + b;
}
static float InOutCubic(float t, float b, float c)
{
	if ((t*=2) < 1) return (c/2)*t*t*t + b;
    t-=2;
    return (c/2)*(t*t*t + 2) + b;
}
static float InQuart(float t, float b, float c)
{
	return c*t*t*t*t + b;
}
static float OutQuart(float t, float b, float c)
{
	--t;
	return -c * (t*t*t*t - 1) + b;
}
static float InOutQuart(float t, float b, float c)
{
	if ((t*=2) < 1) return (c/2)*t*t*t*t + b;
    t-=2;
    return -(c/2) * (t*t*t*t - 2) + b;
}
static float InQuint(float t, float b, float c)
{
	return c*t*t*t*t*t + b;
}
static float OutQuint(float t, float b, float c)
{
	--t;
	return c*(t*t*t*t*t+1) + b;
}
static float InOutQuint(float t, float b, float c)
{
	if ((t*=2) < 1) return (c/2)*t*t*t*t*t + b;
    t-=2;
	return (c/2)*(t*t*t*t*t + 2) + b;
}
static float InSine(float t, float b, float c)
{
	return -c * cosf(t * (b2_pi/2)) + c + b;
}
static float OutSine(float t, float b, float c)
{
	return c * sinf(t * (b2_pi/2)) + b;
}
static float InOutSine(float t, float b, float c)
{
	return -(c/2) * (cosf(b2_pi*t) - 1) + b;
}
static float InExpo(float t, float b, float c)
{
	return (t==0) ? b : c * powf(2, 10 * (t - 1)) + b;
}
static float OutExpo(float t, float b, float c)
{
	return (t==1.0f) ? b+c : c * (-powf(2, -10 * t) + 1) + b;
}
static float InOutExpo(float t, float b, float c)
{
	if (t==0) return b;
	if (t==1.0f) return b+c;
	if ((t*=2) < 1) return (c/2) * powf(2, 10 * (t - 1)) + b;
	return (c/2) * (-powf(2, -10 * --t) + 2) + b;
}
static float InCirc(float t, float b, float c)
{
	return -c * (sqrtf(1.0f - t*t) - 1) + b;
}
static float OutCirc(float t, float b, float c)
{
	--t;
	return c * sqrtf(1.0f - t*t) + b;
}
static float InOutCirc(float t, float b, float c)
{
	if ((t/=1.0f/2) < 1) return -c/2 * (sqrtf(1 - t*t) - 1) + b;
    t-=2;
    return c/2 * (sqrtf(1 - t*t) + 1) + b;
}
static float InElastic(float t, float b, float c)
{
	if (t==0) return b; if (t==1) return b+c;
	float p=0.3f;
	float a=c; 
	float s=p/4;
	float postFix = a*powf(2,10*(t-=1)); // this is a fix, again, with post-increment operators
	return -(postFix * sinf((t-s)*(2*b2_pi)/p)) + b;
}
static float OutElastic(float t, float b, float c)
{
	if (t==0) return b; if (t==1) return b+c;
	float p=0.3f;
	float a=c; 
	float s=p/4;
	return (a*powf(2,-10*t) * sinf( (t-s)*(2*b2_pi)/p ) + c + b);
}
static float InOutElastic(float t, float b, float c)
{
	if (t==0) return b; if ((t/=0.5f)==2) return b+c;
	float p=0.3f*1.5f;
	float a=c; 
	float s=p/4;
	if (t < 1) {
		float postFix=a*powf(2,10*(t-=1)); // postIncrement is evil
		return -0.5f*(postFix*sin((t-s)*(2*b2_pi)/p)) + b;
	} 
	float postFix = a*powf(2,-10*(t-=1)); // postIncrement is evil
	return postFix * sin((t-s)*(2*b2_pi)/p)*0.5f + c + b;
}
static float InBack(float t, float b, float c)
{
	const static float s = 1.70158f;
	return c*t*t*((s+1)*t - s) + b;
}
static float OutBack(float t, float b, float c)
{
	t = t - 1;
	const float s = 1.70158f;
	return c*(t * t * ((s + 1) * t + s) + 1) + b;
}
static float InOutBack(float t, float b, float c)
{
	float s = 1.70158f;
	if ((t*=2) < 1)
    {
        s*=1.525f;
        return c/2*(t*t*((s+1)*t - s)) + b;
    }
    t-=2;
    s*=1.525f;
    return c/2*(t*t*((s+1)*t + s) + 2) + b;
}
static float OutBounce(float t, float b, float c)
{
	if (t < (1.0f/2.75f))
	{
		return c*(7.5625f*t*t) + b;
	}
	else if (t < (2.0f/2.75f))
	{
        t-=(1.5f/2.75f);
		return c*(7.5625f*t*t + 0.75f) + b;
	}
	else if (t < (2.5f/2.75f))
	{
        t-=(2.25f/2.75f);
		return c*(7.5625f*t*t + 0.9375f) + b;
	}
	else
	{
        t-=(2.625f/2.75f);
		return c*(7.5625f*t*t + 0.984375f) + b;
	}
}
static float InBounce(float t, float b, float c)
{
	return c - OutBounce(1.0f-t, 0, c) + b;
}
static float InOutBounce(float t, float b, float c)
{
	if (t < 0.5f) return InBounce (t*2, 0, c) * 0.5f + b;
	return OutBounce (t*2-1.0f, 0, c) * 0.5f + c*0.5f + b;
}

static oEaseFunc g_eases[] =
{
	Linear,
	InQuad,
	OutQuad,
	InOutQuad,
	InCubic,
	OutCubic,
	InOutCubic,
	InQuart,
	OutQuart,
	InOutQuart,
	InQuint,
	OutQuint,
	InOutQuint,
	InSine,
	OutSine,
	InOutSine,
	InExpo,
	OutExpo,
	InOutExpo,
	InCirc,
	OutCirc,
	InOutCirc,
	InElastic,
	OutElastic,
	InOutElastic,
	InBack,
	OutBack,
	InOutBack,
	InBounce,
	OutBounce,
	InOutBounce
};

oEaseFunc oEase::get( uint8 index )
{
	if (index < sizeof(g_eases)/sizeof(oEaseFunc))
	{
		return g_eases[index];
	}
	return nullptr;
}

float oEase::func(uint8 id, float time, float begin, float change)
{
	if (id < sizeof(g_eases) / sizeof(oEaseFunc))
	{
		return g_eases[id](time, begin, change);
	}
	return 0.0f;
}
NS_DOROTHY_END
