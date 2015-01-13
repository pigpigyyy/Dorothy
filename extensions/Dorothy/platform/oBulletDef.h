/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OBULLET_DEF_H__
#define __DOROTHY_PLATFORM_OBULLET_DEF_H__

#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/model/oFace.h"

NS_DOROTHY_BEGIN
class oWorld;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN
class oBullet;
class oUnit;

class oBulletDef: public CCObject
{
public:
	enum { None = 0 };
	void setVelocity(float angle, float speed);
	PROPERTY_REF(oVec2, _velocity, Velocity);
	void setHighSpeedFix(bool var);
	bool isHighSpeedFix() const;
	PROPERTY_NAME(float, GravityScale);
	PROPERTY_NAME(oFace*, Face);
	int type;
	int endEffect;
	float lifeTime;
	float damageRadius;
	static oBulletDef* create();
	void setAsCircle(float radius);
	oBodyDef* getBodyDef() const;
	static const int SensorTag;
protected:
	oBulletDef();
	oRef<oBodyDef> _bodyDef;
	oRef<oFace> _face;
	CC_LUA_TYPE(oBulletDef)
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OBULLET_DEF_H__