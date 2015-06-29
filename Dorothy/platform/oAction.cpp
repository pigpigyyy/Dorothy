/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oAction.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oBullet.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/physics/oSensor.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/effect/oEffectCache.h"
#include "Dorothy/misc/oScriptHandler.h"
#include "Dorothy/misc/oHelper.h"
#include "Dorothy/audio/oAudio.h"

NS_DOROTHY_PLATFORM_BEGIN

oAction* oActionDef::toAction(oUnit* unit)
{
	oScriptAction* action = new oScriptAction(name, priority, unit);
	action->reaction = reaction;
	action->recovery = recovery;
	action->_available = available;
	action->_create = create;
	action->_stop = stop;
	return action;
}

// oAction
unordered_map<string, oOwn<oActionDef>> oAction::_actionDefs;

oAction::oAction(const string& name, int priority, oUnit* owner):
_name(name),
_priority(priority),
_isDoing(false),
_owner(owner),
reaction(-1.0f)
{ }

oAction::~oAction()
{
	_owner = nullptr;
}

const string& oAction::getName() const
{
	return _name;
}

int oAction::getPriority() const
{
	return _priority;
}

bool oAction::isDoing() const
{
	return _isDoing;
}

oUnit* oAction::getOwner() const
{
	return _owner;
}

bool oAction::isAvailable()
{
	return true;
}

void oAction::run()
{
	_isDoing = true;
	_reflexDelta = 0.0f;
	if (actionStart)
	{
		actionStart(this);
	}
}

void oAction::update( float dt )
{
	float reactionTime = _owner->sensity * oAction::reaction;
	if (reactionTime >= 0)
	{
		_reflexDelta += dt;
		if (_reflexDelta >= reactionTime)
		{
			_reflexDelta = 0.0f;
			//Check AI here
			oAI::conditionedReflex(_owner);
		}
	}
}

void oAction::stop()
{
	_isDoing = false;
	if (actionEnd)
	{
		actionEnd(this);
	}
}

void oAction::add( const string& name, int priority, float reaction, float recovery, int available, int create, int stop )
{
	oActionDef* actionDef = new oActionDef();
	actionDef->name = name;
	actionDef->priority = priority;
	actionDef->reaction = reaction;
	actionDef->recovery = recovery;
	actionDef->available = oScriptHandler::create(available);
	actionDef->create = oScriptHandler::create(create);
	actionDef->stop = oScriptHandler::create(stop);
	_actionDefs[name] = oOwnMake(actionDef);
}

void oAction::clear()
{
	_actionDefs.clear();
}

HANDLER_WRAP_START(oActionHandlerWrapper)
	void call(oAction* action) const
	{
		void* params[] = {action};
		int paramTypes[] = {CCLuaType<oAction>()};
		CCScriptEngine::sharedEngine()->executeFunction(getHandler(), 1, params, paramTypes);
	}
HANDLER_WRAP_END

void oAction::addHandler( int type, int handler )
{
	switch (type)
	{
	case oAction::Start:
		actionStart += std::make_pair(oActionHandlerWrapper(handler), &oActionHandlerWrapper::call);
		break;
	case oAction::End:
		actionEnd += std::make_pair(oActionHandlerWrapper(handler), &oActionHandlerWrapper::call);
		break;
	}
}

void oAction::removeHandler( int type, int handler )
{
	switch (type)
	{
	case oAction::Start:
		actionStart -= std::make_pair(oActionHandlerWrapper(handler), &oActionHandlerWrapper::call);
		break;
	case oAction::End:
		actionEnd -= std::make_pair(oActionHandlerWrapper(handler), &oActionHandlerWrapper::call);
		break;
	}
}

void oAction::clearHandler(int type)
{
	switch (type)
	{
	case oAction::Start:
		actionStart.Clear();
		break;
	case oAction::End:
		actionEnd.Clear();
		break;
	}
}

oScriptAction::oScriptAction( const string& name, int priority, oUnit* owner ):
oAction(name, priority, owner)
{ }

bool oScriptAction::isAvailable()
{
	void* params[] = {this};
	int paramTypes[] = {CCLuaType<oAction>()};
	return CCScriptEngine::sharedEngine()->executeFunction(_available->get(), 1, params, paramTypes) != 0;
}

void oScriptAction::run()
{
	oAction::run();
	int handler = CCScriptEngine::sharedEngine()->executeActionCreate(_create->get());
	_update = oScriptHandler::create(handler);
	CCScriptEngine::sharedEngine()->executeActionUpdate(_update->get(), this, CCLuaType<oAction>(), 0);
}

