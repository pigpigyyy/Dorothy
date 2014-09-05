/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oBullet.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/physics/oSensor.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/effect/oEffectCache.h"
#include "Dorothy/misc/oScriptHandler.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/model/oModelDef.h"

NS_DOROTHY_PLATFORM_BEGIN

oBullet::oBullet(oBulletDef* bulletDef, oUnit* unit) :
oBody(bulletDef->getBodyDef(), unit->getWorld()),
type(bulletDef->type),
_bulletDef(bulletDef),
_owner(unit),
_current(0),
_lifeTime(bulletDef->lifeTime),
_face(nullptr)
{
	oBullet::setFaceRight(unit->isFaceRight());
	_detectSensor = oBody::getSensorByTag(oBulletDef::SensorTag);
	_detectSensor->bodyEnter += std::make_pair(this, &oBullet::onBodyEnter);
	oVec2 v = _bulletDef->getVelocity();
	oBody::setVelocity((_isFaceRight ? v.x : -v.x), v.y);
	oBody::setGroup(oSharedData.getGroupDetect());
	oFace* face = bulletDef->getFace();
	if (face)
	{
		CCNode* node = face->toNode();
		oBullet::setFace(node);
	}
	oModel* model = unit->getModel();
	const oVec2& offset = (model ? model->getModelDef()->getKeyPoint(oUnitDef::BulletKey) : oVec2::zero);
	oBullet::setPosition(
		ccpAdd(
		unit->getPosition(),
		(unit->isFaceRight() ? ccp(-offset.x, offset.y) : (CCPoint)offset)));
	if (oBody::getBodyDef()->gravityScale != 0.0f)
	{
		oBullet::setRotation(-CC_RADIANS_TO_DEGREES(atan2f(v.y, unit->isFaceRight() ? v.x : -v.x)));
	}
	this->scheduleUpdate();
}

void oBullet::updatePhysics()
{
	if (_bodyB2->IsAwake())
	{
		const b2Vec2& pos = _bodyB2->GetPosition();
		/* Here only CCNode::setPosition(const CCPoint& var) work for modify CCNode`s position.
		 Other positioning functions have been overridden by oBody`s.
		*/
		CCNode::setPosition(CCPoint(oWorld::oVal(pos.x), oWorld::oVal(pos.y)));
		if (_bodyB2->GetGravityScale() != 0.0f)
		{
			b2Vec2 velocity = _bodyB2->GetLinearVelocity();
			CCNode::setRotation(-CC_RADIANS_TO_DEGREES(atan2f(velocity.y, velocity.x)));
		}
	}
}

void oBullet::update( float dt )
{
	_current += dt;
	if (_current >= _lifeTime)
	{
		oBullet::destroy();
	}
}

void oBullet::onExit()
{
	oBody::onExit();
	if (_face)
	{
		CCNode::traverse(
			_face,
			[](CCNode* node)->void
			{
				oIDisposable* item = dynamic_cast<oIDisposable*>(node);
				item->disposing.Clear();
			}
		);
		_face = nullptr;
	}
}

void oBullet::cleanup()
{
	oBody::cleanup();
	oBullet::clearHandler();
}

oBullet* oBullet::create(oBulletDef* def, oUnit* unit)
{
	oBullet* bullet = new oBullet(def, unit);
	bullet->autorelease();
	return bullet;
}

oUnit* oBullet::getOwner() const
{
	return _owner;
}

oSensor* oBullet::getDetectSensor() const
{
	return _detectSensor;
}

void oBullet::setFaceRight(bool var)
{
	_isFaceRight = var;
}

bool oBullet::isFaceRight() const
{
	return _isFaceRight;
}

void oBullet::onBodyEnter( oSensor* sensor, oBody* body )
{
	if (body == _owner)
	{
		return;
	}
	oUnit* unit = CCLuaCast<oUnit>(body->getOwner());
	bool isHitTerrain = oSharedData.isTerrain(body) && oBullet::targetAllow.isTerrainAllowed();
	bool isHitUnit = unit && oBullet::targetAllow.isAllow(oSharedData.getRelation(_owner, unit));
	bool isHit = isHitTerrain || isHitUnit;
	if (isHit && hitTarget)
	{
		bool isRangeDamage = _bulletDef->damageRadius > 0.0f;
		if (isRangeDamage)
		{
			CCPoint pos = this->getPosition();
			CCRect rect(
				pos.x - _bulletDef->damageRadius,
				pos.y - _bulletDef->damageRadius,
				_bulletDef->damageRadius * 2,
				_bulletDef->damageRadius * 2);
			_world->query(rect, [&](oBody* body)
			{
				oUnit* unit = CCLuaCast<oUnit>(body->getOwner());
				if (unit && targetAllow.isAllow(oSharedData.getRelation(_owner, unit)))
				{
					hitTarget(this, unit);
				}
				return false;
			});
		}
		else if (isHitUnit)
		{
			/* hitTarget function may cancel this hit by returning false */
			isHit = hitTarget(this, unit);
		}
	}
	if (isHit)
	{
		oBullet::destroy();
	}
}

oBulletDef* oBullet::getBulletDef()
{
	return _bulletDef;
}

void oBullet::setFace(CCNode* var)
{
	oIDisposable* newItem = dynamic_cast<oIDisposable*>(var);
	if (newItem == nullptr)
	{
		return;
	}
	if (_face)
	{
		oIDisposable* oldItem = dynamic_cast<oIDisposable*>(_face);
		oldItem->disposing.Clear();
		CCNode::removeChild(_face, true);
	}
	_face = var;
	CCNode::addChild(var);
	newItem->disposing = std::make_pair(this, &oBullet::onFaceDisposed);
}

CCNode* oBullet::getFace() const
{
	return _face;
}

void oBullet::onFaceDisposed( oIDisposable* item )
{
	_face = nullptr;
	item->disposing.Clear();
	oBody::destroy();
}

void oBullet::destroy()
{
	CCAssert(_detectSensor != nullptr, "Invoke it once only!");
	if (!_isDestroyed)
	{
		_isDestroyed = true;
		_detectSensor->setEnabled(false);
		_detectSensor = nullptr;
		CCNode::unscheduleAllSelectors();
		if (_bulletDef->endEffect != oEffectType::None)
		{
			oEffect* effect = oEffect::create(_bulletDef->endEffect);
			effect->setOffset(this->getPosition())
				->attachTo(this->getParent())
				->autoRemove()
				->start();
		}
		oBody::setVelocity(0, 0);
		hitTarget.Clear();
		if (_face)
		{
			oIDisposable* item = dynamic_cast<oIDisposable*>(_face);
			item->dispose();
		}
		else
		{
			oBody::destroy();
		}
	}
}

HANDLER_WRAP_START(oBulletHandlerWrapper)
	bool call(oBullet* bullet, oUnit* target) const
	{
		CCObject* params[] = {bullet, target};
		return CCScriptEngine::sharedEngine()->executeFunction(getHandler(), 2, params) != 0;
	}
HANDLER_WRAP_END

void oBullet::addHandler( int handler )
{
	hitTarget += std::make_pair(oBulletHandlerWrapper(handler), &oBulletHandlerWrapper::call);
}

void oBullet::removeHandler( int handler )
{
	hitTarget -= std::make_pair(oBulletHandlerWrapper(handler), &oBulletHandlerWrapper::call);
}

void oBullet::clearHandler()
{
	hitTarget.Clear();
}

NS_DOROTHY_PLATFORM_END
