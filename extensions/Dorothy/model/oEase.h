#ifndef __DOROTHY_MODEL_OEASE_H__
#define __DOROTHY_MODEL_OEASE_H__

NS_DOROTHY_BEGIN

typedef float (*oEaseFunc)(float, float, float);

class oEase
{
public:
	enum
	{
		Linear = 0,
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
	static oEaseFunc get(uint8 id);
	static float func(uint8 id, float time, float begin, float change);
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OEASE_H__