void oScriptAction::update( float dt )
{
	if (CCScriptEngine::sharedEngine()->executeActionUpdate(_update->get(), this, CCLuaType<oAction>(), dt) != 0)
	{
		oScriptAction::stop();
	}
	oAction::update(dt);
}

void oScriptAction::stop()
{
	_update = nullptr;
	void* params[] = {this};
	int paramTypes[] = {CCLuaType<oAction>()};
	CCScriptEngine::sharedEngine()->executeFunction(_stop->get(), 1, params, paramTypes);
	oAction::stop();
}

// oWalk
oWalk::oWalk( oUnit* unit ):
oAction(oID::ActionWalk, oID::PriorityWalk, unit)
{
	oAction::reaction = oID::ReactionWalk;
	oAction::recovery = oID::RecoveryWalk;
}

bool oWalk::isAvailable()
{
	return _owner->isOnSurface();
}

void oWalk::run()
{
	oModel* model = _owner->getModel();
	model->setSpeed(_owner->moveSpeed);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(oAction::recovery);
	model->resume(oID::AnimationWalk);
	_eclapsed = 0.0f;
	oAction::run();
}

void oWalk::update(float dt)
{
	if (_owner->isOnSurface())
	{
		float move = _owner->move * _owner->moveSpeed;
		if (_eclapsed < oAction::recovery)
		{
			_eclapsed += dt;
			move *= MIN(_eclapsed / oAction::recovery, 1.0f);
		}
		_owner->setVelocityX(_owner->isFaceRight() ? move : -move);
	}
	else
	{
		oWalk::stop();
	}
	oAction::update(dt);
}

void oWalk::stop()
{
	oAction::stop();
	_owner->getModel()->pause();
}

oAction* oWalk::create(oUnit* unit)
{
	return new oWalk(unit);
}

// oTurn
oTurn::oTurn( oUnit* unit ):
oAction(oID::ActionTurn, oID::PriorityTurn, unit)
{ }

void oTurn::run()
{
	_owner->setFaceRight(!_owner->isFaceRight());
	if (actionStart)
	{
		actionStart(this);
	}
	if (actionEnd)
	{
		actionEnd(this);
	}
}

oAction* oTurn::create( oUnit* unit )
{
	return new oTurn(unit);
}

oIdle::oIdle( oUnit* unit ):
oAction(oID::ActionIdle, oID::PriorityIdle, unit)
{
	oAction::reaction = oID::ReactionIdle;
	oAction::recovery = oID::RecoveryIdle;
}

void oIdle::run()
{
	oModel* model = _owner->getModel();
	model->setSpeed(1.0f);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(oAction::recovery);
	if (!_owner->isOnSurface())
	{
		oModel* model = _owner->getModel();
		model->resume(oID::AnimationJump);
	}
	else
	{
		model->resume(oID::AnimationIdle);
	}
	oAction::run();
}

void oIdle::update(float dt)
{
	oModel* model = _owner->getModel();
	if (!_owner->isOnSurface())
	{
		model->resume(oID::AnimationJump);
	}
	else if (_owner->getModel()->getCurrentAnimationName() != oID::AnimationIdle)
	{
		model->resume(oID::AnimationIdle);
	}
	oAction::update(dt);
}

void oIdle::stop()
{
	oAction::stop();
	_owner->getModel()->pause();
}

oAction* oIdle::create( oUnit* unit )
{
	return new oIdle(unit);
}

oJump::oJump( oUnit* unit ):
oAction(oID::ActionJump, oID::PriorityJump, unit)
{
	oAction::reaction = oID::ReactionJump;
	oAction::recovery = oID::RecoveryJump;
}

bool oJump::isAvailable()
{
	return _owner->isOnSurface();
}

void oJump::run()
{
	oModel* model = _owner->getModel();
	model->setSpeed(1.0f);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(oAction::recovery);
	model->resume(oID::AnimationJump);
	_current = 0.0f;
	_owner->setVelocityY(_owner->jump);
	oSensor* sensor = _owner->getGroundSensor();
	b2Body* self = _owner->getB2Body();
	b2Body* target = ((oBody*)sensor->getSensedBodies()->objectAtIndex(0))->getB2Body();
	b2DistanceInput input =
	{
		b2DistanceProxy(self->GetFixtureList()->GetShape(), 0),
		b2DistanceProxy(target->GetFixtureList()->GetShape(), 0),
		self->GetTransform(),
		target->GetTransform()
	};
	b2DistanceOutput output;
	b2Distance(&output, &input);
	target->ApplyLinearImpulse(
		b2Vec2(-self->GetMass() * self->GetLinearVelocityX(),
			-self->GetMass() * self->GetLinearVelocityY()),
			output.pointB);
	oAction::run();
}

