/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MODEL_OKEYFRAMEDEF_H__
#define __DOROTHY_MODEL_OKEYFRAMEDEF_H__

#include "model/oModelAnimationDef.h"

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
	const oOwnVector<oKeyFrameDef>& getFrames() const;
	virtual oActionDuration* toAction();
	virtual string toXml();
	virtual void restoreResetAnimation(CCObject* data);
private:
	oOwnVector<oKeyFrameDef> _keyFrameDefs;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OKEYFRAMEDEF_H__