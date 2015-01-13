/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oBullet.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/model/oClip.h"
#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/model/oFace.h"
#include "Dorothy/effect/oEffectCache.h"

NS_DOROTHY_PLATFORM_BEGIN

const int oBulletDef::SensorTag = 0;

oBulletDef::oBulletDef():
type(0),
lifeTime(0),
damageRadius(0),
endEffect(oEffectType::None),
_bodyDef(oBodyDef::create())
{ }

oBodyDef* oBulletDef::getBodyDef() const
{
	return _bodyDef;
}

oBulletDef* oBulletDef::create()
{
	oBulletDef* def = new oBulletDef();
	def->autorelease();
	return def;
}

void oBulletDef::setVelocity( float angle, float speed )
{
	angle = CC_DEGREES_TO_RADIANS(angle);
	_velocity.x = cosf(angle) * speed;
	_velocity.y = sinf(angle) * speed;
}

void oBulletDef::setVelocity( const oVec2& velocity )
{
	_velocity = velocity;
}

const oVec2& oBulletDef::getVelocity() const
{
	return _velocity;
}

void oBulletDef::setHighSpeedFix(bool var)
{
	_bodyDef->bullet = var;
}

bool oBulletDef::isHighSpeedFix() const
{
	return _bodyDef->bullet;
}

void oBulletDef::setGravityScale(float var)
{
	_bodyDef->gravityScale = var;
}

float oBulletDef::getGravityScale() const
{
	return _bodyDef->gravityScale;
}

void oBulletDef::setAsCircle( float radius )
{
	_bodyDef->clearFixtures();
	_bodyDef->attachCircleSensor(oBulletDef::SensorTag, radius);
}

void oBulletDef::setFace(oFace* var)
{
	_face = var;
}

oFace* oBulletDef::getFace() const
{
	return _face;
}

NS_DOROTHY_PLATFORM_END