void oJump::update(float dt)
{
	if (_current < 0.2f)//don`t check for ground for a while, for actor won`t lift immediately.
	{
		_current += dt;
	}
	else
	{
		if (_owner->isOnSurface())
		{
			oModel* model = _owner->getModel();
			model->setRecovery(oAction::recovery*0.5f);
			model->resume(oID::AnimationIdle);
			if (_current < 0.2f + oAction::recovery*0.5f)
			{
				_current += dt;
			}
			else oJump::stop();
		}
		oAction::update(dt);
	}
}

void oJump::stop()
{
	oAction::stop();
	_owner->getModel()->pause();
}

oAction* oJump::create( oUnit* unit )
{
	return new oJump(unit);
}

oCancel::oCancel( oUnit* unit ):
oAction(oID::ActionCancel, oID::PriorityCancel, unit)
{ }

void oCancel::run()
{ }

oAction* oCancel::create( oUnit* unit )
{
	return new oCancel(unit);
}

// oAttack

oAttack::oAttack(const string& name, oUnit* unit ):
oAction(name, oID::PriorityAttack, unit)
{
	oAction::recovery = oID::RecoveryAttack;
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationAttack] += std::make_pair(this, &oMeleeAttack::onAnimationEnd);
}

oAttack::~oAttack()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationAttack] -= std::make_pair(this, &oMeleeAttack::onAnimationEnd);
}

void oAttack::run()
{
	_current = 0;
	_attackDelay = _owner->getUnitDef()->attackDelay / _owner->attackSpeed;
	_attackEffectDelay = _owner->getUnitDef()->attackEffectDelay / _owner->attackSpeed;
	oModel* model = _owner->getModel();
	model->setLoop(false);
	model->setLook(oID::LookFight);
	model->setRecovery(oAction::recovery);
	model->setSpeed(_owner->attackSpeed);
	model->play(oID::AnimationAttack);
	oAction::run();
}

void oAttack::update( float dt )
{
	_current += dt;
	if (_attackDelay >= 0 && _current >= _attackDelay)
	{
		_attackDelay = -1;
		if (!_owner->getUnitDef()->sndAttack.empty())
		{
			oSound::play(_owner->getUnitDef()->sndAttack.c_str());
		}
		this->onAttack();
	}
	if (_attackEffectDelay >= 0 && _current >= _attackEffectDelay)
	{
		_attackEffectDelay = -1;
		const string& attackEffect = _owner->getUnitDef()->attackEffect;
		if (!attackEffect.empty())
		{
			oVec2 key = _owner->getModel()->getModelDef()->getKeyPoint(oUnitDef::AttackKey);
			if (_owner->getModel()->getModelDef()->isFaceRight() != _owner->isFaceRight())
			{
				key.x = -key.x;
			}
			oEffect* effect = oEffect::create(attackEffect);
			effect->setOffset(key)->attachTo(_owner)->autoRemove()->start();
		}
	}
}

void oAttack::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

void oAttack::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
	}
}

float oAttack::getDamage( oUnit* target )
{
	float factor = oSharedData.getDamageFactor(_owner->damageType, target->defenceType);
	float damage = (_owner->attackBase + _owner->attackBonus) * (_owner->attackFactor + factor);
	return damage;
}

oVec2 oAttack::getHitPoint( oBody* self, oBody* target, b2Shape* selfShape )
{
	oVec2 hitPoint;
	float distance = -1;
	for (b2Fixture* f = target->getB2Body()->GetFixtureList();f;f = f->GetNext())
	{
		if (!f->IsSensor())
		{
			b2DistanceInput input =
			{
				b2DistanceProxy(selfShape, 0),
				b2DistanceProxy(f->GetShape(), 0),
				self->getB2Body()->GetTransform(),
				target->getB2Body()->GetTransform()
			};
			b2DistanceOutput output;
			b2Distance(&output, &input);
			if (distance == -1 || distance > output.distance)
			{
				distance = output.distance;
				hitPoint = oWorld::oVal(output.pointB);
			}
		}
	}
	return hitPoint;
}

