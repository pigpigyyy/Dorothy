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
	return (-c/2) * ((--t)*(t-2) - 1) + b;
}
static float InCubic(float t, float b, float c)
{
	return c*t*t*t + b;
}
static float OutCubic(float t, float b, float c)
{
	return c*((t-1)*t*t + 1) + b;
}
static float InOutCubic(float t, float b, float c)
{
	if ((t*=2) < 1) return (c/2)*t*t*t + b;
	return (c/2)*((t-=2)*t*t + 2) + b;
}
static float InQuart(float t, float b, float c)
{
	return c*t*t*t*t + b;
}
static float OutQuart(float t, float b, float c)
{
	return -c * ((t-1)*t*t*t - 1) + b;
}
static float InOutQuart(float t, float b, float c)
{
	if ((t*=2) < 1) return (c/2)*t*t*t*t + b;
	return -(c/2) * ((t-=2)*t*t*t - 2) + b;
}
static float InQuint(float t, float b, float c)
{
	return c*t*t*t*t*t + b;
}
static float OutQuint(float t, float b, float c)
{
	return c*((t-1)*t*t*t*t + 1) + b;
}
static float InOutQuint(float t, float b, float c)
{
	if ((t*=2) < 1) return (c/2)*t*t*t*t*t + b;
	return (c/2)*((t-=2)*t*t*t*t + 2) + b;
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
	return c * sqrtf(1.0f - (t-1)*t) + b;
}
static float InOutCirc(float t, float b, float c)
{
	if ((t/=1.0f/2) < 1) return -c/2 * (sqrtf(1 - t*t) - 1) + b;
	return c/2 * (sqrtf(1 - (t-=2)*t) + 1) + b;
}
static float InElastic(float t, float b, float c)
{
	static float s=1.70158f, p=0.3f, a=c;
	if (t==0) return b;  if (t==1) return b+c;
	if (a < abs(c)) { a=c; s=p/4; }
	else s = p/(2*b2_pi) * asinf(c/a);
	return -(a*powf(2,10*(t-=1)) * sinf( (t-s)*(2*b2_pi)/p )) + b;
}
static float OutElastic(float t, float b, float c)
{
	static float s=1.70158f, p=0.3f, a=c;
	if (t==0) return b;  if (t==1) return b+c;
	if (a < abs(c)) { a=c; s=p/4; }
	else s = p/(2*b2_pi) * asinf(c/a);
	return a*powf(2,-10*t) * sinf( (t-s)*(2*b2_pi)/p ) + c + b;
}
static float InOutElastic(float t, float b, float c)
{
	static float s=1.70158f, p=(0.3f*1.5f), a=c;
	if (t==0) return b;  if ((t*=2)==2) return b+c;
	if (a < abs(c)) { a=c; s=p/4; }
	else s = p/(2*b2_pi) * asinf(c/a);
	if (t < 1) return -0.5f*(a*powf(2,10*(t-=1)) * sinf( (t-s)*(2*b2_pi)/p )) + b;
	return a*powf(2,-10*(t-=1)) * sinf( (t-s)*(2*b2_pi)/p )*0.5f + c + b;
}
static float InBack(float t, float b, float c)
{
	const static float s = 1.70158f;
	return c*t*t*((s+1)*t - s) + b;
}
static float OutBack(float t, float b, float c)
{
	t = t - 1;
	const static float s = 1.70158f;
	return c*(t * t * ((s + 1) * t + s) + 1) + b;
}
static float InOutBack(float t, float b, float c)
{
	static float s = 1.70158f;
	if ((t*=2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
	return c/2*((t-=2)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
}
static float OutBounce(float t, float b, float c)
{
	if (t < (1.0f/2.75f))
	{
		return c*(7.5625f*t*t) + b;
	}
	else if (t < (2.0f/2.75f))
	{
		return c*(7.5625f*(t-=(1.5f/2.75f))*t + 0.75f) + b;
	}
	else if (t < (2.5f/2.75f))
	{
		return c*(7.5625f*(t-=(2.25f/2.75f))*t + 0.9375f) + b;
	}
	else
	{
		return c*(7.5625f*(t-=(2.625f/2.75f))*t + 0.984375f) + b;
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

NS_DOROTHY_END
