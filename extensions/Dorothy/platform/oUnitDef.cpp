/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oUnitDef.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oAI.h"

#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModelCache.h"
#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/effect/oEffectCache.h"
#include "Dorothy/physics/oSensor.h"

NS_DOROTHY_PLATFORM_BEGIN

const float oUnitDef::BOTTOM_OFFSET(4.0f);
const float oUnitDef::GROUND_SENSOR_HEIGHT(4.0f);
bool oUnitDef::usePreciseHit = true;
const char* oUnitDef::BulletKey = "bullet";
const char* oUnitDef::AttackKey = "attack";
const char* oUnitDef::HitKey = "hit";

oUnitDef::oUnitDef() :
tag(0),
reflexArc(),
_scale(1.0f),
sensity(0),
move(0),
jump(0),
maxHp(0),
detectDistance(0),
attackBase(0),
attackDelay(0),
attackEffect(),
attackEffectDelay(0),
attackRange(),
attackPower(),
attackType(oAttackType::Melee),
attackTarget(oAttackTarget::Single),
damageType(0),
defenceType(0),
hitEffect(),
bulletType(),
_bodyDef(oBodyDef::create()),
_density(1.0f),
_friction(0.4f),
_restitution(0.4f)
{ }

oUnitDef* oUnitDef::create()
{
	oUnitDef* unitDef = new oUnitDef();
	INIT(unitDef);
	unitDef->autorelease();
	return unitDef;
}

oBodyDef* oUnitDef::getBodyDef() const
{
	return _bodyDef;
}

oModelDef* oUnitDef::getModelDef() const
{
	return _modelDef;
}

const CCSize& oUnitDef::getSize() const
{
	return _size;
}

void oUnitDef::setSize(const CCSize& size)
{
	_size = size;
	oUnitDef::updateBodyDef();
}

void oUnitDef::setDensity(float density)
{
	_density = density;
	_bodyDef->setDensity(density);
}
float oUnitDef::getDensity() const
{
	return _density;
}

void oUnitDef::setFriction(float friction)
{
	_friction = friction;
	_bodyDef->setFriction(friction);
}
float oUnitDef::getFriction() const
{
	return _friction;
}

void oUnitDef::setRestitution(float restitution)
{
	_restitution = restitution;
	_bodyDef->setRestitution(restitution);
}
float oUnitDef::getRestitution() const
{
	return _restitution;
}

void oUnitDef::setScale(float var)
{
	_scale = var;
	oUnitDef::updateBodyDef();
}
float oUnitDef::getScale() const
{
	return _scale;
}

void oUnitDef::updateBodyDef()
{
	_bodyDef->clearFixtures();
	_bodyDef->fixedRotation = false;
	CCSize size = _size;
	size.width *= _scale;
	size.height *= _scale;
	if (size.width != 0.0f && size.height != 0.0f)
	{
		_bodyDef->fixedRotation = true;
		float hw = size.width * 0.5f;
		float hh = size.height * 0.5f;
		oVec2 vertices[] =
		{
			oVec2(-hw, hh),
			oVec2(-hw + BOTTOM_OFFSET, -hh),
			oVec2(hw - BOTTOM_OFFSET, -hh),
			oVec2(hw, hh)
		};
		_bodyDef->attachPolygon(vertices, 4, _density, _friction, _restitution);
		_bodyDef->attachPolygonSensor(
			oUnitDef::GroundSensorTag,
			size.width - BOTTOM_OFFSET * 2,
			GROUND_SENSOR_HEIGHT,
			b2Vec2(0, -hh - GROUND_SENSOR_HEIGHT * 0.5f),
			0);
	}
}

void oUnitDef::setModel(const string& modelFile)
{
	_model = modelFile;
	if (!modelFile.empty())
	{
		_modelDef = oSharedModelCache.load(modelFile.c_str());
		if (_size == CCSize::zero)
		{
			oUnitDef::setSize(_modelDef->getSize());
		}
	}
}
const string& oUnitDef::getModel() const
{
	return _model;
}

void oUnitDef::setStatic(bool var)
{
	_bodyDef->type = var ? b2_staticBody : b2_dynamicBody;
}
bool oUnitDef::isStatic() const
{
	return _bodyDef->type == b2_staticBody;
}

NS_DOROTHY_PLATFORM_END