// oMeleeAttack
oMeleeAttack::oMeleeAttack( oUnit* unit ):
oAttack(oID::ActionMeleeAttack, unit)
{
	_polygon.SetAsBox(oWorld::b2Val(_owner->getWidth()*0.5f), 0.0005f);
}

void oMeleeAttack::onAttack()
{
	oSensor* sensor = _owner->getAttackSensor();
	if (sensor)
	{
		CCARRAY_START(oBody, body, sensor->getSensedBodies())
		{
			oUnit* target = CCLuaCast<oUnit>(body->getOwner());
			BLOCK_START
			{
				BREAK_NOT(target);
				bool attackRight = _owner->getPositionX() < target->getPositionX();
				bool faceRight = _owner->isFaceRight();
				BREAK_IF(attackRight != faceRight);//!(hitRight == faceRight || hitLeft == faceLeft)
				oRelation relation = oSharedData.getRelation(_owner, target);
				BREAK_IF(!_owner->targetAllow.isAllow(relation));
				/* Get hit point */
				oHit* hitAction = (oHit*)(target->getAction(oID::ActionHit));
				if (hitAction)
				{
					oVec2 hitPoint = oUnitDef::usePreciseHit ? oAttack::getHitPoint(_owner, target, &_polygon) : oVec2(target->getPosition());
					hitAction->setHitInfo(hitPoint, _owner->attackPower, !attackRight);
				}
				/* Make damage */
				float damage = oAttack::getDamage(target);
				target->properties["hp"] -= damage;
				if (damaged)
				{
					damaged(_owner, target, damage);
				}
			}
			BLOCK_END
		}
		CCARRAY_END
	}
}

oAction* oMeleeAttack::create( oUnit* unit )
{
	return new oMeleeAttack(unit);
}

// oRangeAttack
oRangeAttack::oRangeAttack( oUnit* unit ):
oAttack(oID::ActionRangeAttack, unit)
{ }

oAction* oRangeAttack::create( oUnit* unit )
{
	return new oRangeAttack(unit);
}

void oRangeAttack::onAttack()
{
	oBulletDef* bulletDef = _owner->getBulletDef();
	if (bulletDef)
	{
		oBullet* bullet = oBullet::create(bulletDef, _owner);
		bullet->targetAllow = _owner->targetAllow;
		bullet->hitTarget = std::make_pair(this, &oRangeAttack::onHitTarget);
		_owner->getWorld()->addChild(bullet, _owner->getZOrder());
		//SimpleAudioEngine::sharedEngine()->playEffect("sound/d_att.wav");
	}
}

bool oRangeAttack::onHitTarget( oBullet* bullet, oUnit* target )
{
	/* Get hit point */
	oHit* hitAction = (oHit*)(target->getAction(oID::ActionHit));
	if (hitAction)
	{
		b2Shape* shape = bullet->getDetectSensor()->getFixture()->GetShape();
		oVec2 hitPoint = oUnitDef::usePreciseHit ? oAttack::getHitPoint(_owner, target, shape) : oVec2(target->getPosition());
		bool attackRight = bullet->getVelocityX() > 0.0f;
		hitAction->setHitInfo(hitPoint, _owner->attackPower, !attackRight);
	}
	/* Make damage */
	float damage = oAttack::getDamage(target);
	target->properties["hp"] -= damage;
	if (damaged)
	{
		damaged(_owner, target, damage);
	}
	return true;
}

oHit::oHit( oUnit* unit ):
oAction(oID::ActionHit, oID::PriorityHit, unit),
_effect(nullptr),
_hitFromRight(true),
_attackPower(),
_hitPoint()
{
	oAction::recovery = oID::RecoveryHit;
	const string& hitEffect = _owner->getUnitDef()->hitEffect;
	if (!hitEffect.empty())
	{
		_effect = oEffect::create(hitEffect);
		_effect->attachTo(_owner);
		_effect->retain();
	}
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationHit] += std::make_pair(this, &oHit::onAnimationEnd);
}

oHit::~oHit()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationHit] -= std::make_pair(this, &oHit::onAnimationEnd);
}

void oHit::run()
{
	oModel* model = _owner->getModel();
	model->setLook(oID::LookSad);
	model->setLoop(false);
	model->setRecovery(oAction::recovery);
	model->setSpeed(1.0f);
	model->play(oID::AnimationHit);
	oVec2 key = CCPointApplyAffineTransform(_hitPoint, _owner->parentToNodeTransform());
	if (_effect)
	{
		_effect->setOffset(key)->start();
	}
	_owner->setVelocityX(_hitFromRight ? -_attackPower.x : _attackPower.x);
	_owner->setVelocityY(_attackPower.y);
	_owner->setFaceRight(_hitFromRight);
	oAction::run();
}

