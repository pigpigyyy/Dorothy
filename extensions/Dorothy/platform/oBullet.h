/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OBULLET_H__
#define __DOROTHY_PLATFORM_OBULLET_H__

#include "Dorothy/physics/oBody.h"
#include "Dorothy/misc/oIDisposable.h"

NS_DOROTHY_BEGIN
class oWorld;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN

class oUnit;
class oBulletDef;
class oBullet;

typedef Delegate<bool (oBullet* bullet, oUnit* target)> oBulletHandler;

class oBullet: public oBody
{
public:
	PROPERTY_READONLY(oUnit*, Owner);
	PROPERTY_BOOL(_isFaceRight, FaceRight);
	PROPERTY(CCNode*, _face, Face);
	PROPERTY_READONLY(oSensor*, DetectSensor);
	virtual void update(float dt);
	virtual void onExit();
	void onBodyEnter(oSensor* sensor, oBody* body);
	void onFaceDisposed(oIDisposable* item);
	oBulletDef* getBulletDef();
	static oBullet* create(oBulletDef* def, oUnit* unit);
	oTargetAllow targetAllow;
	oBulletHandler hitTarget;
	void addHandler(int handler);
	void removeHandler(int handler);
	void clearHandler();
	int type;
	virtual void destroy();
protected:
	oBullet(oBulletDef* def, oUnit* unit);
	virtual void updatePhysics();
private:
	oRef<oBulletDef> _bulletDef;
	oRef<oUnit> _owner;
	oSensor* _detectSensor;
	float _lifeTime;
	float _current;
	CC_LUA_TYPE(oBullet)
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OBULLET_H__
