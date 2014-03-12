#ifndef __DOROTHY_MODEL_OKEYFRAMEDEF_H__
#define __DOROTHY_MODEL_OKEYFRAMEDEF_H__

#include "Dorothy/model/oModelAnimationDef.h"

NS_DOROTHY_BEGIN

class oSequence;

class oKeyFrameDef
{
public:
	enum
	{
		MaxKeyAttributes = 6
	};
	oKeyFrameDef();
	uint8 easePos;
	uint8 easeScale;
	uint8 easeOpacity;
	uint8 easeRotation;
	uint8 easeSkew;
	bool visible;/*1*/
	float opacity;/*2*/
	float duration;
	float x;
	float y;/*3*/
	float scaleX;
	float scaleY;/*4*/
	float rotation;/*5*/
	float skewX;
	float skewY;/*6*/
	string toXml();
};

class oKeyAnimationDef: public oModelAnimationDef
{
public:
	void add(oKeyFrameDef* def);
	virtual oActionDuration* toAction();
	virtual string toXml();
	virtual void restoreResetAnimation(CCObject* data);
private:
	oOwnVector<oKeyFrameDef> _keyFrameDefs;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OKEYFRAMEDEF_H__