void oHit::update( float dt )
{ }

void oHit::setHitInfo( const oVec2& hitPoint, const oVec2& attackPower, bool hitFromRight )
{
	_hitPoint = hitPoint;
	_hitFromRight = hitFromRight;
	_attackPower = attackPower;
}

void oHit::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
	}
}

void oHit::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

oAction* oHit::create( oUnit* unit )
{
	return new oHit(unit);
}

oDie::oDie( oUnit* unit ):
oAction(oID::ActionDie, oID::PriorityDie, unit)
{
	oAction::recovery = oID::RecoveryDie;
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationDie] += std::make_pair(this, &oDie::onAnimationEnd);
}

oDie::~oDie()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationDie] -= std::make_pair(this, &oDie::onAnimationEnd);
}

void oDie::run()
{
	oModel* model = _owner->getModel();
	model->setLook(oID::LookDead);
	model->setLoop(false);
	model->setRecovery(oAction::recovery);
	model->setSpeed(1.0f);
	model->play(oID::AnimationDie);
	const string& hitEffect = _owner->getUnitDef()->hitEffect;
	if (!hitEffect.empty())
	{
		oEffect* effect = oEffect::create(hitEffect);
		effect->attachTo(_owner)->autoRemove()->start();
	}
	if (!_owner->getUnitDef()->sndDeath.empty())
	{
		oSound::play(_owner->getUnitDef()->sndDeath.c_str());
	}
	oAction::run();
}

void oDie::update( float dt )
{ }

void oDie::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

void oDie::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
	}
}

oAction* oDie::create( oUnit* unit )
{
	return new oDie(unit);
}

const char* oID::AnimationWalk = "walk";
const char* oID::AnimationAttack = "attack";
const char* oID::AnimationIdle = "idle";
const char* oID::AnimationJump = "jump";
const char* oID::AnimationHit = "hit";
const char* oID::AnimationDie = "die";

const char* oID::ActionWalk = "walk";
const char* oID::ActionTurn = "turn";
const char* oID::ActionMeleeAttack = "meleeAttack";
const char* oID::ActionRangeAttack = "rangeAttack";
const char* oID::ActionIdle = "idle";
const char* oID::ActionCancel = "cancel";
const char* oID::ActionJump = "jump";
const char* oID::ActionHit = "hit";
const char* oID::ActionDie = "die";

typedef oAction* (*oActionFunc)(oUnit* unit);
static const unordered_map<string,oActionFunc> g_createFuncs =
{
	{oID::ActionWalk, &oWalk::create},
	{oID::ActionTurn, &oTurn::create},
	{oID::ActionMeleeAttack, &oMeleeAttack::create},
	{oID::ActionRangeAttack, &oRangeAttack::create},
	{oID::ActionIdle, &oIdle::create},
	{oID::ActionCancel, &oCancel::create},
	{oID::ActionJump, &oJump::create},
	{oID::ActionHit, &oHit::create},
	{oID::ActionDie, &oDie::create}
};

oAction* oAction::create( const string& name, oUnit* unit )
{
	auto it = _actionDefs.find(name);
	if (it != _actionDefs.end())
	{
		return it->second->toAction(unit);
	}
	else
	{
		auto it = g_createFuncs.find(name);
		if (it != g_createFuncs.end())
		{
			return it->second(unit);
		}
	}
	return nullptr;
}

const int oID::PriorityIdle = 0;
const int oID::PriorityWalk = 1;
const int oID::PriorityTurn = 2;
const int oID::PriorityJump = 2;
const int oID::PriorityAttack = 3;
const int oID::PriorityCancel = 2147483647;
const int oID::PriorityHit = 4;
const int oID::PriorityDie = 5;

const float oID::ReactionWalk = 1.5f;
const float oID::ReactionIdle = 2.0f;
const float oID::ReactionJump = 1.5f;

const float oID::RecoveryWalk = 0.1f;
const float oID::RecoveryAttack = 0.2f;
const float oID::RecoveryIdle = 0.1f;
const float oID::RecoveryJump = 0.2f;
const float oID::RecoveryHit = 0.05f;
const float oID::RecoveryDie = 0.05f;

const char* oID::LookHappy = "happy";
const char* oID::LookFight = "fight";
const char* oID::LookSad = "sad";
const char* oID::LookDead = "dead";

NS_DOROTHY_PLATFORM_END
